#pragma once

#include "settings.h"

#ifdef USE_OGR
#include "ogrsf_frmts.h"
#endif

#include "ofTypes.h"
#include "ofxThread.h"
#include "ofAppRunner.h"

class GeoData
: public ofxThread
{
	friend class SonificationEngine;
public:
	GeoData();
	~GeoData();
	
	void setup();
	void destroy();

	void query(int tag,
			   ofPoint nwCorner,
			   ofPoint seCorner,
			   ofPoint timeInterval);

	void unquery(int tag);
	void clear();

	string dataSourceName;
	string layerName;

protected:
	void threadedFunction();

	struct request_t
	{
		float	latitudeMin,	latitudeMax;
		float	longitudeMin,	longitudeMax;
		int		yearMin,		yearMax;
	};
	
	struct response_t
	{
		map<int, int> offsets;
		ofPoint centroid;
	};
	
private:
	map<int, request_t> requests;
	map<int, response_t> responses;
	
#ifdef USE_OGR
	OGRDataSource	*datasource;
    OGRLayer		*layer;

	OGRPolygon MakeRect(double dfMinX, double dfMinY,
						double dfMaxX, double dfMaxY);
#endif
};
