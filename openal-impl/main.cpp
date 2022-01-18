#include <filesystem>
#include <vector>
#include <iostream>
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "makeFile.h"
#include "fileList.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <stdlib.h>
#include <sndfile.hh>
//#include <Windows.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <strsafe.h>

//#include <pybind11/pybind11.h>

using namespace std;

static LPALCRENDERSAMPLESSOFT alcRenderSamplesSOFT;

int main()
{
	printf("starting...\n");

	// PATH TO DIRECTORY CONTAINING ALL MONO-AURAL FILES
	string inputPath = "C:\\Users\\andre\\source\\repos\\openal-impl-vid1\\res\\Minecraft Sound Pack 1.17 - Sound Effects";

	// PATH TO DIRECTORY CONTAINING ALL BINAURAL DIRECTIOANL FILES
	string outputPath = "C:\\Users\\andre\\OneDrive\\Documents\\ESI2022\\MLDatabases";

	// Get list of all sound effects in the directory.
	vector<string> allFilePaths = fileList::listFilesInDir(inputPath);

	// Print all file paths.
	/*for (string i : allFilePaths) {
		cout << i << endl;
	}*/

	for (string i : allFilePaths) {

		SoundDevice* mysounddevice = SoundDevice::get(); // Create Loopback Listener Device

		// Setup Loopback sample rendering
		alcRenderSamplesSOFT = (LPALCRENDERSAMPLESSOFT)alcGetProcAddress(mysounddevice->p_ALCDevice, "alcRenderSamplesSOFT");

		// Load sound effects
		uint32_t /*ALuint*/ sound1 = SoundBuffer::get()->addSoundEffect(i.c_str());

		// Set Up Source
		SoundSource mySpeaker;

		// Set source position relative to listener
		mySpeaker.setPosition(10, 0, 0);

		/* Ensure 'buffer' can hold 1024 sample frames when calling (4096
		 * bytes for 16-bit stereo). */ // -- sf_count_t is an __int64
		const sf_count_t samplesPerChunk = 1024;
		const sf_count_t channels = 2;
		sf_count_t numItemsToWritePerChunk = samplesPerChunk * channels;
		short samples[samplesPerChunk][channels]{}; // we're rendering floats
		short* psamples = &samples[0][0]; // Pointer to pass by reference to create_file

		// Open the file to write to.
		string outFID = fileList::getFileFromPath(i);
		string outFIDwPath = outputPath + "\\" + outFID + ".wav";
		SNDFILE* outfile = makeFile::openWAV(outFIDwPath.c_str());

		mySpeaker.Play(sound1); // Begin playing the sound effect

		ALint state = AL_PLAYING; // Initialize state variable that follows sound device state to end loop.
		int count = 1;
		while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
		{
			// Record directional sound in 1024 audio sample chunks.
			alcRenderSamplesSOFT(mysounddevice->p_ALCDevice, psamples, 1024);

			// Write samples to opened file.
			sf_count_t samplesWritten = makeFile::writeWAV(outfile, psamples, numItemsToWritePerChunk);

			// Check if sound is done playing.
			alGetSourcei(mySpeaker.p_Source, AL_SOURCE_STATE, &state);
			count++;
		}

		makeFile::closeWAV(outfile);
		cout << outFID << " Done!" << endl;
	}
	cout << "Database Creation Complete!" << endl;
	return 0;
}