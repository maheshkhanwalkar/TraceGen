#include "ExecutableFormat.h"
#include <sys/stat.h>
#include <fstream>

using namespace tg;

ExecutableFormat::ExecutableFormat(std::string file)
    : file(std::move(file)), data() {}

bool ExecutableFormat::read()
{
    struct stat st{};
    int res = stat(file.c_str(), &st);

    // Could not stat() the file
    if(res == -1) {
        return false;
    }

    uint64_t size = st.st_size;
    data = std::vector<char>(size);

    std::ifstream stream(file, std::ios_base::binary);
    stream.read(data.data(), size);

    bool success = !stream.fail();
    stream.close();

    return success;
}
