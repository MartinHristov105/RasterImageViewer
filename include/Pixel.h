#pragma once
#include <iostream>

class Pixel {
public:
	Pixel(); // default black pixel
	Pixel(unsigned char r, unsigned char g, unsigned char b);

	unsigned char getR() const;
	unsigned char getG() const;
	unsigned char getB() const;
private:
	unsigned char r; // values between 0-255
	unsigned char g;
	unsigned char b;
};