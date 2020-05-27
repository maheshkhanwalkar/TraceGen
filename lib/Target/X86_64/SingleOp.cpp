#include "SingleOp.h"

using namespace tg;

/**
 * Find the given prefix in the provided vector
 * @param prefixes - vector of decoded prefixes for the given instruction
 * @param which - prefix to match against
 * @return true if there is a match, false otherwise
 */
static bool find_prefix(const std::vector<Prefix>& prefixes, Prefix which)
{
    for(const Prefix& curr : prefixes) {
        if(curr == which) {
            return true;
        }
    }

    return false;
}

void SingleOpDecoder::decode(const std::vector<Prefix>& prefixes, tg::RexPrefix rex,
        const std::vector<char>& data, size_t start)
{
    unsigned char opcode __unused = data.at(start);

    bool has_rex __unused = rex != RexPrefix::NONE;
    bool has_addr_override __unused = find_prefix(prefixes, Prefix::ADDR_SIZE_OVERRIDE);
    bool has_op_override __unused = find_prefix(prefixes, Prefix::OP_SIZE_OVERRIDE);
    bool has_mod_rm __unused = false;

    // TODO examine the first byte to determine what instruction it is
    // TODO use the variables above and remove __unused specifier (used to placate the compiler...)
}
