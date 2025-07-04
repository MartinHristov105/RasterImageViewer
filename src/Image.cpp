#include "Image.h"

Image::Image(const std::string& format, int maxValue, const std::vector<std::vector<Pixel>>& matrix) : format(format), maxValue(maxValue) {
	if (!setMatrix(matrix)) { throw std::runtime_error("Invalid matrix data!"); }
}

const std::string& Image::getFormat() const { return format; }
int Image::getMaxVal() const { return maxValue; }
size_t Image::getHeight() const { return matrix.size(); }
size_t Image::getWidth() const { return matrix[0].size(); }

const std::vector<std::vector<Pixel>>& Image::getMatrix() const { return matrix; }
std::vector<std::vector<Pixel>>& Image::getMatrix() { return matrix; }

bool Image::setMatrix(const std::vector<std::vector<Pixel>>& matrix) {
	if (matrix.empty()) { return false; }

	size_t tempWidth = matrix[0].size();
	for (size_t i = 1; i < matrix.size(); ++i) {
		if (matrix[i].size() != tempWidth) { return false; } // check if some row has different width
	}

	this->matrix = matrix;
	return true;
}