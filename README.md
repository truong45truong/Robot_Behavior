# ROBOT

## Structure project

```
Project/
    ├── include/ 
        ├── image_bmp.hpp  # define object image bitmap
        ├── loggers.hpp    # define Macro log
        ├── objects.hpp    # define all objects used in the project
        ├── robot.hpp      
        ├── utils.hpp      # define helper function
    ├── src/  
        ├── image_bmp.cpp
        ├── robot.cpp
        ├── main.cpp
    ├── README.md   # Documentation

```

## Bit Map file formart (Document [Wikipedia.org](https://en.wikipedia.org/wiki/BMP_file_format))
```
[ BITMAPFILEHEADER - Bitmap File Header ]
[ BITMAPV5HEADER - DIB Header]
[ Color Table]
[ Image Data PixelArray]
[ ICC Color Profile ]
```

#### Design struct and class for RGB-24

```
struct BMPHeader {
        uint16_t bf_signature = 0x4D42; // "BM"
        uint32_t bf_size = 0x00000046; //Typical offset for a 24-bit BMP [ 70 - 24-bit BMP ] [ 122 - 32-bit BMP ]
        uint16_t bf_reserved_1 = 0 ; // Reserved: Must be 0
        uint16_t bf_reserved_2 = 0; // Reserved: Must be 0
        uint32_t bf_file_offset_to_pixels_array = 0x00000036; // Typical offset for a 24-bit BMP  [ 54 - 24-bit BMP - RGB24 ] [ 122 - 32-bit BMP - ARGB32 ] ; 
    };

```
```
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
        ...
    };
```
```
class ImageBMP {
    ...
    ...
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<uint8_t> pixels_;
    ...
}
```

## Problem solving algorithm

#### Robot in A(x,y) move_to || line_to B(x,y).

```
  _________________________________________   
 A(x,y )                              B(x,y)

 if(A_x == B_x){
    F(x) = x // F(X) in range [A_y : B_y]
 }else{
                                         B_y - A_y
    F(x) = B_y + m( x -A_x) // with m = ------------
                                         B_x - A_x
 }        
                       
```

#### Mark the path the robot will take 
##### Move|Line to C(x,y) E F(x)
Move_To(1,1)

```
---------------------------------
| Move  |       |       |       |
| (1,1) |       |       |       |
---------------------------------
|       | ROBOT |       |       |
|       |       |       |       |
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
Not Mark
```


Line_To(3,3)

```
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
|       |Line to|       |       |
|       |A(3,3) |       |       |
---------------------------------
|       |       |  Mark |       |
|       |       |       |       |
---------------------------------
|       |       |       | Mark  |
|       |       |       |B(3,3) |
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
Mark (1,1) (2,2) (3,3)  E F(x) = B_y + m( x -A_x)


```

##### Move|Line to C(x,y) not E F(x)

```
---------------------------------
|       |       |       |       |
|       |       |       |       |
---------------------------------
|       | ROBOT |       |       |
|       | (1,1) |       |       |
---------------------------------
|       |  A_1  |       |       |
|       |       |       |       |
---------------------------------
|       |  A_2  |       |       |
|  A_3  |       |       |       |
---------------------------------
|D(0,4) |       |       |       |
|       |       |       |       |
---------------------------------
```
Robot from  line_to  D(0,4)

A_1 , A_2, A_3 not E F(x)

==> A_1, A_2, A_3 is the shortest path to D(0,4) it has the shortest distance to the line passing through two points AB 

```
double DistanceToLine(const Point& point_0, const Point& point_1, const Point& point_2){
    double A = point_2.y - point_1.y;
    double B = point_1.x - point_2.x;
    double C = point_2.x*point_1.y - point_1.x*point_2.y;

    return std::abs(A * point_0.x + B * point_0.y + C) / std::sqrt(A * A + B * B);
}
```

# Run 

```
chmod +x ./run.sh
./run.sh
```