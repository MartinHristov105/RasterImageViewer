#pragma once
#include "CoreTransformations.h"
#include "GeometricTransformations.h"

// Make it this way so we can later store transformations in the session for a valid undo/redo and apply
class Transformation {
public:
    Transformation(const std::string& transformationName);

    const std::string getTransformationName() const;
    std::string getTransformationName();

    void applyTransformation(Image& images);
private:
    std::string transformationName;
};