#include <stdint.h>
#include <byteswap.h>

#pragma pack(push, 1)
struct Bitmap_File_Header 
{
    uint16_t header_field;
    uint32_t file_size;
    uint16_t reserved_0;
    uint16_t reserved_1;
    uint32_t image_data_addr;
};

struct Bitmap_Info_Header
{
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes{1};
    uint16_t bit_count;
    uint32_t compression_type;
    uint32_t image_size;
    int32_t  x_ppm;
    int32_t  y_ppm;
    uint32_t colors_used;
    uint32_t important_colors;
};

struct Bitmap_Info_Header_V2 
{
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes{1};
    uint16_t bit_count;
    uint32_t compression_type;
    uint32_t image_size;
    int32_t  x_ppm;
    int32_t  y_ppm;
    uint32_t colors_used;
    uint32_t important_colors;
    uint16_t unit_enum;
    uint16_t reserved;
    uint16_t direction_enum;
    uint16_t halftoning_enum;
    uint32_t halftoning_param_1;
    uint32_t halftoning_param_2;
    uint32_t color_encoding_enum;
    uint32_t app_identifier;
};
#pragma pack(pop)

struct Pixel 
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};