#pragma once
#include <sstream>
#include "CommandHandler.h"

class RasterImagesViewer {
public:
    void run(); // main interactive loop for the Raster Images Viewer application
private:
    std::vector<Session> sessions;
    size_t currentSessionIndex = -1;
};