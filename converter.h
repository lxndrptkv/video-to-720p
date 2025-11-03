#ifndef VIDCON_H
#define VIDCON_H
#include "imports.h"

class VidConvert {
public:
	int run(int argc, char* argv[]);

private:
	bool validateArgs(int argc);
	string buildOutPath(const string& inputPath);
	string buildFFMpegCommand(const string& inputPath, const string& outputPath);
	int execCommand(const string& command);
	void waitForEnterKey();

};

#endif // !VIDCON_H

