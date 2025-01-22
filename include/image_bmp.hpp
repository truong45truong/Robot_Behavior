#ifndef __IMAGE_BMP_HPP__
#define __IMAGE_BMP_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "objects.hpp"

class Image {
public:
    Image(int width, int height) : width(width), height(height) {
        pixels.resize(width * height * 3, 255); // Initialize with white pixels
    }

    void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
        if (x < 0 || x >= width || y < 0 || y >= height) return; // Out of bounds
        int index = (y * width + x) * 3;
        pixels[index] = b;   // BMP stores color as BGR
        pixels[index + 1] = g;
        pixels[index + 2] = r;
    }

    void saveBMP(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not write to file " << filename << std::endl;
            return;
        }

        // BMP Header
        uint32_t fileSize = 54 + pixels.size();
        uint32_t dataOffset = 54;
        uint32_t headerSize = 40;
        uint16_t planes = 1;
        uint16_t bitsPerPixel = 24;
        uint32_t compression = 0;
        uint32_t imageSize = pixels.size();
        uint32_t ppm = 2835; // 72 DPI

        file.put('B').put('M'); // Magic bytes
        file.write(reinterpret_cast<char*>(&fileSize), 4);
        file.write("\0\0\0\0", 4);
        file.write(reinterpret_cast<char*>(&dataOffset), 4);

        // DIB Header
        file.write(reinterpret_cast<char*>(&headerSize), 4);
        file.write(reinterpret_cast<char*>(&width), 4);
        file.write(reinterpret_cast<char*>(&height), 4);
        file.write(reinterpret_cast<char*>(&planes), 2);
        file.write(reinterpret_cast<char*>(&bitsPerPixel), 2);
        file.write(reinterpret_cast<char*>(&compression), 4);
        file.write(reinterpret_cast<char*>(&imageSize), 4);
        file.write(reinterpret_cast<char*>(&ppm), 4);
        file.write(reinterpret_cast<char*>(&ppm), 4);
        file.write("\0\0\0\0", 4);
        file.write("\0\0\0\0", 4);

        // Pixel Data
        for (int y = height - 1; y >= 0; --y) { // BMP stores rows bottom to top
            file.write(reinterpret_cast<char*>(&pixels[y * width * 3]), width * 3);
            // Pad rows to multiple of 4 bytes
            for (int p = 0; p < (4 - (width * 3) % 4) % 4; ++p) {
                file.put(0);
            }
        }

        file.close();
        std::cout << "Image saved to " << filename << std::endl;
    }

private:
    int width, height;
    std::vector<uint8_t> pixels;

};


#endif
