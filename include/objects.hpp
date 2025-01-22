#ifndef __DATA_CONTAINER_HPP
#define __DATA_CONTAINER_HPP
#include <iostream>
#include <vector>

struct Point {
    int x = 0;
    int y = 0;
};

struct GridMap {
    int width = 0;
    int height = 0;
    std::vector<Point> point_marks;
};

namespace bitmap_data {
    struct BMPHeader {
        uint16_t bf_signature = 0x4D42; // "BM"
        uint32_t bf_size = 0x00000046; //Typical offset for a 24-bit BMP [ 70 - 24-bit BMP ] [ 122 - 32-bit BMP ]
        uint16_t bf_reserved_1 = 0 ; // Reserved: Must be 0
        uint16_t bf_reserved_2 = 0; // Reserved: Must be 0
        uint32_t bf_file_offset_to_pixels_array = 0x00000036 // Typical offset for a 24-bit BMP  [ 54 - 24-bit BMP - RGB24 ] [ 122 - 32-bit BMP - ARGB32 ] ; 
    };

    struct DIBHeader {
        uint32_t bv5_header_size = 0x00000028; // [ 40 bytes - 24-bit BMP - RGB24 ] [ 108 bytes - 32-bit BMP - ARGB32 ];
        uint32_t bv5_img_width = 0; // set up later
        uint32_t bv5_img_height = 0; // set up later
        uint16_t bv5_planes = 0x0001; // [ 1 plane for 24-bit and 32-bit BMP] 
        uint16_t bv5_bits_per_pixel = 0x0018; // [ 24 - 24-bit BMP ] [ 32 - 32-bit BMP ] 
        uint32_t bv5_compression = 0; // [ 0 - 24-bit BMP ] [ 3 - 32-bit BMP ]
        uint32_t bv5_img_size = 0; // set up later
        uint32_t bv5_x_pixel_per_meter = 0x00000B13; // 2835 pixels/metre horizontal for 24-bit and 32-bit BMP
        uint32_t bv5_y_pixel_per_meter = 0x00000B13; // 2835 pixels/metre vertical for 24-bit and 32-bit BMP
        uint32_t bv5_color_in_color_table = 0;
        uint32_t bv5_important_color_cout = 0;
        uint32_t bv5_red_channel_bitmask = 0;
        uint32_t bv5_green_channel_bitmask = 0;
        uint32_t bv5_blue_channel_bitmask = 0;
        uint32_t bv5_alpha_channel_bitmask = 0;
        uint32_t bv5_color_space_type = 0;
        uint32_t bv5_color_space_endpoints = 0;
        uint32_t bv5_gamma_for_red_channel = 0;
        uint32_t bv5_gamma_for_green_channel = 0;
        uint32_t bv5_gamma_for_blue_channel = 0;
        uint32_t bv5_intent = 0;
        uint32_t bv5_icc_profile_data = 0;
        uint32_t bv5_icc_profile_size = 0;
        uint32_t bv5_reserved = 0;
    };
};

#endif
