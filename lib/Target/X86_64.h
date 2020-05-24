#pragma once
#include "Target.h"

namespace tg {

class X86_64: public Target {
public:
    /**
     * Create a new x86_64 target
     *
     * This initialises the underlying target with the proper X86_64
     * target type for identification purposes.
     */
    explicit X86_64();

    /**
     * Parse the given x86_64 machine code
     * @param data - machine code to parse
     * @param start_addr - starting virtual address of the first instruction
     */
    void parse(const std::vector<char>& data, uint64_t start_addr) override;
};

}
