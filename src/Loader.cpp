#include "Loader.h"

int Loader::loadMaxValue(std::istream& is) {
    int maxValue = 0;
    is >> maxValue;
    is.ignore(1024, '\n');

    if (maxValue > 255 || maxValue < 0) { throw std::runtime_error("Corrupted file! Max value should be between 0 and 255!"); }
    return maxValue;
}

Image Loader::loadFile(const std::string& fileName) {
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs) { throw std::runtime_error("Failed to open file: " + fileName); } 

    // Special handle for BMP format 
    char magic[2];
    ifs.read(magic, sizeof(magic));
    if (magic[0] == 'B' && magic[1] == 'M') {
        ifs.seekg(0); 
        return loadBMP("BM", ifs);
    }

    // If not BMP restore srteam
    ifs.seekg(0);

    std::string format;
    ifs >> format;
    ifs.ignore(1024, '\n');

    // Skip # comment in the following formats
    if (format == "P1" || format == "P2" || format == "P3") {
        std::string discard;
        std::getline(ifs, discard);
    }

    size_t width = 0;
    size_t height = 0;
    ifs >> width >> height;
    ifs.ignore(1024, '\n');

    std::vector<std::vector<Pixel>> matrix(height, std::vector<Pixel>(width));
    
    if (format == "P1") { return loadPBM(format, ifs, matrix); }
    if (format == "P2") { return loadPGM(format, ifs, matrix); }
    if (format == "P3") { return loadPPM(format, ifs, matrix); }
    if (format == "P4") { return loadPBMBinary(format, ifs, matrix); }
    if (format == "P5") { return loadPGMBinary(format, ifs, matrix); }
    if (format == "P6") { return loadPPMBinary(format, ifs, matrix); }

    throw std::runtime_error("Unknown format: " + format);
}

Image Loader::loadPBM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    for (size_t x = 0; x < matrix.size(); ++x) {
        for (size_t y = 0; y < matrix[x].size(); ++y) {
            int val;
            is >> val;
            if (val != 0 && val != 1) { throw std::runtime_error("Corrupted file! Some pixel(s) have bigger values than the max value!"); }
            matrix[x][y] = val ? Pixel(255, 255, 255) : Pixel(0, 0, 0); // scale for internal work
        }
    }

    return Image(format, 1, matrix);
}
Image Loader::loadPGM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    int maxVal = loadMaxValue(is);

    for (size_t x = 0; x < matrix.size(); ++x) {
        for (size_t y = 0; y < matrix[x].size(); ++y) {
            int val;
            is >> val;
            if (val > maxVal) { throw std::runtime_error("Corrupted file! Some pixel(s) have bigger values than the max value!"); }
            unsigned char gray = (unsigned char)((val * 255) / maxVal); // scale for internal work
            matrix[x][y] = Pixel(gray, gray, gray);
        }
    }

    return Image(format, maxVal, matrix);
}
Image Loader::loadPPM(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    int maxVal = loadMaxValue(is);

    for (size_t x = 0; x < matrix.size(); ++x) {
        for (size_t y = 0; y < matrix[x].size(); ++y) {
            int r = 0;
            int g = 0;
            int b = 0;
            is >> r >> g >> b;
            if (r > maxVal || g > maxVal || b > maxVal) { throw std::runtime_error("Corrupted file! Some pixel(s) have bigger values than the max value!"); }
            matrix[x][y] = Pixel(
                (unsigned char)((r * 255) / maxVal),
                (unsigned char)((g * 255) / maxVal),
                (unsigned char)((b * 255) / maxVal)
            ); // scale for internal work
        }
    }

    return Image(format, maxVal, matrix);
}

Image Loader::loadPBMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    for (size_t x = 0; x < matrix.size(); ++x) {
        size_t byteCount = (matrix[x].size() + 7) / 8; // number of bytes needed for a row
        std::vector<unsigned char> row(byteCount);
        is.read(reinterpret_cast<char*>(row.data()), byteCount); 

        for (size_t y = 0; y < matrix[x].size(); ++y) {
            int byteIndex = y / 8; // current byte
            int bitIndex = 7 - (y % 8); // the bit that represents the pixel
            bool bit = (row[byteIndex] >> bitIndex) & 1;// shift right to get the bit

            matrix[x][y] = bit ? Pixel(255, 255, 255) : Pixel(0, 0, 0); // scale for internal work
        }
    }

    return Image(format, 1, matrix);
}
Image Loader::loadPGMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    int maxVal = loadMaxValue(is);

    for (size_t x = 0; x < matrix.size(); ++x) {
        for (size_t y = 0; y < matrix[x].size(); ++y) {
            unsigned char grayRaw;
            is.read(reinterpret_cast<char*>(&grayRaw), sizeof(grayRaw));
            unsigned char gray = (unsigned char)((grayRaw * 255) / maxVal); // scale for internal work
            matrix[x][y] = Pixel(gray, gray, gray); // load
        }
    }

    return Image(format, maxVal, matrix);
}
Image Loader::loadPPMBinary(const std::string& format, std::istream& is, std::vector<std::vector<Pixel>>& matrix) {
    int maxVal = loadMaxValue(is);

    for (size_t x = 0; x < matrix.size(); ++x) {
        for (size_t y = 0; y < matrix[x].size(); ++y) {
            unsigned char rgbRaw[3];
            is.read(reinterpret_cast<char*>(rgbRaw), sizeof(rgbRaw));
            matrix[x][y] = Pixel(
                (unsigned char)((rgbRaw[0] * 255) / maxVal),
                (unsigned char)((rgbRaw[1] * 255) / maxVal), // scale for internal work
                (unsigned char)((rgbRaw[2] * 255) / maxVal)
            ); // load
        }
    }

    return Image(format, maxVal, matrix);
}

Image Loader::loadBMP(const std::string& format, std::istream& is) {
    is.clear();
    is.seekg(18, std::ios::beg); // skip the first 18 bytes

    size_t width = 0;
    size_t height = 0;
    is.read(reinterpret_cast<char*>(&width), 4); // read width
    is.read(reinterpret_cast<char*>(&height), 4); // read height

    is.seekg(54, std::ios::beg); // skip the rest of the header

    std::vector<std::vector<Pixel>> matrix(height, std::vector<Pixel>(width));
    size_t rowSize = ((24 * width + 31) / 32) * 4; // row size padded to 4 bytes
    std::vector<unsigned char> row(rowSize);

    // Do not support top-down bitmap

    // Bottom-up bitmap: read rows from bottom to top
    for (int x = height - 1; x >= 0; --x) {
        is.read(reinterpret_cast<char*>(row.data()), rowSize); // reads whole row including padding
        for (size_t y = 0; y < width; ++y) {
            int index = y * 3;
            unsigned char b = row[index];
            unsigned char g = row[index + 1];
            unsigned char r = row[index + 2];
            matrix[x][y] = Pixel(r, g, b); // load
        }
    }

    return Image(format, 255, matrix);
}