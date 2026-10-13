#pragma once
#include <string>

struct FileInfo
{
    std::string name;
    std::string path;
    std::uintmax_t size = 0;
};