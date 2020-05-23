#include "MachO.h"

/**
 * Magic values needed for the MachO header
 * Only 64-bit Intel architectures are supported
 *
 * This MachO parser only supports actual executable files -- that is, if
 * it encounters an object file (*.o) or library (*.a, *.dylib), then the
 * parsing will fail.
 *
 * The above behaviour is due to the fact that TraceGen only expects to be
 * given executable files (which it will run after the initial parse step)
 */

#define CPU_TYPE_X86 7U
#define CPU_ARCH_ABI64 0x01000000U
#define CPU_TYPE_X86_64 (CPU_TYPE_X86 | CPU_ARCH_ABI64)
#define MACH64_MAGIC 0xfeedfacfU
#define MH_EXEC 2U

/**
 * 64-bit MachO header format
 */
struct Mach64_Hdr {
    uint32_t magic; /* MACH64_MAGIC */
    int cpu_type; /* CPU_TYPE_X86_64 */
    int cpu_subtype; /* don't care */
    uint32_t file_type /* MH_EXEC */;
    uint32_t n_cmd; /* number of load commands */
    uint32_t tot_cmd_sz; /* total size of all the load commands */
    uint32_t flags;
    uint32_t reserved;
};

/**
 * There are various types of load commands, but the only one that matters for
 * this project is the Segment. This is because other things like dynamic library
 * loading will not be analysed for trace generation, and so, can be ignored outright.
 *
 * When the parser encounters a load command that has cmd != LC_SEGMENT_64, it skips to
 * the next command, continuing until all the commands have been either processed or
 * skipped.
 */

#define LC_SEGMENT_64 0x19

/**
 * 64-bit MachO Load Command Header
 */
struct Mach64_Load_Cmd {
    uint32_t cmd; /* command type */
    uint32_t size; /* total size */
};

/**
 * 64-bit MachO Segment Load Command Header
 */
struct Mach64_Segment_Cmd {
    uint32_t cmd; /* LC_SEGMENT_64 */
    uint32_t cmd_size; /* command size */
    char name[16]; /* segment name */

    uint64_t vm_addr; /* segment's virtual address */
    uint64_t vm_size; /* segment size in memory */

    uint64_t f_off; /* file offset */
    uint64_t f_size; /* segment size in the file */

    int max_pt, init_pt; /* don't care (VM protections) */

    uint32_t n_sect; /* number of sections in the segment */
    uint32_t flags;
};

/**
 * 64-bit MachO Section Header
 */
struct Mach64_Section {
    char sec_name[16]; /* section name */
    char seg_name[16]; /* segment name that this section belongs to */
    uint64_t addr; /* memory address */
    uint64_t size; /* size in bytes of the section */
    uint32_t f_off; /* file offset */
    uint32_t align; /* section alignment */
    uint32_t rel_off; /* relocation file offset (don't care) */
    uint32_t flags;
    uint32_t res1, res2, res3; /* reserved */
};

using namespace tg;

/**
 * Adjust the load command header pointer to the next header
 * @param curr - current header
 * @return a pointer to the next header
 */
static inline Mach64_Load_Cmd* adjust_ptr(Mach64_Load_Cmd* curr)
{
    auto* raw = reinterpret_cast<char*>(curr);
    return reinterpret_cast<Mach64_Load_Cmd*>(raw + curr->size);
}

/**
 * Get the first section header for the given segment
 * @param cmd - segment to compute for
 * @return a pointer to the first section header
 */
static inline Mach64_Section* section_ptr(Mach64_Segment_Cmd* cmd)
{
    auto* raw = reinterpret_cast<char*>(cmd);
    return reinterpret_cast<Mach64_Section*>(raw + sizeof(Mach64_Segment_Cmd));
}

Metadata MachO::parse(const std::string& file)
{
    read(file);
    auto* hdr = reinterpret_cast<Mach64_Hdr*>(data.data());

    /**
     * The provided file should be:
     *    [+] 64-bit MachO
     *    [+] x86_64 platform
     *    [+] Executable
     */
    bool good = hdr->magic == MACH64_MAGIC &&
            hdr->cpu_type == CPU_TYPE_X86_64 &&
            hdr->file_type == MH_EXEC;

    if(!good) {
        throw std::runtime_error("unsupported executable type provided\n");
    }

    auto* ld_hdr = reinterpret_cast<Mach64_Load_Cmd*>(data.data() + sizeof(Mach64_Hdr));

    for(uint32_t i = 0; i < hdr->n_cmd; i++) {
        // Skip all non-segment load commands
        if(ld_hdr->cmd != LC_SEGMENT_64) {
            ld_hdr = adjust_ptr(ld_hdr);
            continue;
        }

        auto* seg = reinterpret_cast<Mach64_Segment_Cmd*>(ld_hdr);

        /**
         * Only process the __TEXT segment, since that is where the actual
         * executable code resides.
         */
        if(std::string(seg->name) != "__TEXT") {
            ld_hdr = adjust_ptr(ld_hdr);
            continue;
        }

        auto* section = section_ptr(seg);

        for(uint32_t j = 0; j < seg->n_sect; j++) {
            /**
             * The __TEXT segment contains a few different sections, but the only
             * one that is actually useful here is the __text section.
             */
            if(std::string(section[j].sec_name) != "__text") {
                continue;
            }

            /**
             * Copy the __text section
             */
            auto start = data.begin() + section->f_off;
            auto end = start + section->size;

            Metadata data(std::vector<char>(start, end), section->addr);
            return data;
        }
    }

    /**
     * Control flow should never reach here for valid executables
     *
     * This is because reaching this point implies that the __text section was not
     * reached while looking through the __TEXT segment or perhaps there was no
     * such segment in the first place.
     *
     * Either way, signal this error condition by throwing an exception, since this
     * is cleaner than trying to return some metadata object that ``represents'' an
     * invalid state.
     */

    throw std::runtime_error("invalid MachO executable -- missing __text section!\n");
}
