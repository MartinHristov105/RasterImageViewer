#include "GeometricTransformations.h"

void GeometricTransformations::applyGeometricTransformations(Image& image, const std::string& transformation) {
	if (transformation == "rotate left") { applyRotateLeft(image.getMatrix()); }
	else if (transformation == "rotate right") { applyRotateRight(image.getMatrix()); }
	else if (transformation == "flip top") { applyFlipTop(image.getMatrix()); }
	else if (transformation == "flip left") { applyFlipLeft(image.getMatrix()); }
}

void GeometricTransformations::applyRotateLeft(std::vector<std::vector<Pixel>>& matrix) {
	size_t oldHeight = matrix.size();
	size_t oldWidth = matrix[0].size();

	// Nothing to transform
	if (oldHeight == 0 || oldWidth == 0) { return; }

	std::vector<std::vector<Pixel>> rotated(oldWidth, std::vector<Pixel>(oldHeight));
	for (size_t i = 0; i < oldHeight; ++i) {
		for (size_t j = 0; j < oldWidth; ++j) {
			rotated[oldWidth - j - 1][i] = matrix[i][j];
		}
	}

	matrix.clear();
	matrix.resize(oldWidth, std::vector<Pixel>(oldHeight));
	matrix = rotated;
}
void GeometricTransformations::applyRotateRight(std::vector<std::vector<Pixel>>& matrix) {
	size_t oldHeight = matrix.size();
	size_t oldWidth = matrix[0].size();

	// Nothing to transform
	if (oldHeight == 0 || oldWidth == 0) { return; }

	std::vector<std::vector<Pixel>> rotated(oldWidth, std::vector<Pixel>(oldHeight));
	for (size_t i = 0; i < oldHeight; ++i) {
		for (size_t j = 0; j < oldWidth; ++j) {
			rotated[j][oldHeight - i - 1] = matrix[i][j];
		}
	}

	matrix.clear();
	matrix.resize(oldWidth, std::vector<Pixel>(oldHeight));
	matrix = rotated;
}
void GeometricTransformations::applyFlipTop(std::vector<std::vector<Pixel>>& matrix) {
	size_t height = matrix.size();
	// Nothing to transform
	if (height == 0) { return; }

	for (size_t i = 0; i < height / 2; ++i) {
		std::swap(matrix[i], matrix[height - i - 1]);
	}
}
void GeometricTransformations::applyFlipLeft(std::vector<std::vector<Pixel>>& matrix) {
	size_t height = matrix.size();
	// Nothing to transform
	if (height == 0) { return; }

	size_t width = matrix[0].size();
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width / 2; ++j) {
			std::swap(matrix[i][j], matrix[i][width - j - 1]);
		}
	}
}