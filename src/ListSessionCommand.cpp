#include "ListSessionCommand.h"

void ListSessionCommand::applyListSessionCommand(const Session& session) {
    std::cout << "Files in session with ID " << session.getID() << ":\n";

    for (size_t i = 0; i < session.getImages().size(); ++i) {
        std::string fileName = session.getFileNames()[i];
        std::cout << fileName << " - ";
        if (session.getImages()[i].getFormat() == "P1") {
            std::cout << "portable bitmap format";
        }
        else if (session.getImages()[i].getFormat() == "P2") {
            std::cout << "portable graymap format";
        }
        else if (session.getImages()[i].getFormat() == "P3") {
            std::cout << "portable pixmap format";
        }
        else if (session.getImages()[i].getFormat() == "P4") {
            std::cout << "portable Bitmap (Binary)";
        }
        else if (session.getImages()[i].getFormat() == "P5") {
            std::cout << "portable Graymap (Binary)";
        }
        else if (session.getImages()[i].getFormat() == "P6") {
            std::cout << "portable Pixmap (Binary)";
        }
        else if (session.getImages()[i].getFormat()[0] == 'B' && session.getImages()[i].getFormat()[1] == 'M') {
            std::cout << "24bit Bitmap";
        }
        std::cout << "\n";
    }
}