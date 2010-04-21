#include "SonificationEngine.h"
#include "msaColor.h"
#include "SoundEngine.h"

#define INSTRUMENT_NOTE(i,n) string("instrument"+ofToString(i)+"_note"+ofToString(n))

//--------------------------------------------------------------
SonificationEngine::SonificationEngine(string name)
{
	nTicks		= 0;
	position	= 0;
	lerpFactor	= 0.123;
	tickFreq	= 10;

	disableAllEvents();
	ofAddListener(ofEvents.setup, (ofxMSAInteractiveObject*)this, &ofxMSAInteractiveObject::_setup);
//	ofAddListener(ofEvents.draw, (ofxMSAInteractiveObject*)this, &ofxMSAInteractiveObject::_draw);
}

//--------------------------------------------------------------
void
SonificationEngine::setup()
{
	string filename;
	// Add the MarSystems
	map<int, string>::iterator instr_iter;
	for (instr_iter = instruments.begin(); instr_iter != instruments.end(); instr_iter++)
	{
		int instr = instr_iter->first;

		for (int note=0; note<TIMESTAMP_RANGE_YEARS; note++)
		{
			filename = ofToDataPath(instruments[instr] + "/" + ofToString(note+1) + ".wav");

			sequencer.loadSound(INSTRUMENT_NOTE(instr,note), filename);
		}
	}
	SoundEngine_SetEffectsVolume(0.111f);

	startThread(false, false); // non-blocking, non-verbose
}

//--------------------------------------------------------------
void
SonificationEngine::threadedFunction()
{
	while (isThreadRunning())
	{
		ofSleepMillis(1000.0/tickFreq);

		position = (position+1) % TIMESTAMP_RANGE_DAYS;
		
		string sampleTag;
		
		int year_idx, date_idx;
		int instrument;

#ifdef USE_GEO_DATA
		if (geoData==NULL || geoData->responses.empty())
			continue;

		map<int, GeoData::response_t>::iterator resp_iter;

		map<int, GeoData::response_t>::iterator	instr_iter;
		map<int,int>::iterator					year_iter;

		geoData->lock();
		for (instr_iter = geoData->responses.begin();
			 instr_iter != geoData->responses.end();
			 instr_iter++)
		{
			instrument	= instr_iter->first;
			ofPoint& p	= instr_iter->second.centroid;

			for (year_iter = instr_iter->second.offsets.begin();
				 year_iter != instr_iter->second.offsets.end();
				 year_iter++)
			{
				year_idx	= year_iter->first;
				date_idx	= year_iter->second;

				sampleTag = INSTRUMENT_NOTE(instrument,year_idx);

				if (date_idx == position)
				{
					if (sequencer.samples.find(sampleTag) != sequencer.samples.end())
					{
						sequencer.samples[sampleTag]->setLocation(
							ofMap(p.x, MAP_NW_CORNER_LAT, MAP_SE_CORNER_LAT,	0., 1.),
							ofMap(p.y, MAP_NW_CORNER_LONG, MAP_SE_CORNER_LONG,	0., 1.),
							ofMap(p.z, MIN_MAP_ELEVATION, MAX_MAP_ELEVATION,	0., 1.));

						sequencer.samples[sampleTag]->play();
					}
				}
			}
		}
		geoData->unlock();
#endif
	}
}


//--------------------------------------------------------------
void SonificationEngine::draw()
{
	draw(0,0, ofGetWidth(), ofGetWidth());
}

//--------------------------------------------------------------
void SonificationEngine::draw(float x, float y)
{
	draw(x, y, ofGetWidth(), ofGetWidth());
}

//--------------------------------------------------------------
void SonificationEngine::draw(float x, float y, float w, float h)
{
	int year_idx, date_idx;
	int instrument;
	
#ifdef USE_GEO_DATA
	map<int, GeoData::response_t>::iterator	instr_iter;
	map<int,int>::iterator					year_iter;	
#endif
	
	int roygbiv = 0;
	msaColor color;

	glPushMatrix();
	glTranslatef(x, y+h, 0.);
	glScalef(1., -1., 1.);
	
	ofSetColor(0x777777);
	for (int i=0; i<TIMESTAMP_RANGE_YEARS; i++)
	{
		if (i%2)
			ofSetLineWidth(2.0);
		else
			ofSetLineWidth(1.0);

		ofLine(0, i*(h/TIMESTAMP_RANGE_YEARS),
			   w, i*(h/TIMESTAMP_RANGE_YEARS));
	}
	ofSetLineWidth(1.0);

#ifdef USE_GEO_DATA
	geoData->lock();
	for (instr_iter = geoData->responses.begin();
		 instr_iter != geoData->responses.end();
		 instr_iter++)
	{
		instrument = instr_iter->first;
		roygbiv = (roygbiv+1) % 7;

		color.setHSV(roygbiv*(360./7.), 1., 1., 1.);
		color.setGL();

		for (year_iter = instr_iter->second.offsets.begin();
			 year_iter != instr_iter->second.offsets.end();
			 year_iter++)
		{
			year_idx	= year_iter->first;
			date_idx	= year_iter->second;
			
			ofCircle(ofMap(date_idx, 0, TIMESTAMP_RANGE_DAYS,	0, w),
					 ofMap(year_idx, 0, TIMESTAMP_RANGE_YEARS,	0, h),
					 (h/TIMESTAMP_RANGE_YEARS)-1);
		}
	}
	geoData->unlock();
#endif

	if (position < smoothedPosition)
		smoothedPosition = position;
	else
		smoothedPosition = ofLerp(smoothedPosition, position, lerpFactor);

	float sequencerPos = ofMap(smoothedPosition, 0, TIMESTAMP_RANGE_DAYS, 0, w);
	
	ofSetColor(0xdadada);
	ofSetLineWidth(3.0);
	ofLine(sequencerPos, 0, sequencerPos, h);
	ofSetLineWidth(1.0);

	glPopMatrix();
}
