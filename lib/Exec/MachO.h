#pragma once
#include "ExecutableFormat.h"

namespace tg {

/**
 * MachO executable format
 *
 * This format is used on macOS systems for any and all kinds of executable code,
 * that is, object code, executables, and libraries [static, dynamic]
 *
 * This class implements the ``MachO-specific'' parsing needed to identify the various
 * sections within the provided executable.
 */
class MachO : public ExecutableFormat {

public:
    /**
     * Construct an MachO object with the provided file as the underlying
     * data to process.
     *
     * @param file - underlying file to process
     */
    explicit MachO(std::string file);

    /**
     * Parse the MachO file
     */
    void parse() override;

    /**
     * Get the __text section (from __TEXT segment)
     * @return the bytes of the section
     */
    const std::vector<char> & getTextSection() override;

    /**
     * Get the virtual address of the __text section
     * @return the starting virtual address
     */
    uint64_t getTextAddr() override;

private:
    std::vector<char> text;
    uint64_t v_addr;

};

}
