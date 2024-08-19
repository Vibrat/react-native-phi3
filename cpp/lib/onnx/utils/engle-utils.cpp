#include <filesystem>
#include <iostream>
#include "engle_utils.h"

namespace EngleUtils
{
    bool isDirectory(const std::string &path)
    {
        return std::filesystem::exists(path) && std::filesystem::is_directory(path);
    }

    bool isFile(const std::string& path)
    {
        return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
    }
}
