#include <stdint.h>
#include <byteswap.h>

#pragma pack(push, 1)
struct BMPHeader_24
{
    // File header (14 bytes)
    uint16_t header_field;
    uint32_t file_size;
    uint16_t reserved_0;
    uint16_t reserved_1;
    uint32_t image_data_offset;

    // DIB Heeader (40 bytes)
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
#pragma pack(pop)
