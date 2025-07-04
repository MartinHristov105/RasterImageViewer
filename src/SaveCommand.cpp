#include "SaveCommand.h"

void SaveCommand::applySaveCommand(Session& session, const std::vector<std::string>& fileNames) {	
    Session temp = applyAllTransformations(session); // create a temporary session with all transformations applied
    std::vector<Image>& images = temp.getImages();

    for (size_t i = 0; i < images.size(); ++i) {
        std::ofstream ofs;
        // Open file in text mode for ASCII formats, binary mode for binary formats
        if (images[i].getFormat() == "P1" || images[i].getFormat() == "P2" || images[i].getFormat() == "P3") {
            ofs.open(fileNames[i]);
        }
        else { ofs.open(fileNames[i], std::ios::binary); }

        // Throw error if file could not be opened
        if (!ofs.is_open()) { throw std::runtime_error(fileNames[i]); }

        Saver::saveFile(images[i], ofs); // save the transformed image to the file
    }
    session.markAsSaved(); // mark the original session as saved
}

Session SaveCommand::applyAllTransformations(Session& session) {
    Session temp = session;
    if (temp.getTransformations().empty()) { return temp; } // if no transformations are made just create a copy of the session

    // Apply transformations for each image in the session.
    for (size_t i = 0; i < temp.getImages().size(); ++i) {
        Image& image = temp.getImages()[i];
        size_t start = temp.getImageStartTransformationIndex()[i];
        size_t end = temp.getCurrentTransformationIndex();

        // Track transformation counts for optimization.
        size_t RRotations = 0;
        size_t LRotations = 0;
        size_t flipTopCount = 0;
        size_t flipLeftCount = 0;
        bool hasGrayscale = false;
        bool hasMonochrome = false;
        size_t negativeCount = 0;

        // Analyze transformations that affect the current image.
        for (size_t j = start; j < end; ++j) {
            const std::string& name = temp.getTransformations()[j].getTransformationName();

            if (name == "rotate left") { ++LRotations; }
            else if (name == "rotate right") { ++RRotations; }
            else if (name == "flip top") { ++flipTopCount; }
            else if (name == "flip left") { ++flipLeftCount; }
            else if (name == "grayscale" && !hasMonochrome) { hasGrayscale = true; }
            else if (name == "monochrome") {
                hasGrayscale = false;
                hasMonochrome = true;
            }
            else if (name == "negative") { ++negativeCount; }
        }

        // Simplify transformations by using mod.
        LRotations %= 4;
        RRotations %= 4;
        flipTopCount %= 2;
        flipLeftCount %= 2;
        negativeCount %= 2;

        // Apply effect of the transformations.
        if (LRotations > RRotations) {
            for (size_t j = 0; j < LRotations - RRotations; ++j) {
                Transformation("rotate left").applyTransformation(image);
            }
        }
        else {
            for (size_t j = 0; j < RRotations - LRotations; ++j) {
                Transformation("rotate right").applyTransformation(image);
            }
        }
        if (flipTopCount) { Transformation("flip top").applyTransformation(image); }
        if (flipLeftCount) { Transformation("flip left").applyTransformation(image); }
        if (hasGrayscale) { Transformation("grayscale").applyTransformation(image); }
        if (hasMonochrome) { Transformation("monochrome").applyTransformation(image); }
        if (negativeCount) { Transformation("negative").applyTransformation(image); }
    }

    return temp;
}