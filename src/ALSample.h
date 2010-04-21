#pragma once

#include "ofUtils.h"
#include <CoreAudio/CoreAudioTypes.h>

class ALSample
{
public:
	
	ALSample();
	~ALSample();

	void	play();
	void	stop();
	void	stopWithDecay(); //if you loaded a loop with a decay sound attached you should use this to stop it.

	void	setVolume(float _vol);
	void	setPan(float _pan); // i may not have implemented 
	void	setPitch(float _pitch);
	
	void	setLocation(float x, float y, float z);

	float	getPosition();
	float	getPitch();
	float	getPan();

	float	pan;
	float	pitch;
	float	volume;

	UInt32	myId;	
	bool	stopped;
};
