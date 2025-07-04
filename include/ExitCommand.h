#pragma once
#include "SaveCommand.h"
#include "Session.h"

class ExitCommand {
public:
    static void applyExitCommand(std::vector<Session>& sessions);
};

// Helper functions
std::string mapFormatToExtension(const std::string& format); 
std::vector<std::string> generateOutputFilenames(const Session& session, const std::vector<std::string>& providedNames);