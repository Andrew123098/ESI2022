#pragma once
#include <stdlib.h>
#include <vector>
#include <sndfile.hh>

class makeFile
{
public:
	static void create_file(const char* fname, int format, short* buffer, int bufferSize);
	static SNDFILE* openWAV(const char* path);
	static sf_count_t writeWAV(SNDFILE* outfile, float* buffer, sf_count_t numItemsToWrite);
	static void closeWAV(SNDFILE* outfile);
};