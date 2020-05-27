#include "Address.h"

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
    // TODO decode the ModRM and SIB to determine the required bytes
    //  needed for addressing
    (void)modRM;
    (void)SIB;

    return 0;
}
