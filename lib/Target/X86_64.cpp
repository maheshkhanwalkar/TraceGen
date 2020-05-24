#include "X86_64.h"

using namespace tg;

X86_64::X86_64() : Target(TargetType::X86_64) { }

/**
 * Parse a single instruction from the machine code
 * @param data - machine code
 * @param start - starting index
 * @return how many bytes were consumed
 */
static size_t parse_one(const std::vector<char>& data, size_t start)
{
    (void)data;
    (void)start;

    // TODO actually parse a single instruction
    return data.size();
}

void X86_64::parse(const std::vector<char>& data, uint64_t start_addr)
{
    (void)start_addr;

    for(size_t s = 0; s < data.size(); ) {
        s += parse_one(data, s);
    }
}
