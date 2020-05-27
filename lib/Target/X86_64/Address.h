#pragma once
#include <cstddef>

namespace tg {

class AddressDecoder {
public:
    /**
     * Check whether the ModRM specifies whether a SIB byte is
     * required for the given instruction
     *
     * @param modRM - byte representing the ModRM section
     * @return true if SIB is required, false otherwise
     */
    static bool hasSIB(unsigned char modRM);

    /**
     * Decode the addressing mode byte(s) for an instruction
     * @param modRM - byte representing the ModRM section
     * @param SIB - byte representing the SIB section
     * @return the number of bytes needed for addressing purposes
     */
    static size_t decode(unsigned char modRM, unsigned char SIB);

};

}
