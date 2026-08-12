#include "bmp_defs.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <bit>

class BMP_V1
{
private:

    std::ifstream&          infile;
    std::fstream&           outfile;

    Bitmap_File_Header               file_header;
    Bitmap_Info_Header               info_header;

    void initializeFileHeader();
    void initializeInfoHeader();
    void grayscale24Bit();
    void writeGrayScaleToOutputFile(std::vector<std::vector<Pixel>> pixelGrid);
    

public:

    BMP_V1(std::ifstream& infile_arg, std::fstream& outfile_arg);
    ~BMP_V1();
    std::vector<uint32_t> getDataBuffer();
    void initialize();
    void makeGrayscale();

};


