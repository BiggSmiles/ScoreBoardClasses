// WeatherSetup.h

#ifndef _WEATHERSETUP_h
#define _WEATHERSETUP_h


/*==============================================================================*/


#define SEALEVELPRESSURE_HPA (1020.6)

const char *weather[] = { "stable", "sunny", "cloudy", "unstable", "thunderstorm", "unknown(more time needed)" };
enum FORECAST
	{
	STABLE = 0,			// "Stable Weather Pattern"
	SUNNY = 1,			// "Slowly rising Good Weather", "Clear/Sunny "
	CLOUDY = 2,			// "Slowly falling L-Pressure ", "Cloudy/Rain "
	UNSTABLE = 3,		// "Quickly rising H-Press",     "Not Stable"
	THUNDERSTORM = 4,	// "Quickly falling L-Press",    "Thunderstorm"
	UNKNOWN = 5			// "Unknown (More Time needed)
	};

Adafruit_BME280 bme(0x76);

float lastPressure = -1;
float lastTemp = -1;
int   lastForecast = -1;
const int LAST_SAMPLES_COUNT = 5;
float lastPressureSamples[LAST_SAMPLES_COUNT];
// average value is used in forecast algorithm.
float pressureAvg;
// average after 2 hours is used as reference value for the next iteration.
float pressureAvg2;
float dP_dt;
// this CONVERSION_FACTOR is used to convert from Pa to kPa in forecast algorithm
// get kPa/h be dividing hPa by 10
#define CONVERSION_FACTOR (1.0/10.0)


#endif
