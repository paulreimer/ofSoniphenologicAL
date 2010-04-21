/*
 *  ALSample.cpp
 *  Mobile Frameworks
 *
 *  Created by Zach Gage on 9/6/08.
 *  Copyright 2008 stfj. All rights reserved.
 *
 */

#include "SoundEngine.h"
#include "ALSample.h"

ALSample::ALSample()
{
	volume	= 1.0f;
	pitch	= 0.0f;
	pan		= 1.0f;
	stopped	= true;
}

ALSample::~ALSample()
{
	SoundEngine_UnloadEffect(myId);
}

//--------------------------------------------------------------
void
ALSample::play()
{
	SoundEngine_StartEffect(myId);
	stopped = false;
}

//--------------------------------------------------------------
void
ALSample::stop()
{
	SoundEngine_StopEffect(myId, false);
	stopped = true;
}

//--------------------------------------------------------------
void
ALSample::stopWithDecay()
{
	SoundEngine_StopEffect(myId, true);
	stopped = true;
}

//--------------------------------------------------------------
void
ALSample::setVolume(float _vol)
{
	volume = _vol;
	SoundEngine_SetEffectLevel(myId, (Float32)volume);
}

//--------------------------------------------------------------
void
ALSample::setPitch(float _pitch)
{
	pitch = _pitch;
	SoundEngine_SetEffectPitch(myId, (Float32)pitch);
}

//--------------------------------------------------------------
void
ALSample::setLocation(float x, float y, float z)
{
	pan = (x+1.0)/2; // this is where im compensating for the scale of oF... (pan in oF is 0-1.0, in ofxAL it's -1.0 to 1.0)
	SoundEngine_SetEffectPosition(myId, x, y, z);
}

//--------------------------------------------------------------
float
ALSample::getPitch()
{
	return pitch;
}

//--------------------------------------------------------------
float
ALSample::getPan()
{
	return pan;
}
