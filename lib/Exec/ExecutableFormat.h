#pragma once
#include <string>
#include <vector>

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
     * Construct an executable format object with the provided
     * file as the underlying data to process.
     *
     * @param file - underlying file to process
     */
    explicit ExecutableFormat(std::string file);

    /**
     * Read the executable file
     *
     * This stores the entire raw file within the internal buffer. However, this
     * raw format is not yet usable -- the file *must* be parsed first. Only then
     * will the other methods dealing with specific executable sections can be used.
     *
     * @return true if successful, false otherwise
     */
    bool read();

    /**
     * Parse the loaded file, identifying the various sections and initialising
     * any internal data structures, as needed.
     *
     * This method is pure virtual since the parsing will be dependent on the
     * actual type of executable format (i.e. ELF, Mach-O, PE/COFF)
     */
    virtual void parse() = 0;

    /**
     * Get the text section of the executable
     * @return the text section bytes
     */
    virtual const std::vector<char>& getTextSection() = 0;

    /**
     * Get the address of the text section
     * @return the address
     */
    virtual uint64_t getTextAddr() = 0;

    /**
     * Destroy the executable format
     */
    virtual ~ExecutableFormat() = default;

protected:
    std::string file;
    std::vector<char> data;
};

}
