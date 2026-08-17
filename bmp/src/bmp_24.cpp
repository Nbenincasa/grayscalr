#include "../include/bmp_24.h"

BMP_24::BMP_24(const std::string& inputPath_arg, const std::string& outputPath_arg)
: inputPath{inputPath_arg},
  outputPath{outputPath_arg}
{
}

BMP_24::~BMP_24()
{
}


bool BMP_24::covertToGrayscale()
{
    // Open input file
    std::ifstream infile(this->inputPath, std::ios::binary);

    // Ensure open file to avoid nullptr exceptions
    if(!infile)
    {
        std::cerr << "ERROR: Failed to open input file.\n";
        return false;
    }

    // Read header data into struct
    infile.read(reinterpret_cast<char*>(&this->header), sizeof(header));

    // Check for supported BMP format
    if( this->header.header_field != 0x4D42 || this->header.bit_count != 24 || this->header.compression_type != 0 )
    {
        std::cerr << "ERROR: Unsupported BMP format. Uncompressed 24-bit BMP only.\n";
        std::cout << this->header.header_field << "\n";
        std::cout << this->header.bit_count << "\n";
        std::cout << this->header.compression_type << "\n";
    }

    // Header can be stored as negative for top-down data storage
    int height = std::abs(this->header.height);
    
    // Open output file
    std::ofstream outfile(this->outputPath, std::ios::binary);
    
    // Ensure open file to avoid nullptr exceptions
    if(!outfile)
    {
        std::cerr << "ERROR: Failed to open input file.\n";
        return false;
    }
    
    // Write header to output file first
    outfile.write(reinterpret_cast<char*>(&this->header), sizeof(header));
    
    // Jump to pixel data offset
    infile.seekg(this->header.image_data_offset, std::ios::beg);
    
    // BMP Rows are stored in multiples of 4 bytes, calculate row info and create a buffer for rows
    int rowstride{ this->header.width * 3 };
    int padding{ (4 - (rowstride % 4)) % 4 };
    int row_size = rowstride + padding;
    std::vector<uint8_t> row_buffer(row_size);

    // Cycle through rows
    for(int y = 0; y < height; y++ )
    {
        // Read the row data into a buffer
        infile.read(reinterpret_cast<char*>(row_buffer.data()), row_size);

        for(int x = 0; x < this->header.width; x++)
        {
            // Create pixel offset to read pixel data
            int pixel_offset = x * 3;

            // Get values
            uint8_t blue  = row_buffer[pixel_offset];
            uint8_t green = row_buffer[pixel_offset + 1 ];
            uint8_t red   = row_buffer[pixel_offset + 2 ];

            // Make gray
            uint8_t gray = static_cast<uint8_t>(blue * 0.0722 + green * 0.7152 + red * 0.2126);

            // Set gray to pixel value
            row_buffer[pixel_offset] = gray;
            row_buffer[pixel_offset + 1 ] = gray;
            row_buffer[pixel_offset + 2 ] = gray;;
        }

        // Write row by row
        outfile.write(reinterpret_cast<const char*>(row_buffer.data()), row_size);
    }
     
    // Notify success and close files before returning.
    std::cout << "Success: Grayscale image saved to " << outputPath << "\n";
    infile.close();
    outfile.close();
    return true;
}