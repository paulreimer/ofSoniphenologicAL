/*
 *  ALSequencer.cpp
 *  Mobile Frameworks
 *
 *  Created by Zach Gage on 9/6/08.
 *  Copyright 2008 stfj. All rights reserved.
 *
 */

#include "ALSequencer.h"
#include "SoundEngine.h"

ALSequencer::ALSequencer()
{
	OSStatus err = SoundEngine_Initialize(44100);
	
	if(err)
	{
		printf("ERROR failed to initialize soundEngine.");
	}
	else
	{
		printf("SoundEngine initialized \n");
		numSounds = 0;

		OSStatus err = SoundEngine_SetListenerPosition(0.0f, 0.0f, 0.0f);

		if(err)
		{
			printf("ERROR failed to set listener position..\n (if you are running in the simulator, this is normal, sounds won't work.) \n");
		}

//		SoundEngine_SetMasterVolume(0.8f);
	}
}

ALSequencer::~ALSequencer()
{
	SoundEngine_Teardown();		
}

//--------------------------------------------------------------
void
ALSequencer::loadSound(string tag, string fileName)
{
	UInt32 id = GetNextID();
	SoundEngine_LoadEffect(ofToDataPath(fileName).c_str(), &id);

	samples[tag] = new ALSample();
	samples[tag]->myId = id;
}

//--------------------------------------------------------------
void
ALSequencer::loadSoundFromData(string tag, int * data, int dataSize, int dataSampleRate, bool looping)
{
	UInt32 id = GetNextID();
	SoundEngine_LoadEffectFromData(data, dataSize, dataSampleRate, looping, &id);

	samples[tag] = new ALSample();
	samples[tag]->myId = id;
}

//--------------------------------------------------------------
void
ALSequencer::unloadSound(string tag)
{
	samples.erase(tag);
}

//--------------------------------------------------------------
void
ALSequencer::vibrate()
{
//	SoundEngine_Vibrate();
}

//--------------------------------------------------------------
void
ALSequencer::SetListenerLocation(float x, float y, float z){
	SoundEngine_SetListenerPosition(x, y, z);
}

//--------------------------------------------------------------
void
ALSequencer::SetListenerVelocity(float x, float y, float z){
	SoundEngine_SetListenerVelocity(x, y, z);
}

//--------------------------------------------------------------
void
ALSequencer::SetListenerGain(float gain)
{
	SoundEngine_SetListenerGain(gain);
}

//--------------------------------------------------------------
void
ALSequencer::SetListenerPitch(float pitch)
{
	//SoundEngine_SetListenerPitch(pitch);
}

//--------------------------------------------------------------
void
ALSequencer::SetReferenceDistance(float dist)
{
	SoundEngine_SetReferenceDistance(dist);
}

//--------------------------------------------------------------
void
ALSequencer::SetMaxDistance(float dist)
{
	SoundEngine_SetMaxDistance(dist);
}

//--------------------------------------------------------------
UInt32
ALSequencer::GetNextID()
{
	return numSounds++;
}
