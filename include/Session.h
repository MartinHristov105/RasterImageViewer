#pragma once
#include "Transformation.h"

class Session {
public:
	Session() = default;
	Session(const std::vector<std::string>& fileNames, const std::vector<Image>& images, const std::vector<Transformation>& transformations);

	const int getID() const;

	const std::vector<std::string>& getFileNames() const;
	std::vector<std::string>& getFileNames();

	const std::vector<Image>& getImages() const;
	std::vector<Image>& getImages();

	const std::vector<Transformation>& getTransformations() const;
	std::vector<Transformation>& getTransformations();
	size_t getCurrentTransformationIndex() const;

	size_t getSavedTransformationIndex() const;

	const std::vector<size_t>& getImageStartTransformationIndex() const;
	std::vector<size_t>& getImageStartTransformationIndex();

	void markAsSaved();

	void addTransformation(const Transformation& newTransforms);
	void undo();
	void redo();
private:
	static int ID;

	const int id;
	std::vector<std::string> fileNames;
	std::vector<Image> images;

	std::vector<Transformation> transformations;
	size_t currentTransformationIndex;

	size_t savedTransformationIndex;

	std::vector<size_t> imageStartTransformationIndex;
};