#pragma once
#include <AL\alc.h>

class SoundDevice
{
public:
	static SoundDevice* get();
	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;

private:
	SoundDevice();
	~SoundDevice();

	float listenerPos[3] = {0.0,0.0,0.0};
	float listenerVel[3] = {0.0,0.0,0.0};
	float listenerOri[6] = {0.0,0.0,-1.0,0.0,1.0,0.0};

};

