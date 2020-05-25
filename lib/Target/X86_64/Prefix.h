#pragma once

namespace tg {

/**
 * x86_64 instruction prefixes
 *
 * This enum represents all the different kinds of prefixes that
 * exist within the architecture.
 *
 * An instruction may have optional prefix(es), which act as a modifier,
 * but the overall instruction functionality is the same.
 *
 * This enumeration contains both the prefix name, as well as, its encoding
 * value defined in the ISA. This simplifies prefix detection logic by simply
 * enumerating over the possibilities in the enum and the default case indicates
 * that the instruction has no prefix.
 *
 * The values for the prefixes *do not* clash with the primary opcode values, so
 * simply looking at the first byte and checking for a match is sufficient.
 *
 * NOTES:
 *   + The BND prefix (encoded 0xf2) is not supported. Only architectures with
 *     Intel MPX support can have branch instructions annotated with this -- but
 *     this seems to be enough of an edge-case to ignore outright.
 *
 *   + Branch hints (encoded 0x2e - NT, 0x3e - T) are also not supported. These
 *     are ignored in modern architectures, so it is safe to ignore. Any branch
 *     that does have these prefixes will be mislabelled as {CS,DS}_SEG_OVERRIDE
 *
 * TODO:
 *   + Handle the REX prefix. This is different from the other prefixes in that is it
 *     used only in 64-bit mode to indicate operands are 64-bit wide. It is still yet
 *     to be determined whether that will be handled here or dealt with somewhere else.
 */
enum Prefix : unsigned char {
    // Group 1 prefixes
    LOCK =  0xf0, /* lock prefix */
    REPNZ = 0xf2, /* repeat not zero (not equal) */
    REPZ =  0xf3,  /* repeat zero (equal) */

    // Group 2 prefixes
    CS_SEG_OVERRIDE = 0x2e,
    SS_SEG_OVERRIDE = 0x36,
    DS_SEG_OVERRIDE = 0x3e,
    ES_SEG_OVERRIDE = 0x26,
    FS_SEG_OVERRIDE = 0x64,
    GS_SEG_OVERRIDE = 0x65,

    // Group 3 prefix
    OP_SIZE_OVERRIDE = 0x66,

    // Group 4 prefix
    ADDR_SIZE_OVERRIDE = 0x67,

    // Invalid prefix
    // This is used during prefix decoding to indicate that
    // the provided byte does not match any prefix
    INVALID
};

/**
 * Decode the given byte, returning the prefix it represents
 * @param byte - byte to decode
 * @return the equivalent prefix or invalid prefix
 */
Prefix decode_prefix(unsigned char byte);

}
