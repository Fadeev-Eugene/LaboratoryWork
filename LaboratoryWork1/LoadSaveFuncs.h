//Fadeev Eugene st128225@student.spbu.ru
//This code contains realization of load and save funcs



#ifndef LoadSaveFuncs_H
#define LoadSaveFuncs_H

#include "BMPImage.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


BMPImage loadBMP(const std::string& filename);

void saveBMP(const std::string& filename, const BMPImage& image);

#endif
