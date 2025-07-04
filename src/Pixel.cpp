#include "Pixel.h"

Pixel::Pixel() : Pixel(0, 0, 0) {}
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

unsigned char Pixel::getR() const { return r; }
unsigned char Pixel::getG() const { return g; }
unsigned char Pixel::getB() const { return b; }