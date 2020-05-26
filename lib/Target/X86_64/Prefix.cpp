#include "Prefix.h"

namespace tg {

Prefix PrefixDecoder::decode_prefix(unsigned char byte)
{
    auto raw = static_cast<Prefix>(byte);

    switch (raw) {
        case Prefix::LOCK:
        case Prefix::REPNZ:
        case Prefix::REPZ:
        case Prefix::CS_SEG_OVERRIDE:
        case Prefix::SS_SEG_OVERRIDE:
        case Prefix::DS_SEG_OVERRIDE:
        case Prefix::ES_SEG_OVERRIDE:
        case Prefix::FS_SEG_OVERRIDE:
        case Prefix::GS_SEG_OVERRIDE:
        case Prefix::OP_SIZE_OVERRIDE:
        case Prefix::ADDR_SIZE_OVERRIDE:
            return raw;
        default:
            return Prefix::NONE;
    }
}

RexPrefix PrefixDecoder::decode_rex(unsigned char byte)
{
    /**
     * Not a valid REX prefix -- ignore
     *
     * The decoding for REX prefixes is a lot easier than other prefixes since
     * it has a contiguous value space assigned to it.
     *
     * Legacy prefixes are messy since there are many gaps between the values,
     * requiring a more cumbersome matching process -- see decode_prefix() above.
     */
    if(byte < 0x40 || byte > 0x4f) {
        return RexPrefix::NONE;
    }

    // Values already correspond -- so just perform a simple static cast
    return static_cast<RexPrefix>(byte);
}

}
