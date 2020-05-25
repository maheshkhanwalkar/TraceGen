#include "Prefix.h"

namespace tg {

Prefix decode_prefix(unsigned char byte)
{
    switch (byte) {
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
            return static_cast<Prefix>(byte);
        default:
            return Prefix::INVALID;
    }
}

}
