This program takes an image in BMP format and creates a grayscale version.

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
5. Use header info to get size and starting position of pixel array
6. Edit RGB values such that all values are equal and grayscaled
7. Write edited data into a new file
8. Save file
9. Verify file was created successfully