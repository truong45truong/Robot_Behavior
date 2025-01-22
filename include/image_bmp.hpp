#ifndef __IMAGE_BMP_HPP__
#define __IMAGE_BMP_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "objects.hpp"
#include "logger.hpp"

#define Fx(x1, y1, x2, y2, x) ((y1) + ((y2) - (y1)) * ((x) - (x1)) / ((x2) - (x1)))  // y = y1 + m(x - x1) [ m = (y2 -y1) / (x2 - x1) ] 
class ImageBMP {
public:
    ImageBMP(int width_, int height_);

    void Mark(const Point& point_mark,const int& size_mark, bitmap_data::RGB_24 rgb) noexcept;

    inline void setPixel(int x, int y, bitmap_data::RGB_24 rgb) noexcept;

    void drawLine(int x1, int y1, int x2, int y2, bitmap_data::RGB_24 rgb);

    void saveBMP_RGB24(const std::string& filename);

    constexpr inline int GetWidth() const noexcept {
        return width_;
    }

    constexpr inline int GetHeigth() const noexcept {
        return height_;
    }

    std::vector<uint8_t> GetPixels() const noexcept {
        return pixels_;
    }
private:
    int width_, height_;
    bitmap_data::BMPHeader bmp_header_;
    bitmap_data::DIBHeader dib_header_;
    std::vector<uint8_t> pixels_;
};

#endif
