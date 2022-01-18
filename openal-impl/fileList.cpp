#include <filesystem>
#include <vector>
#include <iostream>
#include <string.h>
#include "fileList.h"
using namespace std;

// This file contains 1 overloaded function (function and function helper) that, given a directory path,
// recursivly moves through all sub-directories are returns a string vector of all regular files.

// Runs once and calls its helper.
vector<string> fileList::listFilesInDir(std::string inputPath) {
	vector<string> toRet; // Initialize string vector that holds all file paths.
	const std::filesystem::path pathToShow = inputPath; // Convert to path format for filesystem lib.

	// Recursivly loop through directory.
	for (const auto& entry : filesystem::directory_iterator(pathToShow)) {
		const auto filenameStr = entry.path().filename().string(); // Get file or directory name as a string.
		if (entry.is_directory()) { // If directory, add the directoy name to path and recurse into it.
			toRet = fileList::listFilesInDirHelper(inputPath+"\\"+filenameStr, toRet);
		}
		else if (entry.is_regular_file()) { // If File, add file path to vector.
			toRet.push_back(inputPath + "\\" + filenameStr);
		}
		else // If neither directory nor file, print ??
			cout << "??    " << filenameStr << '\n';
	}

	//vector<string> toRet = fileList::list;
	return toRet;
}

// Is called by above function and calls itself multiple times to recursivly move through sub-directories.
vector<string> fileList::listFilesInDirHelper(std::string inputPath, std::vector<std::string> toRet) {
	const std::filesystem::path pathToShow = inputPath;

	for (const auto& entry : filesystem::directory_iterator(inputPath)) {
		const auto filenameStr = entry.path().filename().string(); // Get file or directory name as a string.
		if (entry.is_directory()) { // If directory, add the directoy name to path and recurse into it.
			fileList::listFilesInDirHelper(inputPath + "\\" + filenameStr, toRet);
		}
		else if (entry.is_regular_file()) { // If File, add file path to vector.
			toRet.push_back(inputPath + "\\" + filenameStr);
		}
		else // If neither directory nor file, print ??
			cout << "??    " << filenameStr << '\n';
	}
	return toRet;
}

string fileList::getFileFromPath(string pathString) {
	int found = pathString.string::find_last_of("/\\");
	string subStr = pathString.string::substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(found) + 1, pathString.size());
	for (int i = 0; i < 4; i++) {
		subStr.pop_back();
	}
	return subStr;
}
