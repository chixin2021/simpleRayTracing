#include <iostream>
#include <fstream>
#include "./lib/toojpeg/toojpeg.h"
using namespace std;


/****************************************************
 *    write grid data to image file in jpg format   *
 *    black pixel represents a dead cell            *
 *    white pixel represents a live cell            *
 ****************************************************
 */

ofstream outputFile;

void color_to_jpeg(int imax, int jmax, color* canvas, string filename){
    outputFile.open(filename, std::ios_base::out | std::ios_base::binary);
    // define a callback
    auto output = [](unsigned char byte) { 
        outputFile << byte;
        };

    // Encode from raw pixels to disk with a single function call
    // The image argument has width * height RGBA pixels or width * height * 4 bytes
    auto image = new unsigned char[jmax * imax * 3];


    for(int i = 0; i < imax; i++){
        for(int j = 0; j < jmax; j++) {
        int offset = 3 * jmax * i + 3 * j ;
        image[offset + 0] = 255 * canvas[j + i * jmax].x(); 
        image[offset + 1] = 255 * canvas[j + i * jmax].y(); 
        image[offset + 2] = 255 * canvas[j + i * jmax].z();
        }
    }

    // thread safe: we write the whole pixel data to file instead of write file in parallel.  
    TooJpeg::writeJpeg(output, image, jmax, imax);
    outputFile.close();
    delete[] image;
    return;    
}
