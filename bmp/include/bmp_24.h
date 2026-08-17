#include "bmp_defs.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <bit>

class BMP_24
{
private:

    BMPHeader  header;
    const std::string inputPath;
    const std::string outputPath;
    
    public:
    
    BMP_24(const std::string& inputPath_arg, const std::string& outputPath_arg);
    ~BMP_24();
    bool covertToGrayscale();

};


