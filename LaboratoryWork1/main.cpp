#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include "LoadSaveFuncs.h"
#include "BMPImage.h"

std::mutex cout_mutex;

void processImage(const std::string& filename, int kernelSize, double sigma, const std::string& suffix) {
    try {
        std::unique_ptr<BMPImage> image;
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Thread " << suffix << ": loading image..." << std::endl;
        }
        image.reset(new BMPImage(loadBMP(filename)));
        
        if (suffix == "clockwise") {
            image->rotate90Clockwise();
            saveBMP("rotated_clockwise.bmp", *image);
        } else {
            image->rotate90CounterClockwise();
            saveBMP("rotated_counterclockwise.bmp", *image);
        }
        
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Thread " << suffix << ": rotated image saved" << std::endl;
        }
        
        image->applyGaussianFilter(kernelSize, sigma);
        std::string filteredName = "gaussian_filtered_" + suffix + ".bmp";
        saveBMP(filteredName, *image);
        
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Thread " << suffix << ": filtered image saved" << std::endl;
        }
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cerr << "Error in thread " << suffix << ": " << e.what() << std::endl;
    }
}

int main() {
    std::string name;
    int size;
    double sigma;

    std::cout << "Type name of your file >> ";
    std::cin >> name;
    std::cout << "Type size of Gaussian Kernel >> ";
    std::cin >> size;
    std::cout << "Type value of standard deviation >> ";
    std::cin >> sigma;
    std::cout << std::endl;
    
    std::thread t1(processImage, name, size, sigma, "clockwise");
    std::thread t2(processImage, name, size, sigma, "counterclockwise");
    
    t1.join();
    t2.join();

    return 0;
}
