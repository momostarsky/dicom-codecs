#include <dicomcodecs/codec.hpp>

void readFile(std::string fileName, std::vector<uint8_t>& vec);
void printImage(const dicomcodecs::image& image);
void readFileAndDecode(const std::string& fileName, const std::string& codec, dicomcodecs::image& image);
void roundTrip(const dicomcodecs::image& image, const std::string& codec, double maxAverageDiff = 0.0);
void readFileAndRoundTrip(const std::string& fileName, const std::string& codec, double maxAverageDiff = 0.0);
void benchmark(dicomcodecs::image& image, const std::string& codec, size_t iterations);
std::string makeRawFileName(const char* name, const dicomcodecs::image& image);
void writeFile(const std::string fileName, const std::vector<uint8_t>& vec);
void readRawFile(const std::string fileName, dicomcodecs::image& image);


void roundTripTests() {
    readFileAndRoundTrip("extern/test-data/jpegls/CT1.JLS", "charls");
    readFileAndRoundTrip("extern/test-data/jpeg2000/CT1.j2k", "openjpeg");
    readFileAndRoundTrip("extern/test-data/jpeglossy8bit/jpeg400jfif.jpg", "libjpeg-turbo", 2.0);
    readFileAndRoundTrip("extern/test-data/jpeglossy12bit/test12.jpg", "ijg12", 2.0);
}

void benchmarkRawFilePath(const std::string& filePath, const std::string& codec, size_t iterations) {
    dicomcodecs::image image;
    readRawFile(filePath, image);
    benchmark(image, codec, iterations);
}

void benchmarkTests() {
    printf("** Running Benchmark Tests **\n");
    dicomcodecs::image image;
    std::string codec("charls");
    size_t iterations = 1;
    benchmarkRawFilePath("extern/test-data/raw/CT1-512-512-1-16-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/CT2-512-512-1-16-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/MG1-3064-4664-1-12-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/MR2-1024-1024-1-12-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/MR3-512-512-1-16-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/MR4-512-512-1-12-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/NM1-256-1024-1-16-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/RG1-1841-1955-1-15-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/RG2-1760-2140-1-10-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/RG3-1760-1760-1-10-0.raw", codec, iterations);
    benchmarkRawFilePath("extern/test-data/raw/SC1-2048-2487-1-12-0.raw", codec, iterations);
}

void makeRawImages() {
    printf("** Creating Raw Images **\n");
    dicomcodecs::image image;
    std::string fileName;
    readFileAndDecode("extern/test-data/jpegls/CT1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/CT1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/CT2.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/CT2", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/MG1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/MG1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

/*    readFileAndDecode("extern/test-data/jpegls/MR1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/MR1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);
*/
    readFileAndDecode("extern/test-data/jpegls/MR2.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/MR2", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/MR3.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/MR3", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/MR4.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/MR4", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/NM1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/NM1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/RG1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/RG1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/RG2.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/RG2", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/RG3.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/RG3", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/SC1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/SC1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);

    readFileAndDecode("extern/test-data/jpegls/XA1.JLS", "charls", image);
    fileName = makeRawFileName("extern/test-data/raw/XA1", image);
    printf("%s\n", fileName.c_str());
    writeFile(fileName, image.rawBytes);
}

int main(int argc, char** argv) 
{
    init();

    //makeRawImages();
    //roundTripTests();
    benchmarkTests();

    //readFileAndDecode("../../chafey/openjphjs/test/fixtures/j2c/CT1.j2c", "openjpeg", image); // HTJ2K


    return 0;
}