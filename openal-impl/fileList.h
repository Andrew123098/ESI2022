#pragma once
#include <filesystem>
#include <vector>
using namespace std;

class fileList {
public:
	static vector<string> listFilesInDir(string inputPath);
	static vector<string> listFilesInDirHelper(string inputPath, vector<string> toRet);
	static string getFileFromPath(string pathString);
};