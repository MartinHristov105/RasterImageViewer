#pragma once
#include "Image.h"

class GeometricTransformations {
public:
	static void applyGeometricTransformations(Image& image, const std::string& transformation); // generic transformation
private:
	static void applyRotateLeft(std::vector<std::vector<Pixel>>& matrix);
	static void applyRotateRight(std::vector<std::vector<Pixel>>& matrix);
	static void applyFlipTop(std::vector<std::vector<Pixel>>& matrix);
	static void applyFlipLeft(std::vector<std::vector<Pixel>>& matrix);
};