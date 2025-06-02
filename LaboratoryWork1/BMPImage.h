//Fadeev Eugene st128225@student.spbu.ru
//This code contains realization of BMPImage structure

#ifndef BMPImage_H
#define BMPImage_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdint>

struct Pixel
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};


struct BMPImage
{
    int width, height;
    std::vector<Pixel> pixels;

    BMPImage(int w, int h);

    Pixel& getPixel(int x, int y);

    const Pixel& getPixel(int x, int y) const;

    void rotate90Clockwise();

    void rotate90CounterClockwise();

    std::vector<std::vector<double>> generateGaussianKernel(int size, double sigma);

    void applyGaussianFilter(int kernelSize, double sigma);
};


#endif
