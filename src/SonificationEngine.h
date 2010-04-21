#pragma once

#include "settings.h"

#include "ofxMSAInteractiveObject.h"
#include "ofxThread.h"

#include "ALSequencer.h"
#include "GeoData.h"

class SonificationEngine
: public ofxMSAInteractiveObject
, public ofxThread
{
public:
	SonificationEngine(string name = "SonificationEngine");
	void threadedFunction();

	void setup();
	void draw();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);

	ALSequencer sequencer;
	GeoData* geoData;

	float lerpFactor;
	map<int, string> instruments;
private:
	double tickFreq;
	int nTicks;
	int position;
	float smoothedPosition;
};
