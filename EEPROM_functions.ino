/*
*
* Read and write demo of the AT24CX library
* Written by Christian Paul, 2014-11-24
* https://github.com/cyberp/AT24Cx
*
*/


// setup
void I2C_Eeprom_Setup() {
	if (eepSettings.debugEeprom) { Serial.println("\nI2C_Eeprom_Setup()"); }
	//	AT24CX(0, 256);
	AT24CX(1, 256);
	if (eepSettings.debugEeprom) {
		Serial.println("AT24CX read/write demo");
		Serial.println("----------------------");
		Serial.print("AT24C32 DEC Addr: "); Serial.println(AT24CX_ID, DEC);
		Serial.print("AT24C32 HEX Addr: "); Serial.println(AT24CX_ID, HEX);
		Serial.print("AT24C32 BIN Addr: "); Serial.println(AT24CX_ID, BIN);
		Serial.println("----------------------\n");
	}
}



void fetchEepromValues() {
	//
	// from eeprom or esp8266 flash memory
	//   address if 0x57
	//  read the information from the AT24C32 and store in eepSeeting struct
	//
	if (eepSettings.debugEeprom) { Serial.println("fetchEepromValues() - begin fetch"); }
	String str = "";
	char m[10];

	eepSettings.Zone = mem.readInt(sZone);



	eepSettings.FirstEepromSetup = mem.read(sFirstEepromSetup);
	eepSettings.debug = mem.read(sdebug);
	eepSettings.debugEeprom = mem.read(sdebugEeprom);
	eepSettings.debugLoop = mem.read(sdebugLoop);
	eepSettings.debugRTC = mem.read(sdebugRTC);
	eepSettings.hour = mem.read(shour);
	eepSettings.minutes = mem.read(sminutes);
	eepSettings.seconds = mem.read(sseconds);
	eepSettings.month = mem.read(smonth);
	eepSettings.day = mem.read(sday);
	eepSettings.year = mem.readInt(syear);

	eepSettings.boardDistance = mem.read(sboarddistance);

	eepSettings.dayLightSavesChange = mem.read(sdayLightSavesChange);



	if (eepSettings.debugEeprom) { printEepsettings("debugEEPROM on"); }
	if (eepSettings.debugEeprom) { Serial.println("fetchEepromValues() - end fetch"); }
}



void storeValuesToEeprom() {
	if (eepSettings.debugEeprom) { Serial.println("\nstoreValuesToEeprom() - begin store"); }
	int si = 0;
	byte b = 0;
	char m[10];  //used for dates
	String str = "";

	si = mem.readInt(sZone);		// zone
	if (si != eepSettings.Zone) { mem.writeInt(sZone, eepSettings.Zone); }

	delay(1);

	b = mem.read(sFirstEepromSetup);
	if (b != eepSettings.FirstEepromSetup) { mem.write(sFirstEepromSetup, eepSettings.FirstEepromSetup); }
	delay(1);
	b = mem.read(sdebug);
	if (b != eepSettings.debug) { mem.write(sdebug, eepSettings.debug); }
	delay(1);
	b = mem.read(sdebugEeprom);
	if (b != eepSettings.debugEeprom) { mem.write(sdebugEeprom, eepSettings.debugEeprom); }
	delay(1);
	b = mem.read(sdebugLoop);
	if (b != eepSettings.debugLoop) { mem.write(sdebugLoop, eepSettings.debugLoop); }
	delay(1);
	b = mem.read(sdebugRTC);
	if (b != eepSettings.debugRTC) { mem.write(sdebugRTC, eepSettings.debugRTC); }
	b = mem.read(smonth);
	if (b != eepSettings.month) { mem.write(smonth, eepSettings.month); }
	delay(1);
	b = mem.read(sday);
	if (b != eepSettings.day) { mem.write(sday, eepSettings.day); }
	delay(1);
	b = mem.read(shour);
	if (b != eepSettings.hour) { mem.write(shour, eepSettings.hour); }
	delay(1);
	b = mem.read(sminutes);
	if (b != eepSettings.minutes) { mem.write(sminutes, eepSettings.minutes); }
	delay(1);
	b = mem.read(sseconds);
	if (b != eepSettings.seconds) { mem.write(sseconds, eepSettings.seconds); }
	delay(1);


	b = mem.read(sdayLightSavesChange);
	if (b != eepSettings.dayLightSavesChange) { mem.write(sdayLightSavesChange, eepSettings.dayLightSavesChange); }
	delay(1);
	
	si = mem.readInt(syear);		// zone
	if (si != eepSettings.year) { mem.writeInt(syear, eepSettings.year); }

	si = mem.readInt(sboarddistance);		// use to set board distance
	if (si != eepSettings.boardDistance) {
		mem.write(sboarddistance, eepSettings.boardDistance);
		}
	b = mem.read(swinby2);
	if (b != eepSettings.winby2) {
		mem.write(swinby2, eepSettings.winby2);
		}
	delay(1);
	b = mem.read(sexactscore);
	if (b != eepSettings.exactscore) {
		mem.write(sexactscore, eepSettings.exactscore);
		}
	delay(1);




	delay(1);
	if (eepSettings.debugEeprom) { Serial.println("storeValuesToEeprom() - end store"); }
}


