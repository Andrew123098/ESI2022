#include "makeFile.h"
#include <sndfile.hh>

#define		BUFFER_LEN		1024

static void create_file(const char* fname, int format)
{
	static short buffer[BUFFER_LEN];

	SndfileHandle file;
	int channels = 2;
	int srate = 41000;

	printf("Creating file named '%s'\n", fname);

	file = SndfileHandle(fname, SFM_WRITE, format, channels, srate);

	memset(buffer, 0, sizeof(buffer));

	file.write(buffer, BUFFER_LEN);

	puts("");
	/*
	**	The SndfileHandle object will automatically close the file and
	**	release all allocated memory when the object goes out of scope.
	**	This is the Resource Acquisition Is Initailization idom.
	**	See : http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
	*/
} /* create_file */