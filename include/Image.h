#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include "Pixel.h"

class Image {
public:
	Image() = default;
	Image(const std::string& format, int maxValue, const std::vector<std::vector<Pixel>>& matrix);
	
	const std::string& getFormat() const;
	int getMaxVal() const;
	size_t getHeight() const;
	size_t getWidth() const;
	const std::vector<std::vector<Pixel>>& getMatrix() const;
	std::vector<std::vector<Pixel>>& getMatrix();

	bool setMatrix(const std::vector<std::vector<Pixel>>& matrix);
private:
	std::string format; // stores format
	int maxValue; // stores maxValue
	std::vector<std::vector<Pixel>> matrix; // store matrix of pixels
};