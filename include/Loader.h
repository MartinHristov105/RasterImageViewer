#pragma once
#include <fstream>
#include "Image.h"

class Loader {
public:
	static Image loadFile(const std::string& filename); // generic loader
private:
    static int loadMaxValue(std::istream& is);

    static Image loadPBM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix);
    static Image loadPGM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix);
    static Image loadPPM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix);

    static Image loadPBMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix); 
    static Image loadPGMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix);
    static Image loadPPMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix);

    static Image loadBMP(const std::string& format, std::istream& is); 
};