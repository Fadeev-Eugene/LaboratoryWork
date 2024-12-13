//Fadeev Eugene st128225@student.spbu.ru
//This programm contains code for the first laboratory work
//This code reads 24 bit per pixel bmp image and apply to it rotation and gaussian filter

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include "LoadSaveFuncs.h"
#include "BMPImage.h"


int main()
{
    //input file name
    std::string name;
    int size;
    double sigma;

    std::cout<<"Type name of your file >> ";
    std::cin>>name;
    std::cout<<std::endl;

    std::cout<<"Type size of Gaussian Kernel >> ";
    std::cin>>size;
    std::cout<<std::endl;

    std::cout<<"Type value of standard deviation >> ";
    std::cin>>sigma;
    std::cout<<std::endl;

    {
        BMPImage image = loadBMP(name);
        image.rotate90Clockwise();
        saveBMP("rotated_clockwise.bmp", image);
        std::cout<<"rotated_clockwise.bmp is created"<<std::endl;
        image.applyGaussianFilter(size, sigma);
        saveBMP("gaussian_filtered_clockwise.bmp", image);
        std::cout<<"gaussian_filtered_clockwise.bmp is created"<<std::endl;
    }

    {
        BMPImage image2 = loadBMP(name);
        image2.rotate90CounterClockwise();
        saveBMP("rotated_counterclockwise.bmp", image2);
        std::cout<<"rotated_counterclockwise.bmp is created"<<std::endl;
        image2.applyGaussianFilter(size, sigma);
        saveBMP("gaussian_filtered_counterclockwise.bmp", image2);
        std::cout<<"gaussian_filtered_counterclockwise.bmp is created"<<std::endl;
    }

    return 0;
}
