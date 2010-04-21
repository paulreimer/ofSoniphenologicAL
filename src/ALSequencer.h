#pragma once

#include "ofUtils.h"
//#include <CoreAudio/CoreAudioTypes.h>
#include "ALSample.h"

#include <map>

class ALSequencer
{
public:
	ALSequencer();
	~ALSequencer();
	
	void	loadSound(string tag, string fileName);
	void	loadSoundFromData(string tag, int * data, int dataSize, int dataSampleRate, bool looping);
	void	unloadSound(string tag);
	
	void	vibrate();

	void	SetListenerLocation(float x, float y, float z);
	void	SetListenerVelocity(float x, float y, float z);

	void	SetListenerGain(float gain);
	void	SetListenerPitch(float pitch);

	void	SetReferenceDistance(float dist); // sets the distance after which attenuation is applied
	void	SetMaxDistance(float dist); // sets the maximum distance for which attenuation is applied
	
	static void initializeSoundEngine();				
	static void closeSoundEngine();	

	UInt32 GetNextID();

	std::map<string, ALSample*> samples;
private:
	UInt32 numSounds;
};
