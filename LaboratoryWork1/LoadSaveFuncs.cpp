//Fadeev Eugene st128225@student.spbu.ru
//This code contains realization of load and save funcs

#include "BMPImage.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


// Function for loading image
BMPImage loadBMP(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    // Read BMP header
    file.seekg(14);
    int w;
    file.read(reinterpret_cast<char*>(&w), 4);

    file.seekg(18);
    int width, height;
    file.read(reinterpret_cast<char*>(&width), 4);
    file.read(reinterpret_cast<char*>(&height), 4);
    BMPImage image(width, height);

    // Skip header and read pixel data
    file.seekg(w+14);
    int padding = (4 - (width * 3) % 4) % 4;
    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            Pixel& p = image.getPixel(x, y);
            file.read(reinterpret_cast<char*>(&p), 3);
        }
        file.ignore(padding);  // Пропустить padding байты
    }

    return image;
}


// Function or saving image
void saveBMP(const std::string& filename, const BMPImage& image)
{
    std::ofstream file(filename, std::ios::binary);

    const int padding = (4 - (image.width * 3) % 4) % 4;
    //std::cout<<padding<<std::endl;
    const int fileSize = 54 + (3 * image.width + padding) * image.height;

    // BMP Header
    file.put('B').put('M');                            // Signature
    file.write(reinterpret_cast<const char*>(&fileSize), 4); // File size
    file.put(0).put(0).put(0).put(0);                  // Reserved
    file.put(54).put(0).put(0).put(0);                 // Pixel data offset
    // DIB Header
    const int headerSize = 40;
    file.write(reinterpret_cast<const char*>(&headerSize), 4);       // DIB header size
    file.write(reinterpret_cast<const char*>(&image.width), 4);      // Image width
    file.write(reinterpret_cast<const char*>(&image.height), 4);     // Image height
    file.put(1).put(0);                                       // Planes
    file.put(24).put(0);                                      // Bits per pixel
    file.put(0).put(0).put(0).put(0);                         // Compression (none)
    const int dataSize = (3 * image.width + padding) * image.height;
    file.write(reinterpret_cast<const char*>(&dataSize), 4);         // Image data size
    const int ppm = 2835;                                    // Pixels per meter (72 DPI)
    file.write(reinterpret_cast<const char*>(&ppm), 4);      // Horizontal resolution
    file.write(reinterpret_cast<const char*>(&ppm), 4);      // Vertical resolution
    file.put(0).put(0).put(0).put(0);                        // Colors in color table
    file.put(0).put(0).put(0).put(0);                        // Important color count

    // Pixel data

    for (int y = image.height - 1; y >= 0; --y)
    {
        for (int x = 0; x < image.width; ++x)
        {
            const Pixel& p = image.getPixel(x, y);
            file.write(reinterpret_cast<const char*>(&p.blue), 1);
            file.write(reinterpret_cast<const char*>(&p.green), 1);
            file.write(reinterpret_cast<const char*>(&p.red), 1);
        }
        file.write("\0\0\0", padding); // Add padding bytes if needed
    }
}
