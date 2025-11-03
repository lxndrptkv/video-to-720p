#include "converter.h"

int VidConvert::run(int argc, char* argv[]) {
	if (!validateArgs(argc)) {
		waitForEnterKey();
		return 1;
	}

	string inputFilePath = argv[1];
	string outputFilePath = buildOutPath(inputFilePath);
	string command = buildFFMpegCommand(inputFilePath, outputFilePath);

	cout << "Converting \"" << inputFilePath << "\"to 720p with higher compression..."<< endl;
	int result = execCommand(command);

	cout << "\n Conversion finished! Press Enter to exit..." << endl;
	waitForEnterKey();
	return result;
}

bool VidConvert::validateArgs(int argc) {
	if (argc != 2) {
		cerr << "Error: Drag and drop video file onto the .exe to convert." << endl;
		return false;

	}
	return true;
}

string VidConvert::buildOutPath(const string& inputPath) {
	string outputPath = inputPath;
	size_t dotPos = outputPath.find_last_of('.');
	if (dotPos != string::npos) {
		outputPath.insert(dotPos, "_720p24fpsCompressed");
	}
	else {
		outputPath += "_720p24fpsCompressed";
	}
	return outputPath;
}

string VidConvert::buildFFMpegCommand(const string& inputPath, const string& outputPath) {
	return "ffmpeg -i \"" + inputPath + "\" "
		"-vf scale=-1:720 "    // 720p resolution~ ♪
		"-r 24 "               // 24 fps for smooth vibes
		"-c:v h264 "           // H264 codec
		"-preset slow "        // Slow preset for better compression
		"-crf 32 "             // Higher CRF for smaller files
		"-c:a aac -b:a 64k "   // Audio settings
		"\"" + outputPath + "\"";
}

int VidConvert::execCommand(const string& command) {
	return system(command.c_str());
}
void VidConvert::waitForEnterKey() {
	cin.get();
}