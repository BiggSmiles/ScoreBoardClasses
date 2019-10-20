


void printValues(float t, float hum, float a, float hidx, float p, double dp, int forecast) {
	char str[15] = "";
	Serial.print("Temperature = ");
	//float C = t;
	sprintf(str, "%4.1f", a);
	Serial.print(str);
	Serial.println(" *F");
	Serial.print("Pressure = ");

	sprintf(str, "%6.1f", p);
	Serial.print(str);
//	Serial.print(p / 100.0F);
//	Serial.println(" hPa");

	Serial.print("Approx. Altitude = ");
	sprintf(str, "%6.1f", a);
	Serial.print(str);
	Serial.println(" ft.");

	Serial.print("Humidity = ");
	sprintf(str, "%3f", hum);
	Serial.print(str);
	Serial.println(" %");

	Serial.print("forecast = ");
	Serial.print(forecast);
	Serial.print(" - ");
	Serial.println(weather[forecast]);

	Serial.println();
}

void ServerUpdate() // used to read sensor data and send it to controller
{
	double T, P, H, A, C;

	if (!bme.begin()) {
		if (testModeNo7SegmentAttached) {
			Serial.println("Could not find a valid BME280 sensor, check wiring!");
			}
		return;
		}


	T = bme.readTemperature();

	P = bme.readPressure() / 100.0;
	H = bme.readHumidity();
	A = bme.readAltitude(SEALEVELPRESSURE_HPA)* 3.28084;

		Serial.print("Temperature = ");
		Serial.print(bme.readTemperature());
		Serial.println(" *C");

		Serial.print("Pressure = ");

		Serial.print(bme.readPressure() / 100.0F);
		Serial.println(" hPa");

		Serial.print("Approx. Altitude = ");
		Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
		Serial.println(" m");

		Serial.print("Humidity = ");
		Serial.print(bme.readHumidity());
		Serial.println(" %");

		Serial.println();
		

//	int forecast = sample(P);
//
//	Serial.print("Forecast index"); Serial.println(forecast);
//	C = T;
////	T = C * 9 / 5 + 32;  //convert to F from C
//
//	Serial.print("T: "); Serial.println(T);
//	T = (T * 2) + 30;  // convert C to F
//
//	// unmark for debuging
//
//Serial.print("T = \t"); Serial.print(T, 1); Serial.print(" degC\t");
//	Serial.print("P = \t"); Serial.print(P, 1); Serial.print(" mBar\t");
//	Serial.print("F = \t"); Serial.print(weather[forecast]); Serial.println(" ?");
//	
//	double dp = dewPoint(C, H);
//	double hi = heatIndex(T, H);
// 
//	printValues(T, H, A, hi, P, dp, forecast);
//	
//	updateTemp(T, H, A, hi, P, dp,  forecast);
}

float getLastPressureSamplesAverage()
{
	int LAST_SAMPLES_COUNT = 20;
	float lastPressureSamplesAverage = 0;
	for (int i = 0; i < LAST_SAMPLES_COUNT; i++)
	{
		lastPressureSamplesAverage += lastPressureSamples[i];
	}
	lastPressureSamplesAverage /= LAST_SAMPLES_COUNT;

	return lastPressureSamplesAverage;
}

// Algorithm found here
// http://www.freescale.com/files/sensors/doc/app_note/AN3914.pdf
// Pressure in hPa -->  forecast done by calculating kPa/h

int sample(float pressure)
{
	// Calculate the average of the last n minutes.
	int index = minuteCount % LAST_SAMPLES_COUNT;
	lastPressureSamples[index] = pressure;

	minuteCount++;
	if (minuteCount > 185)
	{
		minuteCount = 6;
	}

	if (minuteCount == 5)
	{
		pressureAvg = getLastPressureSamplesAverage();
	}
	else if (minuteCount == 35)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) // first time initial 3 hour
		{
			dP_dt = change * 2; // note this is for t = 0.5hour
		}
		else
		{
			dP_dt = change / 1.5; // divide by 1.5 as this is the difference in time from 0 value.
		}
	}
	else if (minuteCount == 65)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) //first time initial 3 hour
		{
			dP_dt = change; //note this is for t = 1 hour
		}
		else
		{
			dP_dt = change / 2; //divide by 2 as this is the difference in time from 0 value
		}
	}
	else if (minuteCount == 95)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) // first time initial 3 hour
		{
			dP_dt = change / 1.5; // note this is for t = 1.5 hour
		}
		else
		{
			dP_dt = change / 2.5; // divide by 2.5 as this is the difference in time from 0 value
		}
	}
	else if (minuteCount == 125)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		pressureAvg2 = lastPressureAvg; // store for later use.
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) // first time initial 3 hour
		{
			dP_dt = change / 2; // note this is for t = 2 hour
		}
		else
		{
			dP_dt = change / 3; // divide by 3 as this is the difference in time from 0 value
		}
	}
	else if (minuteCount == 155)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) // first time initial 3 hour
		{
			dP_dt = change / 2.5; // note this is for t = 2.5 hour
		}
		else
		{
			dP_dt = change / 3.5; // divide by 3.5 as this is the difference in time from 0 value
		}
	}
	else if (minuteCount == 185)
	{
		float lastPressureAvg = getLastPressureSamplesAverage();
		float change = (lastPressureAvg - pressureAvg) * CONVERSION_FACTOR;
		if (firstRound) // first time initial 3 hour
		{
			dP_dt = change / 3; // note this is for t = 3 hour
		}
		else
		{
			dP_dt = change / 4; // divide by 4 as this is the difference in time from 0 value
		}
		pressureAvg = pressureAvg2; // Equating the pressure at 0 to the pressure at 2 hour after 3 hours have past.
		firstRound = false; // flag to let you know that this is on the past 3 hour mark. Initialized to 0 outside main loop.
	}

	int forecast = UNKNOWN;
	if (minuteCount < 35 && firstRound) //if time is less than 35 min on the first 3 hour interval.
	{
		forecast = UNKNOWN;
	}
	else if (dP_dt < (-0.25))
	{
		forecast = THUNDERSTORM;
	}
	else if (dP_dt > 0.25)
	{
		forecast = UNSTABLE;
	}
	else if ((dP_dt > (-0.25)) && (dP_dt < (-0.05)))
	{
		forecast = CLOUDY;
	}
	else if ((dP_dt > 0.05) && (dP_dt < 0.25))
	{
		forecast = SUNNY;
	}
	else if ((dP_dt >(-0.05)) && (dP_dt < 0.05))
	{
		forecast = STABLE;
	}
	else
	{
		forecast = UNKNOWN;
	}

	// uncomment when debugging
	//Serial.print(F("Forecast at minute "));
	//Serial.print(minuteCount);
	//Serial.print(F(" dP/dt = "));
	//Serial.print(dP_dt);
	//Serial.print(F("kPa/h --> "));
	//Serial.println(weather[forecast]);

	return forecast;
}
double heatIndex(double tempF, double humidity)
{
	double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5 = -6.838e-3, c6 = -5.482e-2, c7 = 1.228e-3, c8 = 8.528e-4, c9 = -1.99e-6;
	double T = tempF;
	double R = humidity;

	double A = ((c5 * T) + c2) * T + c1;
	double B = ((c7 * T) + c4) * T + c3;
	double C = ((c9 * T) + c8) * T + c6;

	double rv = (C * R + B) * R + A;
	return rv;
}

double dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO))) - 1);
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1);
	RHS += log10(1013.246);

	// factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

	// (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP / 0.61078); // temp var
	return (241.88 * T) / (17.558 - T);
}
