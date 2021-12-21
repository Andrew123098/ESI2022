#include "SoundDevice.h"
#include <AL\al.h>
#include <AL\alext.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static LPALCLOOPBACKOPENDEVICESOFT alcLoopbackOpenDeviceSOFT;

SoundDevice* SoundDevice::get()
{
	static SoundDevice* snd_device = new SoundDevice();
	return snd_device;
}

SoundDevice::SoundDevice()
{
	alcLoopbackOpenDeviceSOFT = (LPALCLOOPBACKOPENDEVICESOFT)alcGetProcAddress(NULL, "alcLoopbackOpenDeviceSOFT");
	p_ALCDevice = alcLoopbackOpenDeviceSOFT(nullptr); // nullptr = get default device
	
	if (!p_ALCDevice)
		throw("failed to get sound device");

	// Define listener properties (created automatically with device)
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	ALCint attrs[] = {
		/* Standard 16-bit stereo 44.1khz. Can change as desired. */
		ALC_FORMAT_TYPE_SOFT, ALC_SHORT_SOFT,
		ALC_FORMAT_CHANNELS_SOFT, ALC_STEREO_SOFT,
		ALC_FREQUENCY, 44100,

		/* request default HRTF */
		ALC_HRTF_SOFT, ALC_TRUE,
		ALC_HRTF_ID_SOFT, 1,
		AL_SOURCE_RELATIVE, ALC_TRUE, // Define source distance as relative to listener.
		AL_INVERSE_DISTANCE_CLAMPED,  ALC_TRUE, //Use realistic attenuation model.

		/* end-of-list */
		0
	};



	p_ALCContext = alcCreateContext(p_ALCDevice, attrs);  // create context
	if(!p_ALCContext)
		throw("Failed to set sound context");

	if (!alcMakeContextCurrent(p_ALCContext))   // make context current
		throw("failed to make context current");


	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
	printf("Opened \"%s\"\n", name);
	if (!alcIsExtensionPresent(NULL, "ALC_SOFT_loopback"))
		std::cout << "Loopback rendering not supported" << std::endl;
	std::cout << "got here1" << std::endl;

}

SoundDevice::~SoundDevice()
{
	if (!alcMakeContextCurrent(nullptr))
		std::cout << "failed to set context to nullptr" << std::endl;

	alcDestroyContext(p_ALCContext);
	if (p_ALCContext)
		std::cout << "failed to unset during close" << std::endl;

	if (!alcCloseDevice(p_ALCDevice))
		std::cout << "failed to close sound device" << std::endl;
}
