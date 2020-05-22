#include "ExecutableFormat.h"
#include <fstream>

using namespace tg;

ExecutableFormat::ExecutableFormat(std::string file)
    : file(std::move(file)), data() {}

bool ExecutableFormat::read()
{
    std::ifstream stream(file, std::ios_base::binary);
    stream.seekg(std::ios::end);

    uint64_t size = stream.tellg();
    stream.seekg(std::ios::beg);

    data = std::vector<char>(size);
    stream.read(data.data(), size);

    // Status of the read
    bool res = !stream.fail();

    stream.close();
    return res;
}
