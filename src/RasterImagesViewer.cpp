#include "RasterImagesViewer.h"

void RasterImagesViewer::run() {
    std::cout << "Welcome to Raster Images Viewer!\n";

    bool running = true;
    // Main command loop
    while (running) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        // Require a session for all commands except 'load' and 'exit'
        if ((command != "load" && command != "exit") && sessions.empty()) {
            std::cout << "You must first load a session!\n";
            continue;
        }

        if (command == "load") {
            std::vector<std::string> fileNames;
            std::string fileName;
            while (iss >> fileName) {
                fileNames.push_back(fileName);
            }

            if (fileNames.empty()) {
                std::cout << "No file names provided! Usage: load <file1> <file2> ...\n";
                continue;
            }

            try {
                Session session = CommandHandler::loadCommand(fileNames);
                sessions.push_back(session);
                currentSessionIndex = sessions.size() - 1;
                std::cout << "Session loaded successfully.\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error loading session:\n" << e.what() << '\n';
            }
        }
        else if (command == "add") {
            std::string fileName;
            iss >> fileName;

            if (fileName.empty()) {
                std::cout << "No file names provided! Usage: add <file>\n";
                continue;
            }

            CommandHandler::addCommand(sessions[currentSessionIndex], fileName);
        }
        else if (command == "grayscale" || command == "monochrome" || command == "negative") {
            try {
                CommandHandler::transformationCommand(sessions[currentSessionIndex], command);
            }
            catch (...) {
                std::cout << "Could not make the transformation!";
            }
        }
        else if (command == "rotate") {
            std::string direction;
            iss >> direction;

            if (direction == "left" || direction == "right") {
                std::string endCommand = command + ' ' + direction;
                try {
                    CommandHandler::transformationCommand(sessions[currentSessionIndex], endCommand);
                }
                catch (...) {
                    std::cout << "Could not make the transformation!";
                }
            }
            else {
                std::cout << "Unknown command!\n";
                continue;
            }
        }
        else if (command == "flip") {
            std::string direction;
            iss >> direction;

            if (direction == "top" || direction == "left") {
                std::string endCommand = command + ' ' + direction;
                try {
                    CommandHandler::transformationCommand(sessions[currentSessionIndex], endCommand);
                }
                catch (...) {
                    std::cout << "Could not make the transformation!";
                }
            }
            else {
                std::cout << "Unknown command!\n";
                continue;
            }
        }
        else if (command == "undo") { 
            CommandHandler::undoCommand(sessions[currentSessionIndex]); 
        }
        else if (command == "redo") { 
            CommandHandler::redoCommand(sessions[currentSessionIndex]); 
        }
        else if (command == "save") {
            CommandHandler::saveAsCommand(sessions[currentSessionIndex], {});
            std::cout << "Saved successfully!\n";
        }
        else if (command == "saveas") {
            std::vector<std::string> fileNames;
            std::string fileName;
            while (iss >> fileName) {
                fileNames.push_back(fileName);
            }

            if (fileNames.size() > sessions[currentSessionIndex].getFileNames().size()) {
                std::cout << "Inputed names count should equal or less to the loaded in the session!\n"; 
                continue;
            }
            else {
                CommandHandler::saveAsCommand(sessions[currentSessionIndex], fileNames);
                std::cout << "SavedAs successfully!\n";
            }
        }
        else if (command == "list") {
            std::string fileName;
            iss >> fileName;

            if (fileName != "session") {
                std::cout << "Unknown command!\n";
                continue;
            }
            CommandHandler::listSessionCommand(sessions[currentSessionIndex]);
        }
        else if (command == "paste") {
            std::string srcName;
            std::string dstName;
            size_t posX = 0;
            size_t posY = 0;

            iss >> srcName;
            iss >> dstName;
            iss >> posX;
            iss >> posY;

            if (srcName.empty() || dstName.empty()) {
                std::cout << "No file names provided! Usage: paste <srcName> <dstName> <posX> <posY>\n";
                continue;
            }

            try {
                CommandHandler::pasteCommand(sessions[currentSessionIndex], srcName, dstName, posX, posY);
                std::cout << "Pasted successfully!\n";
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Could not paste!\n" << e.what() << '\n';
            }
            catch (const std::exception& e) {
                std::cout << "Could not paste!\n" << e.what() << '\n';
            }
        }
        else if (command == "switch") {
            size_t sessionId = 0;
            iss >> sessionId;

            bool found = false;
            for (size_t i = 0; i < sessions.size(); ++i) {
                if (sessions[i].getID() == sessionId) {
                    currentSessionIndex = i;
                    std::cout << "Switched to session " << sessionId << "!\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "No session with ID " << sessionId << " found!\n";
            }
        }
        else if (command == "exit") {
            CommandHandler::exitCommand(sessions);
            std::cout << "Goodbye!\n";
            running = false;
        }
        else {
            std::cout << "Unknown command!\n";
        }
    }
}