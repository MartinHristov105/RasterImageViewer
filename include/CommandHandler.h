#pragma once
#include "LoadCommand.h"
#include "SaveCommand.h"
#include "AddCommand.h"
#include "ListSessionCommand.h"
#include "PasteCommand.h"
#include "ExitCommand.h"

class CommandHandler {
public:
    static Session loadCommand(std::vector<std::string>& fileNames);
    static void addCommand(Session& session, std::string& fileName);
    static void transformationCommand(Session& session, const std::string& command);
    static void undoCommand(Session& session);
    static void redoCommand(Session& session);
    static void saveAsCommand(Session& session, const std::vector<std::string>& fileNames);
    static void listSessionCommand(const Session& session);
    static void pasteCommand(Session& session, const std::string& srcName, const std::string& destName, size_t posX, size_t posY);
    static void exitCommand(std::vector<Session>& sessions);
};