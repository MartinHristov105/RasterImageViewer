#include "CoreTransformations.h"

void CoreTransformations::applyCoreTransformations(Image& image, const std::string& transformation) {
    if (transformation == "grayscale") {
        if (!isGrayscale(image.getMatrix())) {
            applyGrayscale(image.getMatrix());
        }
    }
    else if (transformation == "monochrome") {
        if (!isMonochrome(image.getMatrix())) {
            applyMonochrome(image.getMatrix());
        }
    }
    else if (transformation == "negative") {
        applyNegative(image.getMatrix());
    }
}

void CoreTransformations::applyGrayscale(std::vector<std::vector<Pixel>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Make gray
            unsigned char gray = (unsigned char)(0.3 * matrix[i][j].getR() + 0.59 * matrix[i][j].getG() + 0.11 * matrix[i][j].getB());
            matrix[i][j] = Pixel(gray, gray, gray);
        }
    }
}
void CoreTransformations::applyMonochrome(std::vector<std::vector<Pixel>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Make black or white
            unsigned char bw = (matrix[i][j].getR() > 127) ? 255 : 0;
            matrix[i][j] = Pixel(bw, bw, bw);
        }
    }
}
void CoreTransformations::applyNegative(std::vector<std::vector<Pixel>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            int temp = 255;
            // Reverse values
            unsigned char red = temp - matrix[i][j].getR();
            unsigned char green = temp - matrix[i][j].getG();
            unsigned char blue = temp - matrix[i][j].getB();

            matrix[i][j] = Pixel(red, green, blue);
        }
    }
}

bool CoreTransformations::isGrayscale(const std::vector<std::vector<Pixel>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            const Pixel& pixel = matrix[i][j];
            if (!(pixel.getR() == pixel.getG() && pixel.getG() == pixel.getB())) {
                return false; // At least one pixel is colored
            }
        }
    }

    return true; // All pixels are grayscale
}
bool CoreTransformations::isMonochrome(const std::vector<std::vector<Pixel>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            const Pixel& pixel = matrix[i][j];
            if (!((pixel.getR() == 255 || pixel.getR() == 0) && pixel.getG() == pixel.getR() && pixel.getB() == pixel.getG())) {
                return false; // At least one pixel is not black or white
            }
        }
    }

    return true; // All pixels are black or white
}