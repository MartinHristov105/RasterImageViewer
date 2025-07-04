#include "LoadCommand.h"

Session LoadCommand::applyLoadCommand(std::vector<std::string>& fileNames) {
	std::vector<Image> images;

	for (size_t i = 0; i < fileNames.size(); ++i) {
		images.push_back(Loader::loadFile(fileNames[i])); // loadFile returns an image created from fileNames[i]
		size_t pos = fileNames[i].find_last_of('\\');
		fileNames[i] = (pos == std::string::npos) ? fileNames[i] : fileNames[i].substr(pos + 1);
	}

	return Session(fileNames, images, {}); // returns a session with fileNames, images and empty vector of transformations
}