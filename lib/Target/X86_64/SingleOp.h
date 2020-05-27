#pragma once
#include <vector>
#include "Prefix.h"

namespace tg {

class SingleOpDecoder {
public:
    /**
     * Decode a single opcode instruction
     * @param prefixes - instruction prefixes
     * @param rex - REX prefix
     * @param data - machine code
     * @param start - starting byte of the opcode (after all prefixes, if any)
     */
    static void decode(const std::vector<Prefix>& prefixes, RexPrefix rex,
            const std::vector<char>& data, size_t start);

};

}
