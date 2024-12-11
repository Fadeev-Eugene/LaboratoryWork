//Fadeev Eugene st128225@student.spbu.ru
//This code contains realization of BMPImage structure funcs
#include "BMPImage.h"

// Constructor
BMPImage::BMPImage(int w, int h) : width(w), height(h), pixels(w * h) {}

// Functions for getting pixel
Pixel& BMPImage::getPixel(int x, int y)
{
    return pixels[y * width + x];
}

const Pixel& BMPImage::getPixel(int x, int y) const
{
    return pixels[y * width + x];
}


// Function for rotation 90 degries clockwise
void BMPImage::rotate90Clockwise()
{
    std::vector<Pixel> rotatedPixels(height * width);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            rotatedPixels[x * height + (height - y - 1)] = getPixel(x, y);
        }
    }
    pixels = std::move(rotatedPixels);
    std::swap(width, height);
}


// Function for rotation 90 degries counter clockwise
void BMPImage::rotate90CounterClockwise()
{
    std::vector<Pixel> rotatedPixels(height * width);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            rotatedPixels[(width - x - 1) * height + y] = getPixel(x, y);
        }
    }
    pixels = std::move(rotatedPixels);
    std::swap(width, height);
}

// Function for generation of Gaussian kernel
std::vector<std::vector<double>> BMPImage::generateGaussianKernel(int size, double sigma)
{
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double sum = 0.0;
    int offset = size / 2;

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            double exponent = -(std::pow(x - offset, 2) + std::pow(y - offset, 2)) / (2 * sigma * sigma);
            kernel[y][x] = std::exp(exponent) / (2 * M_PI * sigma * sigma);
            sum += kernel[y][x];
        }
    }

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            kernel[y][x] /= sum;
        }
    }
    return kernel;
}


// Function for applying Gaussian filter
void BMPImage::applyGaussianFilter(int kernelSize, double sigma)
{
    auto kernel = generateGaussianKernel(kernelSize, sigma);
    int offset = kernelSize / 2;
    std::vector<Pixel> filteredPixels = pixels;

    for (int y = offset; y < height - offset; ++y)
    {
        for (int x = offset; x < width - offset; ++x)
        {
            double red = 0, green = 0, blue = 0;

            for (int ky = -offset; ky <= offset; ++ky)
            {
                for (int kx = -offset; kx <= offset; ++kx)
                {
                    const Pixel& p = getPixel(x + kx, y + ky);
                    double weight = kernel[ky + offset][kx + offset];
                    red += p.red * weight;
                    green += p.green * weight;
                    blue += p.blue * weight;
                }
            }

            Pixel& fp = filteredPixels[y * width + x];
            fp.red = static_cast<uint8_t>(std::min(std::max(int(red), 0), 255));
            fp.green = static_cast<uint8_t>(std::min(std::max(int(green), 0), 255));
            fp.blue = static_cast<uint8_t>(std::min(std::max(int(blue), 0), 255));
        }
    }
    pixels = std::move(filteredPixels);
}
