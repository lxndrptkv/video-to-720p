#include "imports.h"

int main(int argc, char* argv[]) {
    // Check if file is dragged
    if (argc != 2) {
        cerr << "Error: Drag and drop a video file onto the .exe to convert it to 720p.\n";
        return 1;
    }
    string inputFilePath = argv[1];

    // Append "_720p24fpsCompressed" to the original video name
    string outputFilePath = inputFilePath;
    size_t dotPos = outputFilePath.find_last_of('.');
    if (dotPos != string::npos) {
        outputFilePath.insert(dotPos, "_720p24fpsCompressed");
    }
    else {
        outputFilePath += "_720p24fpsCompressed";
    }

    // FFmpeg command with more compression
    string command = "ffmpeg -i \"" + inputFilePath + "\" "
        "-vf scale=-1:720 "          // 720p
        "-r 24 "                     // 24 fps
        "-c:v libx264 "              // H264 codec
        "-preset slow "            // Slow preset for compression
        "-crf 32 "                   // Higher CRF for more compression
        "-c:a aac -b:a 64k "         // audio 
        "\"" + outputFilePath + "\"";

    // Execute
    cout << "Converting \"" << inputFilePath << "\" to 720p with higher compression...\n";
    int result = system(command.c_str());


    return result;

}

