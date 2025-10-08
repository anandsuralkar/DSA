// bmp.h
#pragma once
#include <vector>
#include <string>

namespace bmp {
    std::vector<std::vector<int>> readBMP(const std::string &filename);
    void writeBMP(const std::string &filename, const std::vector<std::vector<int>> &img);
}
