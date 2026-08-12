#include "../include/bmp_v1.h"

BMP_V1::BMP_V1(std::ifstream& infile_arg, std::fstream& outfile_arg)
: infile{infile_arg},
  outfile{outfile_arg}
{
}

BMP_V1::~BMP_V1()
{
}

void BMP_V1::initialize()
{
    
    this->initializeFileHeader();
    this->initializeInfoHeader();
}

void BMP_V1::initializeFileHeader()
{
    // Populate File Header struct
    // Read from file using known file header size (14 bytes)
    this->infile.read(reinterpret_cast<char*>(&this->file_header), sizeof(file_header));

    // Reset file stream
    this->infile.clear();
    this->infile.seekg(0, std::ios::beg);
}

void BMP_V1::initializeInfoHeader()
{
    // Populate Bitmap Info Header struct
    // Move to known offset for info header(14) and read size to determine bmp header type
    this->infile.seekg(14, std::ios::beg);
    uint32_t size_check;
    this->infile.read(reinterpret_cast<char*>(&size_check), sizeof(size_check));
    
    if( size_check == 40)
    {
        // Header size 40 found, populate Bitmap_Info_Header
        std::cout << "Bitmap Info Header V1 detected, populating bitmap info header...\n";
        
        // Move file pointer back to offset 14
        this->infile.seekg(14, std::ios::beg);

        // Read bitmap info header into struct
        this->infile.read(reinterpret_cast<char*>(&this->info_header), sizeof(info_header));

        std::cout << info_header.bit_count << " Bits per pixel.\n";
    } 

    else
    {
        std::cerr << "Incorrect header size. Expected 40, found " << size_check << "\n";
    }

    // Reset file stream
    this->infile.clear();
    this->infile.seekg(0, std::ios::beg);
}

void BMP_V1::makeGrayscale()
{
    switch(this->info_header.bit_count) 
    {
        case 24:
            this->grayscale24Bit();
    }

}

void BMP_V1::grayscale24Bit()
{

    // Handle reverse order case with abs()
    int32_t  height{std::abs(this->info_header.height)};

    // 3 bytes per pixel so rowstride equals pixel width*3
    int32_t  rowStride{this->info_header.width * 3};

    // Get row padding using rowstride
    uint32_t padding{ (4 - (rowStride % 4)) % 4 };

    // Initialize pixel array object with header information
    std::vector<std::vector<Pixel>> pixelGrid(height, std::vector<Pixel>(this->info_header.width));

    // Move to file stream position to pixel array address before reading pixel data
    this->infile.seekg(this->file_header.image_data_addr, std::ios::beg);

    // Read row by row
    for(int y = 0; y < height; y++ )
    {
        // Handle bottom to top case
        int targetRow = (info_header.height > 0) ? (height - 1 - y) : y;

        // Read each pixel into grid and adjust values
        for(int x = 0; x < this->info_header.width; x++)
        {
            // Get pixel data from file and read into pixel struct for easy modification
            Pixel pixel;
            this->infile.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));

            // Change RB values using standard luminosity formula
            double gray = pixel.b * 0.0722 + pixel.g * 0.7152 + pixel.r * 0.2126;
            pixel.b = static_cast<uint8_t>(gray);
            pixel.g = static_cast<uint8_t>(gray);
            pixel.r = static_cast<uint8_t>(gray);

            // Write updated values to pixelGrid
            pixelGrid[targetRow][x] = pixel;
        }

        // Skip padding bytes
        infile.seekg(padding, std::ios::cur);
    }

    // Write grayscale image to output file upon completion
    this->writeGrayScaleToOutputFile(pixelGrid);
     
}

void BMP_V1::writeGrayScaleToOutputFile(std::vector<std::vector<Pixel>> pixelGrid)
{
    // Move output file header to pixel array address
     this->outfile.seekp(this->file_header.image_data_addr, std::ios::beg);

    int32_t height = pixelGrid.size();
    int32_t width = pixelGrid[0].size();
    int32_t rowStride = width * 3;
    uint32_t padding = (4 - (rowStride % 4)) % 4;

    // Create an array of 0s to use as padding padding bytes
    char paddingBytes[3] = {0, 0, 0};

    // BMP files expect data written bottom-to-top layout sequence
    for (int y = 0; y < height; ++y)
    {

        // If your input header was positive, write out starting from the last array row
        int sourceRow = (this->info_header.height > 0) ? (height - 1 - y) : y;

        // Fix: Write the raw buffer inside the nested elements, not the wrapper objects
        this->outfile.write(reinterpret_cast<char*>(pixelGrid[sourceRow].data()), rowStride);

        // Fix: You must write the padding bytes back out to keep the rows 4-byte aligned!
        if (padding > 0)
        {
            this->outfile.write(paddingBytes, padding);
        }
    }

}