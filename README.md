This program takes an image in BMP format and creates a grayscale version.
It only supports uncompressed 24-bit BMP files

1. Take a file as an argument {X}
2. Check that the file exists and is in the correct format (.bmp){ }
3. Read the file data into a buffer {X}
4. Determine file structure and separate into data structures using known file structure
    - BMP Header 
    - DIB Header 
    - Extra Bit Masks
    - Color Table
    - Gap1
    - Pixel Array
    - Gap 2
    - ICC color profile
5. Save header data to output file
6. Use header info to get size and starting position of pixel array
7. Edit RGB values such that all values are equal and grayscaled
8. Write edited data into a new file
9. Save file
10. Verify file was created successfully