#include "Address.h"
#include <stdexcept>

using namespace tg;

bool AddressDecoder::hasSIB(unsigned char modRM)
{
    unsigned char mod = modRM >> 6U;
    unsigned char rm = modRM & 0x7U;

    // mod=00,01,10 and rm=100 then SIB is present
    return (mod != 0x3) && rm == 0x4;
}

/**
 * Decode the SIB byte to determine required addressing bytes
 * @param mod - bits representing the mod
 * @param SIB - byte representing the SIB
 * @return the number of bytes required for addressing
 */
static inline size_t decode_SIB(unsigned char mod, unsigned char SIB)
{
    unsigned char base = SIB & 0x7U;

    if(base == 0x05) {
        switch(mod) {
            case 0x0:
            case 0x2:
                // disp32
                return 4;
            case 0x1:
                // disp8
                return 1;
            default:
                // This shouldn't be possible -- decode_SIB should only
                // be called when mod \in [0,2]
                throw std::runtime_error("bad value for mod");
        }

    } else {
        return 0;
    }
}

size_t AddressDecoder::decode(unsigned char modRM, unsigned char SIB)
{
    size_t disp;

    unsigned char mod = modRM >> 6U;
    unsigned char rm = modRM & 0x7U;

    switch (mod) {
        case 0x0:
            // disp32 when mod=00 and rm=101 (no disp otherwise)
            disp = (rm == 0x5) ? 4 : 0;
            break;
        case 0x1:
            // disp8 regardless of rm value
            disp = 1;
            break;
        case 0x2:
            // disp32 regardless of rm value
            disp = 4;
            break;
        case 0x3:
            // no disp value
            disp = 0;
            break;
        default:
            // This shouldn't be possible -- since the mask should only
            // allow for values 0-3
            throw std::runtime_error("bad value for ModRM");
    }

    if(hasSIB(modRM)) {
        return disp + decode_SIB(mod, SIB);
    } else {
        return disp;
    }
}
