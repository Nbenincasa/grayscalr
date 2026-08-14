#include "bmp/include/bmp_24.h"

int main(int argc, char* argv[])
{
    // Check for file name
    if(argc < 1)
    {
        std::cerr << "ERROR: No arguments. Include filename when calling executable.\n";
        return 1;
    }
    if (!argv[1]) 
    { 
        std::cerr << "ERROR: File not provided.\n";
        return 1;
    }

    BMP_24 bmp(static_cast<std::string>(argv[1]),"output.bmp");
    bmp.covertToGrayscale();

    return 0;
}