#include "Saver.h"

void Saver::saveFile(const Image& image, std::ostream& os) {
    std::string format = image.getFormat();

    if (format[0] == 'B' && format[1] == 'M') { return saveBMP(image, os); }

    os << format << '\n';

    if (format == "P1" || format == "P2" || format == "P3") { os << "#Saved by RasterImagesViewer\n"; }

    os << image.getWidth() << ' ' << image.getHeight() << '\n';

    if (format == "P1") { return savePBM(image, os); }
    if (format == "P2") { return savePGM(image, os); }
    if (format == "P3") { return savePPM(image, os); }
    if (format == "P4") { return savePBMBinary(image, os); }
    if (format == "P5") { return savePGMBinary(image, os); }
    if (format == "P6") { return savePPMBinary(image, os); }
}

void Saver::savePBM(const Image& image, std::ostream& os) {
    for (size_t x = 0; x < image.getHeight(); ++x) {
        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            int val = (p.getR() == 255) ? 1 : 0; // rescale back
            os << val << ' '; // save
        }
        os << '\n';
    }
}
void Saver::savePGM(const Image& image, std::ostream& os) {
    int maxVal = image.getMaxVal();
    os << maxVal << '\n';

    for (size_t x = 0; x < image.getHeight(); ++x) {
        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            int val = (p.getR() * maxVal + 127) / 255; // rescale back to max value range
            os << val << ' '; // save
        }
        os << '\n';
    }
}
void Saver::savePPM(const Image& image, std::ostream& os) {
    int maxVal = image.getMaxVal();
    os << maxVal << '\n';

    for (size_t x = 0; x < image.getHeight(); ++x) {
        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            unsigned int r = (p.getR() * maxVal + 127) / 255;
            unsigned int g = (p.getG() * maxVal + 127) / 255; // rescale back
            unsigned int b = (p.getB() * maxVal + 127) / 255;

            os << r << ' ' << g << ' ' << b << '\n'; // save
        }
    }
}

void Saver::savePBMBinary(const Image& image, std::ostream& os) {
    for (size_t x = 0; x < image.getHeight(); ++x) {
        unsigned char byte = 0; // stores 8 pixels
        int bitCount = 0; // how many are stored

        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            bool bit = p.getR() == 255; // white(1), black(0)
            byte = (byte << 1) | (bit ? 1 : 0); // shift left and store current bit
            ++bitCount;

            if (bitCount == 8) {
                os.write(reinterpret_cast<const char*>(&byte), sizeof(byte)); // write the byte
                byte = 0; // reset
                bitCount = 0; // reset
            }
        }
        if (bitCount > 0) { // if the row width is not divisible by 8 there will be some leftover bits
            byte = byte << (8 - bitCount); // shift to the left
            os.write(reinterpret_cast<const char*>(&byte), sizeof(byte)); // write the byte
        }
    }
}
void Saver::savePGMBinary(const Image& image, std::ostream& os) {
    int maxVal = image.getMaxVal();
    os << maxVal << '\n';

    for (size_t x = 0; x < image.getHeight(); ++x) {
        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            unsigned char gray = (unsigned char)((p.getR() * maxVal + 127) / 255); // rescale back
            os.write(reinterpret_cast<const char*>(&gray), sizeof(gray)); // save
        }
    }
}
void Saver::savePPMBinary(const Image& image, std::ostream& os) {
    int maxVal = image.getMaxVal();
    os << maxVal << '\n';

    for (size_t x = 0; x < image.getHeight(); ++x) {
        for (size_t y = 0; y < image.getWidth(); ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            unsigned char rgb[3];
            rgb[0] = (unsigned char)((p.getR() * maxVal + 127) / 255);
            rgb[1] = (unsigned char)((p.getG() * maxVal + 127) / 255); // rescale back for user
            rgb[2] = (unsigned char)((p.getB() * maxVal + 127) / 255);

            os.write(reinterpret_cast<const char*>(rgb), sizeof(rgb)); // save
        }
    }
}

void Saver::saveBMP(const Image& image, std::ostream& os) {
    size_t width = image.getWidth(); // get the width
    size_t height = image.getHeight(); // get the height

    size_t rowSize = ((24 * width + 31) / 32) * 4;  // row size padded to 4 bytes
    size_t pixelArraySize = rowSize * height; // the size of all pixels
    size_t fileSize = 54 + pixelArraySize;  // 54 bytes BMP header + all pixel size

    // BMP header
    unsigned char header[54]{ 0 }; // everything equals 0

    // Signature "BM"
    header[0] = 'B';
    header[1] = 'M';

    // File size (4 bytes, little-endian)
    header[2] = (unsigned char)(fileSize & 255);
    header[3] = (unsigned char)((fileSize >> 8) & 255);
    header[4] = (unsigned char)((fileSize >> 16) & 255);
    header[5] = (unsigned char)((fileSize >> 24) & 255);

    // Reserved bytes 6-9 are zero

    // Pixel data offset (54 bytes)
    header[10] = 54;

    // Reserved bytes 11-13 are zero

    // DIB header size (40 bytes)
    header[14] = 40;

    // Reserved bytes 15-17 are zero

    // Image width (4 bytes), each line extracts 1 byte of the 32-bit integer
    header[18] = (unsigned char)(width & 255);
    header[19] = (unsigned char)((width >> 8) & 255);
    header[20] = (unsigned char)((width >> 16) & 255);
    header[21] = (unsigned char)((width >> 24) & 255);

    // Image height (4 bytes), each line extracts 1 byte of the 32-bit integer
    header[22] = (unsigned char)(height & 255);
    header[23] = (unsigned char)((height >> 8) & 255);
    header[24] = (unsigned char)((height >> 16) & 255);
    header[25] = (unsigned char)((height >> 24) & 255);

    // Planes (2 bytes)
    header[26] = 1; // required to be 1

    // Bits per pixel (2 bytes)
    header[28] = 24; // color depth, each pixel is stored as 3 bytes (bgr)

    // Compression bytes 30-33 are zero

    // Image data size (4 bytes)
    header[34] = (unsigned char)(pixelArraySize & 255);
    header[35] = (unsigned char)((pixelArraySize >> 8) & 255);
    header[36] = (unsigned char)((pixelArraySize >> 16) & 255);
    header[37] = (unsigned char)((pixelArraySize >> 24) & 255);

    // The rest of header bytes are 0

    // Write header
    os.write(reinterpret_cast<const char*>(header), sizeof(header));

    // Prepare padding bytes
    std::vector<unsigned char> padding(rowSize - width * 3, 0); // (size, default values)

    // Do not support top-down bitmap

    // Bottom-up bitmap: writes rows from bottom to top
    for (int x = height - 1; x >= 0; --x) {
        for (size_t y = 0; y < width; ++y) {
            const Pixel& p = image.getMatrix()[x][y];
            unsigned char bgr[3];
            bgr[0] = p.getB();
            bgr[1] = p.getG();
            bgr[2] = p.getR();

            // BMP stores pixels in BGR order
            os.write(reinterpret_cast<const char*>(bgr), sizeof(bgr)); // save
        }
        os.write(reinterpret_cast<const char*>(padding.data()), padding.size());
    }
}