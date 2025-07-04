#include "PasteCommand.h"

void PasteCommand::applyPasteCommand(Session& session, const std::string& srcName, const std::string& destName, size_t posX, size_t posY) {
    std::vector<Image>& images = session.getImages();
    std::vector<std::string>& fileNames = session.getFileNames();

    int srcIndex = -1;
    int destIndex = -1;

    // Find the indexes of the source and destination images by name
    for (size_t i = 0; i < fileNames.size(); ++i) {
        if (fileNames[i] == srcName) srcIndex = i;
        if (fileNames[i] == destName) destIndex = i;
    }

    if (srcIndex == -1 || destIndex == -1) { throw std::invalid_argument("One or both image names not found in the session!"); }

    // Check if formats match before attempting to paste
    const std::string& srcFormat = images[srcIndex].getFormat();
    const std::string& destFormat = images[destIndex].getFormat();

    if (srcFormat != destFormat) { throw std::invalid_argument("Could not paste: image formats do not match (" + srcFormat + " into " + destFormat + ")."); }

    // Copy the destination image to modify it
    Image newImage = images[destIndex];
    std::vector<std::vector<Pixel>> newMatrix = newImage.getMatrix();
    std::vector<std::vector<Pixel>>& srcMatrix = images[srcIndex].getMatrix();

    size_t srcHeight = srcMatrix.size();
    size_t srcWidth = srcMatrix[0].size();

    size_t destHeight = newMatrix.size();
    size_t destWidth = newMatrix[0].size();

    // Dimensions needed
    size_t requiredHeight = std::max(destHeight, posY + srcHeight);
    size_t requiredWidth = std::max(destWidth, posX + srcWidth);

    // Expand dimensions in the destination if needed, filling new rows with white pixels
    if (requiredHeight > destHeight) {
        Pixel white(255, 255, 255);
        newMatrix.resize(requiredHeight, std::vector<Pixel>(destWidth, white));
    }

    for (size_t i = 0; i < newMatrix.size(); ++i) {
        std::vector<Pixel>& row = newMatrix[i];
        if (row.size() < requiredWidth) {
            row.resize(requiredWidth, Pixel(255, 255, 255));
        }
    }

    // Copy source image pixels into destination at the given position
    for (size_t y = 0; y < srcHeight; ++y) {
        for (size_t x = 0; x < srcWidth; ++x) {
            newMatrix[posY + y][posX + x] = srcMatrix[y][x];
        }
    }

    // Apply the updated matrix to the image
    newImage.setMatrix(newMatrix);

    size_t srcPos = srcName.find_last_of('.');
    std::string srcFinal = (srcPos == std::string::npos) ? srcName : srcName.substr(0, srcPos);

    std::string fileName = "saves\\" + srcFinal + '_' + destName;

    std::ofstream ofs;
    if (newImage.getFormat() == "P1" || newImage.getFormat() == "P2" || newImage.getFormat() == "P3") { ofs.open(fileName); }
    else { ofs.open(fileName, std::ios::binary); }

    Saver::saveFile(newImage, ofs);
    ofs.close();
    AddCommand::applyAddCommand(session, fileName);
}