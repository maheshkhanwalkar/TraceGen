#pragma once
#include <string>
#include <vector>

#include "Metadata.h"

namespace tg {

/**
 * Executable Format
 *
 * This top-level class encapsulates the common features of various executable
 * formats that exist.
 *
 * Every format will have the same general ``broad'' classes of executable sections:
 *    + Text section (executable code)
 *    + Data section (for initialised data)
 *    + BSS section (uninitialised data)
 *    + Rodata section (read-only data)
 *
 * In addition, each section is essentially just a contiguous stream of bytes which
 * generally have an address associated with them (virtual and/or physical)
 *
 * TraceGen only needs a small set of executable format parsing features, namely,
 * extracting the text section for processing, so that is the only feature that is
 * exposed (and implemented) in this library.
 */
class ExecutableFormat {
public:
    /**
     * Construct an executable format object
     */
    explicit ExecutableFormat() = default;

    /**
     * Parse the provided file, identifying the various sections and initialising
     * any internal data structures, as needed.
     *
     * This method is pure virtual since the parsing will be dependent on the
     * actual type of executable format (i.e. ELF, Mach-O, PE/COFF)
     *
     * @param file - file to read and parse
     * @return the parsed metadata
     */
    virtual Metadata parse(const std::string& file) = 0;

    /**
     * Destroy the executable format
     */
    virtual ~ExecutableFormat() = default;

protected:
    std::vector<char> data;

    /**
     * Read the executable file
     *
     * This stores the entire raw file within the internal buffer. However, this
     * raw format is not yet usable -- the file *must* be parsed first. Only then
     * will the other methods dealing with specific executable sections can be used.
     *
     * @param file - file to read
     * @throws std::runtime_error for any I/O-related problems
     */
    void read(const std::string& file);
};

}
