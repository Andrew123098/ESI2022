#pragma once
#include <AL\alc.h>
#include <AL\al.h>

class SoundListener
{
public:
	SoundListener();
	~SoundListener();

	void Play(const ALuint buffer_to_play);
	void setPosition(ALfloat xpos, ALfloat ypos, ALfloat zpos);

private:
	ALuint p_Listener;
	float p_Gain = 1.f;
	float p_Orientation = 1.f;
	float p_Position[3] = { 0,0,0 };
	float p_Velocity[3] = { 0,0,0 };
};
