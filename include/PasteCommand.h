#pragma once
#include "Session.h"
#include "AddCommand.h"
#include "SaveCommand.h"

class PasteCommand {
public:
	static void applyPasteCommand(Session& session, const std::string& srcName, const std::string& destName, size_t posX, size_t posY);
};