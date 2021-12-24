#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "makeFile.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <stdlib.h>
#include <sndfile.hh>


//static LPALCLOOPBACKOPENDEVICESOFT alcLoopbackOpenDeviceSOFT;
static LPALCRENDERSAMPLESSOFT alcRenderSamplesSOFT;

int main()
{
	printf("starting...\n");

	/*alcLoopbackOpenDeviceSOFT = (LPALCLOOPBACKOPENDEVICESOFT)alcGetProcAddress(NULL, "alcLoopbackOpenDeviceSOFT");*/
	
	SoundDevice * mysounddevice = SoundDevice::get(); // Create Loopback Listener Device

	// Setup Loopback sample rendering
	alcRenderSamplesSOFT = (LPALCRENDERSAMPLESSOFT)alcGetProcAddress(mysounddevice->p_ALCDevice, "alcRenderSamplesSOFT");

	// Load sound effects
	uint32_t /*ALuint*/ sound1 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/cave3.ogg");
	uint32_t /*ALuint*/ sound2 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/launch1.ogg");

	// Set Up Source
	SoundSource mySpeaker;

	// Set source position relative to listener
	mySpeaker.setPosition(0, -10, 0);

	/* Ensure 'buffer' can hold 1024 sample frames when calling (4096
 * bytes for 16-bit stereo). */ // -- sf_count_t is an __int64
	const sf_count_t samplesPerChunk = 1024;
	const sf_count_t channels = 2;
	sf_count_t numItemsToWritePerChunk = samplesPerChunk * channels;
	short samples[samplesPerChunk][channels]{}; // we're rendering floats
	short* psamples = &samples[0][0]; // Pointer to pass by reference to create_file

	// Open the file to write to. ( Use \\ or / for all \ in path )
	const char* path = "C:\\Users\\andre\\source\\repos\\openal-impl-vid1\\OutFiles\\test4.wav";
	SNDFILE* outfile = makeFile::openWAV(path);
	
	mySpeaker.Play(sound2); // Begin playing the sound effect

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

	return 0;
}