#include "imports.h"

int main(int argc, char* argv[]) {
    // Check if file is dragged
    if (argc != 2) {
        cerr << "Error: Drag and drop a video file onto the .exe to convert it to 720p.\n";
        return 1;
    }
    string inputFilePath = argv[1];


    // slaga 720p do originalnoti ime na videoto
    string outputFilePath = inputFilePath;
    size_t dotPos = outputFilePath.find_last_of('.');
    if (dotPos != string::npos) {
        outputFilePath.insert(dotPos, "_720p");
    }
    else {
        outputFilePath += "_720p";
    }
    //ffmpeg build line
    string command = "ffmpeg -i \"" + inputFilePath + "\" -vf scale=-1:720 -c:v libx264 -preset fast -crf 23 -c:a copy \"" + outputFilePath + "\"";

    //executva
    cout << "Converting \"" << inputFilePath << "\" to 720p...\n";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Conversion successful! Output file: \"" << outputFilePath << "\"\n";
    }
    else {
        cerr << "Error: Conversion failed.\n";
    }

    return result;
}

