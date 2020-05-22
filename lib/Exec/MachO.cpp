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

#define CPU_TYPE_X86 7
#define CPU_ARCH_ABI64 0x01000000
#define	CPU_TYPE_X86_64	(CPU_TYPE_X86 | CPU_ARCH_ABI64)
#define MACHO_64_MAGIC 0xfeedfacf
#define MH_EXEC 2

/**
 * 64-bit MachO header format
 */
struct Mach64_Hdr {
    uint32_t magic; /* MACHO_64_MAGIC */
    int cpu_type; /* CPU_TYPE_{X86,X86_64} */
    int cpu_subtype; /* don't care */
    uint32_t file_type;
    uint32_t n_cmd; /* number of load commands */
    uint32_t tot_cmd_sz; /* total size of all the load commands */
    uint32_t flags;
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

MachO::MachO(std::string file) : ExecutableFormat(std::move(file)) {}

void MachO::parse()
{
    // TODO
}
