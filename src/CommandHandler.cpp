#pragma warning(disable:4996)
#include "CommandHandler.h"

Session CommandHandler::loadCommand(std::vector<std::string>& fileNames) {
    return LoadCommand::applyLoadCommand(fileNames);
}

void CommandHandler::addCommand(Session& session, std::string& fileName) {
    AddCommand::applyAddCommand(session, fileName);
}

void CommandHandler::transformationCommand(Session& session, const std::string& command) {
    session.addTransformation(Transformation(command));
}

void CommandHandler::undoCommand(Session& session) {
    session.undo();
}

void CommandHandler::redoCommand(Session& session) {
    session.redo();
}

void CommandHandler::saveAsCommand(Session& session, const std::vector<std::string>& fileNames) {
    std::vector<std::string> generatedNames = generateOutputFilenames(session, fileNames);

    try {
        SaveCommand::applySaveCommand(session, generatedNames);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Could not save file: " << e.what() << '\n';
    }
}

void CommandHandler::listSessionCommand(const Session& session) {
    ListSessionCommand::applyListSessionCommand(session);
}

void CommandHandler::pasteCommand(Session& session, const std::string& srcName, const std::string& destName, size_t posX, size_t posY) {
    PasteCommand::applyPasteCommand(session, srcName, destName, posX, posY);
}

void CommandHandler::exitCommand(std::vector<Session>& sessions) {
    ExitCommand::applyExitCommand(sessions);
}