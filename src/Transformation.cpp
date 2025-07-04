#include "Transformation.h"

Transformation::Transformation(const std::string& transformationName) : transformationName(transformationName) {}

const std::string Transformation::getTransformationName() const { return transformationName; }
std::string Transformation::getTransformationName() { return transformationName; }

void Transformation::applyTransformation(Image& images) {
    if (transformationName == "grayscale" || transformationName == "monochrome" || transformationName == "negative") { CoreTransformations::applyCoreTransformations(images, transformationName); }
    else if (transformationName == "rotate left" || transformationName == "rotate right" || transformationName == "flip top" || transformationName == "flip left") { GeometricTransformations::applyGeometricTransformations(images, transformationName); }
}