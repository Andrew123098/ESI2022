#include "makeFile.h"
#include <sndfile.hh>
#include <stdlib.h>
#include <vector>

//constexpr auto BUFFER_LEN = 1024;

void makeFile::create_file(const char* fname, int format, short* buffer, int bufferSize)
{
	//static short buffer[BUFFER_LEN];
	SndfileHandle file;
	int channels = 2;
	int srate = 41000;

	printf("Creating file named '%s'\n", fname);

	// Create .wav file
	file = SndfileHandle(fname, SFM_WRITE, format, channels, srate);
	
	// Copies the value of the second param to the first 3rd-param-many characters of the object pointed to by the 1st param.
	// Not sure what (if anything) this is actually doing. (See: https://github.com/libsndfile/libsndfile/blob/master/examples/sndfilehandle.cc)
	//memset(buffer, 0, sizeof(buffer));  

	// Write the defined file to hard disk.
	file.write(buffer, bufferSize);

	puts("");
	/*
	**	The SndfileHandle object will automatically close the file and
	**	release all allocated memory when the object goes out of scope.
	**	This is the Resource Acquisition Is Initailization idom.
	**	See : http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
	*/
} /* create_file */

SNDFILE* makeFile::openWAV(const char* path) {
	// Define file metadata and format.
	SF_INFO sfinfo{};
	sfinfo.channels = 2;
	sfinfo.samplerate = 44100;
	sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

	// Create file for writing.
	SndfileHandle file = SndfileHandle(path, SFM_WRITE, sfinfo.format, sfinfo.channels, sfinfo.samplerate);
	
	// Open file for writing and create pointer to file location.
	SNDFILE* outfile = sf_open(path, SFM_WRITE, &sfinfo);

	// Return pointer to file location.
	return outfile;
}

sf_count_t makeFile::writeWAV(SNDFILE* outfile, float* buffer, sf_count_t numItemsToWrite) {
	// Call Write function
	sf_count_t numItemsWritten = sf_write_float(outfile, buffer, numItemsToWrite);
	return numItemsWritten;
}

void makeFile::closeWAV(SNDFILE* outfile) {
	// Sync output buffers with open file.
	sf_write_sync(outfile);
	
	// Close data stream.
	sf_close(outfile);
}

