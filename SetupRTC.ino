 bool  setupRTC()
 {
	if (eepSettings.debugRTC){
		Serial.println();
		 Serial.println("---- setupRTC()--Begin");
	}

	bool rc = true;
	 bool iStat = rtc.begin();
	 if (!iStat) {
		 if (eepSettings.debugRTC) {
			 Serial.println("Couldn't find RTC");

			 rc = false;
			 }
	 }
	 if (rc == false) {
		 return false;
		 }

	if (eepSettings.debugRTC){
		 Serial.print("rtc begin return code: "); Serial.println(iStat);
	}

	if (eepSettings.setDate) {
		if (eepSettings.debugRTC) {	Serial.println("from Compile Time");}

			rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
			rc = true;
			Serial.println("Should be this time: ");
			Serial.print("Date: "); Serial.print(F(__DATE__));
			Serial.print("   Time: "); Serial.println(F(__TIME__));
			delay(20);

}

	if (eepSettings.setDate2) {
		if (eepSettings.debugRTC) {
			Serial.println("from eeprom");
		}
		//
		// use last stored time in rtc memory - AT24C32 module or eepSettings
		//
		rtc.adjust(DateTime(eepSettings.year, eepSettings.month, eepSettings.day, eepSettings.hour, eepSettings.minutes, eepSettings.seconds));
		rc = true;
	}

	now = rtc.now();  // get time from RTC module
	yearIn = now.year();  //used for posting next reading time on display
	monthIn = now.month();
	dayIn = now.day();
	hoursIn = now.hour();
	minutesIn = now.minute();
	secondsIn = now.second();
	
if (eepSettings.debugRTC){
	 Serial.println("---- setupRTC()--End");
}
return rc;
  }
 