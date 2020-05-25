#include "X86_64.h"
#include "Prefix.h"

using namespace tg;

/**
 * Decode the prefixes of the given instruction
 * @param data - machine code
 * @param start - starting index of the current instruction
 * @return a vector containing all the prefixes
 */
static std::vector<Prefix> decode_prefixes(const std::vector<char>& data, size_t start)
{
    std::vector<Prefix> prefixes;

    while(start < data.size()) {
        char byte = data.at(start);
        Prefix equiv = decode_prefix(byte);

        // Not a prefix -- all prefixes have been decoded
        if(equiv == Prefix::INVALID) {
            break;
        }

        prefixes.push_back(equiv);
    }

    return prefixes;
}

/**
 * Decode a single instruction from the machine code
 * @param data - machine code
 * @param start - starting index
 * @param text_start - starting address of the first byte of machine code
 * @return how many bytes were consumed
 */
static size_t decode_one(const std::vector<char>& data, size_t start, uint64_t text_start)
{
    size_t consumed = 0;

    // Starting address of the instruction
    uint64_t i_addr = text_start + start;
    (void)i_addr;

    // Decode all the legacy prefixes
    std::vector<Prefix> prefixes = decode_prefixes(data, start);

    consumed += prefixes.size();
    start += consumed;

    // Decode the REX prefix, if it exists
    RexPrefix rex = decode_rex(data.at(start));

    if(rex != RexPrefix::INVALID) {
        // Valid REX -- so one byte was consumed
        consumed += 1;
        start += 1;
    }

    return consumed;
}

X86_64::X86_64() : Target(TargetType::X86_64) { }

void X86_64::decode(const std::vector<char>& data, uint64_t start_addr)
{
    for(size_t s = 0; s < data.size(); ) {
        s += decode_one(data, s, start_addr);
    }
}
