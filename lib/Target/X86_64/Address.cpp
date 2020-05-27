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

size_t AddressDecoder::decode(unsigned char modRM, unsigned char SIB)
{
    if(hasSIB(modRM)) {
        // TODO decode SIB
        (void)SIB;
        return 0;
    }
    else {
        /**
         * There is no SIB for this instruction
         * The data in the 'SIB' variable contains random junk
         */

        unsigned char mod = modRM >> 6U;
        unsigned char rm = modRM & 0x7U;

        switch (mod) {
            case 0x0:
                // disp32 when mod=00 and rm=101 (no disp otherwise)
                return (rm == 0x5) ? 4 : 0;
            case 0x1:
                // disp8 regardless of rm value
                return 1;
            case 0x2:
                // disp32 regardless of rm value
                return 4;
            case 0x3:
                // no disp value
                return 0;
            default:
                // This shouldn't be possible -- since the mask should only
                // allow for values 0-3
                throw std::runtime_error("bad value for ModRM");
        }
    }
}
