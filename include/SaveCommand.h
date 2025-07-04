#pragma once
#include "Saver.h"
#include "Session.h"

class SaveCommand {
public:
	static void applySaveCommand(Session& session, const std::vector<std::string>& fileNames);
private:
	static Session applyAllTransformations(Session& session); // helper function
};