#pragma once
#include <AL\al.h>
class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Play(const ALuint buffer_to_play);
	void setPosition(ALfloat xpos, ALfloat ypos, ALfloat zpos);
	ALuint p_Source;

private:
	
	float p_Pitch = 1.f;
	float p_Gain = 1.f;
	float p_Position[3] = { 0,0,0 };
	float p_Velocity[3] = { 0,0,0 };
	bool p_LoopSound = false;
	ALuint p_Buffer = 0;
};

