
#include "bmp/include/bmp_v1.h"

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

    // Open filestream in binary mode for both input and output files 
    std::ifstream infile  (argv[1]      , std::ios::binary);
    std::ofstream outfile ("output.bmp" , std::ios::binary);

    // Ensure file successfully opened
    if(!infile.is_open() || !outfile.is_open())
    {
        std::cerr << "ERROR: Failed to open one or more files.\n";
        return 1;
    }
    
    // Write input file data to output file for easier access to pixel array after modification
    outfile << infile.rdbuf();
    outfile.close();

    // Reset file positon for infile
    infile.clear();
    infile.seekg(0);

    // Open filestream for output file editing
    std::fstream editfile("output.bmp", std::ios::in | std::ios::out | std::ios::binary);
    if(!editfile.is_open())
    {
        std::cerr << "ERROR: Failed to open one or more files.\n";
        return 1;
    }

    // Map BMP Data
    BMP_V1 bmp(infile,editfile);

    // Initialize object data for readability
    bmp.initialize();

    // Edit pixel values and write to file
    bmp.makeGrayscale();

    infile.close();
    editfile.close();
    

    return 0;
}