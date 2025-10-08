// bmp.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>
using namespace std;

namespace bmp {

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{54};
};

struct BMPInfoHeader {
    uint32_t size{40};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{24};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};
#pragma pack(pop)

// Declarations (can go to header if you want)
vector<vector<int>> readBMP(const string &filename);
void writeBMP(const string &filename, const vector<vector<int>> &img);


// ---------- Implementation ----------
vector<vector<int>> readBMP(const string &filename) {
    ifstream f(filename, ios::binary);
    if (!f) throw runtime_error("Cannot open file");

    BMPHeader header;
    BMPInfoHeader info;
    f.read(reinterpret_cast<char*>(&header), sizeof(header));
    f.read(reinterpret_cast<char*>(&info), sizeof(info));

    if (info.bit_count != 24 || info.compression != 0)
        throw runtime_error("Only 24-bit uncompressed BMP supported");

    int width = info.width;
    int height = abs(info.height);
    int row_padded = (width * 3 + 3) & (~3);

    vector<vector<int>> img(height, vector<int>(width));
    vector<uint8_t> row(row_padded);

    for (int i = height - 1; i >= 0; --i) {
        f.read(reinterpret_cast<char*>(row.data()), row_padded);
        for (int j = 0; j < width; ++j) {
            uint8_t b = row[j * 3];
            uint8_t g = row[j * 3 + 1];
            uint8_t r = row[j * 3 + 2];
            img[i][j] = (r << 16) | (g << 8) | b;
        }
    }
    return img;
}

void writeBMP(const string &filename, const vector<vector<int>> &img) {
    int height = img.size();
    int width = img[0].size();

    BMPHeader header;
    BMPInfoHeader info;
    info.width = width;
    info.height = height;
    int row_padded = (width * 3 + 3) & (~3);
    info.size_image = row_padded * height;
    header.file_size = info.size_image + sizeof(header) + sizeof(info);

    ofstream f(filename, ios::binary);
    f.write(reinterpret_cast<char*>(&header), sizeof(header));
    f.write(reinterpret_cast<char*>(&info), sizeof(info));

    vector<uint8_t> row(row_padded);
    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            int rgb = img[i][j];
            row[j * 3 + 0] = rgb & 0xFF;
            row[j * 3 + 1] = (rgb >> 8) & 0xFF;
            row[j * 3 + 2] = (rgb >> 16) & 0xFF;
        }
        f.write(reinterpret_cast<char*>(row.data()), row_padded);
    }
}

} // namespace bmp
