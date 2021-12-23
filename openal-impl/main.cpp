#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "makeFile.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <stdlib.h>
#include <iostream>
#include <sndfile.hh>

//static LPALCLOOPBACKOPENDEVICESOFT alcLoopbackOpenDeviceSOFT;
static LPALCRENDERSAMPLESSOFT alcRenderSamplesSOFT;

int main()
{
	std::cout << "starting...\n";

	/*alcLoopbackOpenDeviceSOFT = (LPALCLOOPBACKOPENDEVICESOFT)alcGetProcAddress(NULL, "alcLoopbackOpenDeviceSOFT");*/
	

	/*ALCcontext* context = alcCreateContext(loopbackDevice, attrs);
	alcMakeContextCurrent(context);*/
	
	SoundDevice * mysounddevice = SoundDevice::get(); // Create Loopback Listener Device

	// Setup Loopback sample rendering
	alcRenderSamplesSOFT = (LPALCRENDERSAMPLESSOFT)alcGetProcAddress(mysounddevice->p_ALCDevice, "alcRenderSamplesSOFT");

	// Load sound effects
	uint32_t /*ALuint*/ sound1 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/spell.ogg");
	uint32_t /*ALuint*/ sound2 = SoundBuffer::get()->addSoundEffect("../res/spellsounds/magicfail.ogg");

	// Set Up Source
	SoundSource mySpeaker;

	// Set source position relative to listener
	mySpeaker.setPosition(100, 0, 0);

	/* Ensure 'buffer' can hold 1024 sample frames when calling (4096
 * bytes for 16-bit stereo). */
	std::vector<float> samples; // were rendering floats
	samples.resize(1024 * 2); // 1024 stereo sample frames
	
	alcRenderSamplesSOFT(mysounddevice->p_ALCDevice, samples.data(), 1024);
	std::cout << "got here1" << std::endl;
	//ALCboolean isSupported = alcIsRenderFormatSupportedSOFT();
	
	mySpeaker.Play(sound1);
	//mySpeaker.Play(sound2);
	ALint state = AL_PLAYING;
	std::cout << "playing sound\n";
	while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		std::cout << "currently playing sound\n";

		alcRenderSamplesSOFT(mysounddevice->p_ALCDevice, samples.data(), 1024);
		//... encode / write the 1024 more sample frames to disk here ...
		makeFile::create_file("test.wav", SF_FORMAT_WAV | SF_FORMAT_PCM_16);

			alGetSourcei(mySpeaker.p_Source, AL_SOURCE_STATE, &state);
	}
	
	std::cout << "got here2" << std::endl;

	/*for (float i : data)
		std::cout << data.at(i) << ',';*/

	return 0;
}