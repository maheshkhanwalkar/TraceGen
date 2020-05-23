#pragma once
#include <vector>

namespace tg {

/**
 * Executable metadata
 *
 * This class encapsulates all the necessary metadata extracted from
 * a loaded and parsed executable file.
 *
 * The specific executable format details are handled by one of the subclasses
 * of ExecutableFormat (i.e. MachO), so this class only a contains raw,
 * format-independent data representation.
 */
class Metadata {
public:
    /**
     * Construct a metadata object
     * @param text - raw bytes of the text section
     * @param text_addr - starting address of the text section
     */
    explicit Metadata(std::vector<char>&& text, uint64_t text_addr);

    /**
     * Get the text section
     * @return the bytes of the section
     */
    const std::vector<char>& getTextSection() const;

    /**
     * Get the starting address of the text section
     * @return the address
     */
    uint64_t getTextAddr() const;

private:
    std::vector<char> text;
    uint64_t v_addr;
};


}
