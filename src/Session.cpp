#include "Session.h"

int Session::ID = 0;

Session::Session(const std::vector<std::string>& fileNames, const std::vector<Image>& images, const std::vector<Transformation>& transformations)
	: id(++ID),
      fileNames(fileNames), 
      images(images), 
      transformations(transformations), 
      currentTransformationIndex(0), 
      savedTransformationIndex(0),
      imageStartTransformationIndex(images.size(), 0) {}

const int Session::getID() const { return id; }

const std::vector<std::string>& Session::getFileNames() const { return fileNames; }
std::vector<std::string>& Session::getFileNames() { return fileNames; }

const std::vector<Image>& Session::getImages() const { return images; }
std::vector<Image>& Session::getImages() { return images; }

const std::vector<Transformation>& Session::getTransformations() const { return transformations; }
std::vector<Transformation>& Session::getTransformations() { return transformations; }
size_t Session::getCurrentTransformationIndex() const { return currentTransformationIndex; }

size_t Session::getSavedTransformationIndex() const { return savedTransformationIndex; }

const std::vector<size_t>& Session::getImageStartTransformationIndex() const { return imageStartTransformationIndex; }
std::vector<size_t>& Session::getImageStartTransformationIndex() { return imageStartTransformationIndex; }

void Session::markAsSaved() {
    savedTransformationIndex = currentTransformationIndex; // stores the current transformation index as the saved state.
}

void Session::addTransformation(const Transformation& newTransformation) {
    // If the user had previously undone some transformations, those are discarded.
    // Remove all undone transformations beyond the current point (if any).
    if (currentTransformationIndex < transformations.size()) {
        transformations.erase(transformations.begin() + currentTransformationIndex, transformations.end());
    }

    // Add the new transformation and update the index.
    transformations.push_back(newTransformation);
    ++currentTransformationIndex;
}
void Session::undo() {
    if (transformations.empty() || currentTransformationIndex == 0) { return; } // nothing to undo.
	--currentTransformationIndex; // moves the index one step back in the transformation history.
}
void Session::redo() {
    if (currentTransformationIndex >= transformations.size()) { return; } // nothing to do
    ++currentTransformationIndex; // moves the index one step forward in the transformation history.
}