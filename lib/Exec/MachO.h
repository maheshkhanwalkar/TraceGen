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
     * Construct an MachO parser
     */
    explicit MachO() = default;

    /**
     * Parse the provided MachO file
     *
     * The __text section (from __TEXT segment) and the starting virtual
     * address are extracted and returned within a metadata object.
     */
     Metadata parse(const std::string& file) override;
};

}
