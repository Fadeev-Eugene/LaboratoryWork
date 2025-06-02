# BMP Image Processor

## Author
Evgeny Fadeev, Group B81-mm  
Contact: st128225@student.spbu.ru

## Description
Processes 24-bit BMP images to:
1. Generate rotated versions (90° clockwise and counter-clockwise)
2. Apply Gaussian blur to rotated images
3. Save all results as separate BMP files

Uses multithreading for parallel processing of rotation operations.

## Build & Run
```bash
# Compile project
make

# Execute program
./main

# Clean build artifacts
make clean
