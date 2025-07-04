#pragma once
#include "Loader.h"
#include "Session.h"

class LoadCommand {
public:
	static Session applyLoadCommand(std::vector<std::string>& fileNames);
};