#include "Metadata.h"

using namespace tg;

Metadata::Metadata(std::vector<char>&& text, uint64_t text_addr)
    : text(std::move(text)), v_addr(text_addr) { }

const std::vector<char>& Metadata::getTextSection() const
{
    return text;
}

uint64_t Metadata::getTextAddr() const
{
    return v_addr;
}
