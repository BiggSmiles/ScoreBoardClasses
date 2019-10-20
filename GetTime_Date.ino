bool  getTime_Date()
{
	now = rtc.now();
	delay(10);
	if (now.day() >= 32)
	{
		if (testModeNo7SegmentAttached) {
			Serial.print("getTime_Date() -- Invalid date returned: day: ");
			Serial.println(now.day());
			}
		return false;
	}

	DateTime now = rtc.now();   // get time from RTC module

	yearIn = now.year();  //used for posting next reading time on display
	monthIn = now.month();
	dayIn = now.day();
	hoursIn = now.hour();
	minutesIn = now.minute();
	secondsIn = now.second();
/*
Serial.print("GetTimeDate() Now month:"); Serial.println(now.month());
	Serial.print("savemonth:"); Serial.println(savemonth);
	Serial.print("monthIn:"); Serial.println(monthIn);
	*/
	delay(10);
	//
	//  format date yyyymmdd  day and motnh 2 digits, zero filled and year to include centry
	// 
	sprintf(str1, "%d", now.year());
	today = str1;
	sprintf(str1, "%d", now.month());
	if (monthIn < 10) today = today + "0";
	today = today + str1;
	sprintf(str1, "%d", now.day());
	if (dayIn < 10) today = today + "0";
	today = today + str1;

	return true;
}
