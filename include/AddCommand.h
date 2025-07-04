#pragma once
#include "Session.h"
#include "Loader.h"

class AddCommand {
public:
	static void applyAddCommand(Session& session, std::string& fileName);
};