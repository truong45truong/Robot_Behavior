#ifndef __IMAGE_BMP_CPP__
#define __IMAGE_BMP_CPP__

#include "../include/image_bmp.hpp"

ImageBMP::ImageBMP(int width_, int height_) : width_(width_), height_(height_) {
    pixels_.resize(width_ * height_ * 3, 255); // Initialize with white pixels_
            
    // Initialize DIBHeader
    dib_header_.bv5_img_width = width_;
    dib_header_.bv5_img_height = height_;
    dib_header_.bv5_img_size = pixels_.size();
}

void ImageBMP::Mark(const Point& point_mark,const int& size_mark, bitmap_data::RGB_24 rgb) noexcept {
    drawLine(point_mark.x, point_mark.y - size_mark, point_mark.x, point_mark.y + size_mark, rgb);
    drawLine(point_mark.x - size_mark, point_mark.y, point_mark.x + size_mark, point_mark.y,rgb);
}

inline void ImageBMP::setPixel(int x, int y, bitmap_data::RGB_24 rgb) noexcept {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return; // Out of bounds
    int index = (y * width_ + x) * 3;
    pixels_[index] = rgb.b;   // BMP stores color as BGR
    pixels_[index + 1] = rgb.g;
    pixels_[index + 2] = rgb.r;
}

void ImageBMP::drawLine(int x1, int y1, int x2, int y2, bitmap_data::RGB_24 rgb) {
    if (x1 == x2 && y1 == y2) {
        // Case 3: Single point
        setPixel(x1, y1, rgb);
    } else if (x1 == x2) {
        // Case 2: Vertical line
        int startY = std::min(y1, y2);
        int endY = std::max(y1, y2);
        for (int y = startY; y <= endY; ++y) {
            setPixel(x1, y, rgb);
        }
    } else {
        // Case 1: General case
        int startX = std::min(x1, x2);
        int endX = std::max(x1, x2);
        for (int x = startX; x <= endX; ++x) {
            setPixel(x, Fx(x1, y1, x2, y2, x), rgb);
        }
    }
}

void ImageBMP::saveBMP_RGB24(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        LOG_ERROR(("Could not write to Image BMP " +  std::string(filename)).c_str());
        return;
    }

    // BMP Header
    file.write(reinterpret_cast<char*>(&bmp_header_.bf_signature), 2); // Magic bytes for BMP ("BM")
    file.write(reinterpret_cast<char*>(&bmp_header_.bf_size), 4); // File size
    file.write(reinterpret_cast<char*>(&bmp_header_.bf_reserved_1), 2); // Reserved field (set to 0)
    file.write(reinterpret_cast<char*>(&bmp_header_.bf_reserved_2), 2); // Reserved field (set to 0)
    file.write(reinterpret_cast<char*>(&bmp_header_.bf_file_offset_to_pixels_array), 4); // Offset to pixel data

    // DIB Header
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_header_size), 4); // DIB header size
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_img_width), 4); // ImageBMP width_
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_img_height), 4); // ImageBMP height_
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_planes), 2); // Planes
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_bits_per_pixel), 2); // Bits per pixel
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_compression), 4); // Compression
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_img_size), 4); // ImageBMP size
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_x_pixel_per_meter), 4); // X pixels_ per meter
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_y_pixel_per_meter), 4); // Y pixels_ per meter
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_color_in_color_table), 4); // Colors used (usually 0)
    file.write(reinterpret_cast<char*>(&dib_header_.bv5_important_color_cout), 4); // Important colors (usually 0)

    // Pixel Data
    for (int y = height_ - 1; y >= 0; --y) { // BMP stores rows bottom to top
        file.write(reinterpret_cast<char*>(&pixels_[y * width_ * 3]), width_ * 3);
        // Pad rows to multiple of 4 bytes
        for (int p = 0; p < (4 - (width_ * 3) % 4) % 4; ++p) {
            file.put(0);
        }
    }

    file.close();
    LOG_INFO("ImageBMP saved");
}

#endif