#pragma once
#include "Image.h"

class CoreTransformations {
public:
    static void applyCoreTransformations(Image& image, const std::string& transformation); // generic transformation
private:
    static void applyGrayscale(std::vector<std::vector<Pixel>>& matrix);
    static void applyMonochrome(std::vector<std::vector<Pixel>>& matrix);
    static void applyNegative(std::vector<std::vector<Pixel>>& matrix);

    static bool isGrayscale(const std::vector<std::vector<Pixel>>& matrix);
    static bool isMonochrome(const std::vector<std::vector<Pixel>>& matrix);
};