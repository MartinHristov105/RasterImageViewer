#pragma once
#include <fstream>
#include "Image.h"

class Saver {
public:
	static void saveFile(const Image& image, std::ostream& os);  // generic loader
private:
    static void savePBM(const Image& image, std::ostream& os);
    static void savePGM(const Image& image, std::ostream& os);
    static void savePPM(const Image& image, std::ostream& os);

    static void savePBMBinary(const Image& image, std::ostream& os); 
    static void savePGMBinary(const Image& image, std::ostream& os);
    static void savePPMBinary(const Image& image, std::ostream& os);

    static void saveBMP(const Image& image, std::ostream& os); 
};