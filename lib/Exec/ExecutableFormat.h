#pragma once

/**
 * Executable Format
 *
 * This top-level class encapsulates the common features of various executable
 * formats that exist.
 *
 * Every format will have the same general ``broad'' classes of executable sections:
 *    + Text section (executable code)
 *    + Data section (for initialised data)
 *    + BSS section (uninitialised data)
 *    + Rodata section (read-only data)
 *
 * In addition, each section is essentially just a contiguous stream of bytes which
 * generally have an address associated with them (virtual and/or physical)
 *
 * TraceGen only needs a small set of executable format parsing features, namely,
 * extracting the text section for processing, so that is the only feature that is
 * exposed (and implemented) in this library.
 */
class ExecutableFormat {

};
