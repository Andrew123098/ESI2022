#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <stdlib.h>
#include <iostream>

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
	std::vector<float> data; // were rendering floats
	data.resize(1024 * 2); // 1024 stereo sample frames
	
	alcRenderSamplesSOFT(mysounddevice->p_ALCDevice, data.data(), 1024);
	std::cout << "got here2" << std::endl;
	//ALCboolean isSupported = alcIsRenderFormatSupportedSOFT();
	
	mySpeaker.Play(sound1);
	mySpeaker.Play(sound2);

	
	std::cout << "got here\n";


	return 0;
}