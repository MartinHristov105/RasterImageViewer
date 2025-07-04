#pragma warning(disable:4996)
#include "ExitCommand.h"

void ExitCommand::applyExitCommand(std::vector<Session>& sessions) {
    for (size_t i = 0; i < sessions.size(); ++i) {
        // Check if session has unsaved transformations
        if (!(sessions[i].getCurrentTransformationIndex() == sessions[i].getSavedTransformationIndex())) {
            std::cout << "Session " << sessions[i].getID() << " contains unsaved work.Save it now(y / n) ?\n> ";
            char choice;
            std::cin >> choice;
            choice = std::tolower(choice);
            while (choice != 'y' && choice != 'n') { // valid response
                std::cout << "Invalid choice. Please enter y or n: ";
                std::cin >> choice;
                choice = std::tolower(choice);
            }

            if (choice == 'y') {
                // Generate filenames based on original names and timestamp
                std::vector<std::string> generatedNames = generateOutputFilenames(sessions[i], {});

                try { // save session
                    SaveCommand::applySaveCommand(sessions[i], generatedNames);
                }
                catch (const std::runtime_error& e) {
                    std::cout << "Could not save file: " << e.what() << '\n';
                }
            }
        }
    }
}

std::string mapFormatToExtension(const std::string& format) {
    if (format == "P1" || format == "P4") return ".pbm";
    if (format == "P2" || format == "P5") return ".pgm";
    if (format == "P3" || format == "P6") return ".ppm";
    if (format == "BM") return ".bmp";
    return ".img";
}
// Generates output filenames for saving images, using current time to ensure uniqueness
std::vector<std::string> generateOutputFilenames(const Session& session, const std::vector<std::string>& providedNames) {
    std::vector<std::string> result;
    const std::vector<Image>& images = session.getImages();
    const std::vector<std::string>& originalNames = session.getFileNames();

    std::time_t t = std::time(nullptr); // get current system time formatted as YYYYMMDD_HHMMSS
    std::tm tm = *std::localtime(&t); // may trigger warning if localtime is unsafe on platform
    char timeBuffer[32];
    std::strftime(timeBuffer, sizeof(timeBuffer), "_%Y%m%d_%H%M%S", &tm);

    // Use provided file names directly
    for (size_t i = 0; i < providedNames.size(); ++i) {
        const std::string& name = providedNames[i];
        result.push_back(name);
    }

    // For the remaining images, generate names: original name + timestamp + appropriate extension
    for (size_t i = providedNames.size(); i < images.size(); ++i) {
        std::string base = originalNames[i];
        size_t dotPos = base.find_last_of('.'); // remove . from original file name
        if (dotPos != std::string::npos) {
            base = base.substr(0, dotPos);
        }

        // Create the new name
        std::string newName = "saves\\" + base + timeBuffer + mapFormatToExtension(images[i].getFormat()); // default dir for save if no names are provided
        result.push_back(newName);
    }

    return result;
}