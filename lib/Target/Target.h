#pragma once
#include "Type.h"
#include <vector>

namespace tg {

/**
 * Target
 *
 * This class encapsulates a generic target (architecture) and the
 * associated features that go along with it.
 *
 * The specific subclasses of Target implement the required functionality
 * to perform disassembly and other processing on raw machine code that has
 * been extracted from an executable source.
 *
 * These processes will return a machine-independent instruction representation,
 * which allows for simplified processing for the TraceGen front-end, which can
 * simply used to parsed information to perform the high-level instruction trace
 * setup needed to capture the traces once execution is completed.
 */
class Target {
public:
    /**
     * Create a new target
     * @param type - target type
     */
    explicit Target(TargetType type);

    /**
     * Get the type of the target
     * @return the type
     */
    TargetType getType();

    /**
     * Parse the given machine code
     *
     * TODO change the method return signature -- this will eventually return
     *  a vector of instructions (or something like that...)
     *
     * @param data - raw machine code bytes
     * @param start_addr - starting address of the first byte
     */
    virtual void parse(const std::vector<char>& data, uint64_t start_addr) = 0;

private:
    TargetType type;
};

}
