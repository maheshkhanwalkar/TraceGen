#include "ExecutableFormat.h"
#include <sys/stat.h>
#include <fstream>

using namespace tg;

void ExecutableFormat::read(const std::string& file)
{
    struct stat st{};
    int res = stat(file.c_str(), &st);

    // Could not stat() the file
    if(res == -1) {
        throw std::runtime_error("could not stat() file\n");
    }

    uint64_t size = st.st_size;
    data = std::vector<char>(size);

    std::ifstream stream(file, std::ios_base::binary);
    stream.read(data.data(), size);

    bool success = !stream.fail();
    stream.close();

    if(!success) {
        throw std::runtime_error("could not read the file\n");
    }
}