void setupInitialEepSettings()
{
	if (eepSettings.FirstEepromSetup == false) { return; }

	int Zone = -6;					// time zone offset -5 est and -6 dst
	eepSettings.FirstEepromSetup = true;		// if 0 then eeprom initializtion occurrs

	eepSettings.setDate = 0;		// if true will set to compile date
	eepSettings.setDate2 = 0;		// if true will set to coded date

	eepSettings.debug = 0;				// set to  0 for off and 1 for on
	eepSettings.debugEeprom = 0;			// set to  0 for off and 1 for on
	eepSettings.debugLoop = 0;			// set to  0 for off and 1 for on
	eepSettings.debugRTC = 0;			// set to  0 for off and 1 for on
	eepSettings.month = 10;
	eepSettings.day = 1;
	eepSettings.year = 2017;
	eepSettings.hour = 19;
	eepSettings.minutes = 30;
	eepSettings.seconds = 10;
	eepSettings.hour = 10;  // last saved hour
	eepSettings.minutes = 20;  // last saved minutes
	eepSettings.seconds = 30;  // last saved seconds
	eepSettings.month = 7;  // last saved month
	eepSettings.day = 30;  // last saved day
	eepSettings.year = 2017;  // last saved year
	eepSettings.boardDistance = 26;  // board distance
	eepSettings.dayLightSavesChange = false;  // Manual Sign light test
	eepSettings.winby2 = false;
	eepSettings.exactscore = false;

}
void printEepsettings(String s)
{
	Serial.println(""); Serial.println(s); Serial.println("");
	Serial.print("Zone: "); Serial.println(eepSettings.Zone);
	Serial.print("setDate: "); Serial.println(eepSettings.setDate);
	Serial.print("setDate2: "); Serial.println(eepSettings.setDate2);

	Serial.print("FirstEepromSetup: "); Serial.println(eepSettings.FirstEepromSetup);
	Serial.print("debug: "); Serial.println(eepSettings.debug);
	Serial.print("debugEeprom: "); Serial.println(eepSettings.debugEeprom);
	Serial.print("debugLoop: "); Serial.println(eepSettings.debugLoop);
	Serial.print("eepSettings.month: "); Serial.println(eepSettings.month);
	Serial.print("eepSettings.day: "); Serial.println(eepSettings.day);
	Serial.print("eepSettings.year: "); Serial.println(eepSettings.year);
	Serial.print("eepSettings.hour: "); Serial.println(eepSettings.hour);
	Serial.print("eepSettings.minutes: "); Serial.println(eepSettings.minutes);
	Serial.print("eepSettings.seconds: "); Serial.println(eepSettings.seconds);


	Serial.print("hour: "); Serial.println(eepSettings.hour);
	Serial.print("minutes: "); Serial.println(eepSettings.minutes);
	Serial.print("seconds: "); Serial.println(eepSettings.seconds);
	Serial.print("month: "); Serial.println(eepSettings.month);
	Serial.print("day: "); Serial.println(eepSettings.day);
	Serial.print("year: "); Serial.println(eepSettings.year);

	Serial.print("Board Distance: "); Serial.println(eepSettings.boardDistance);
	Serial.print("Win By 2: "); Serial.println(eepSettings.winby2);
	Serial.print("Exact Score: "); Serial.println(eepSettings.exactscore);

	Serial.print("dayLightSavesChange: "); Serial.println(eepSettings.dayLightSavesChange);
}