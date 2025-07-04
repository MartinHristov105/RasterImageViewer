#include "AddCommand.h"

void AddCommand::applyAddCommand(Session& session, std::string& fileName) {
    try { 
        Image img = Loader::loadFile(fileName);

        size_t pos = fileName.find_last_of('\\');
        fileName = (pos == std::string::npos) ? fileName : fileName.substr(pos + 1);

        session.getImages().push_back(img);
        try {
            session.getFileNames().push_back(fileName);
        }
        catch (...) {
            session.getImages().pop_back();
            throw;
        }
        try {
            session.getImageStartTransformationIndex().push_back(session.getCurrentTransformationIndex());
        }
        catch (...) {
            session.getImages().pop_back();
            session.getFileNames().pop_back();
            throw;
        }
        std::cout << "Image added successfully!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Error adding image:\n" << e.what() << '\n';
    }
}