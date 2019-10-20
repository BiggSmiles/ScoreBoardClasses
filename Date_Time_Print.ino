
void printDate(const char* txt ) {
	Serial.print("---");
	Serial.print(txt);
	Serial.print(' ');
	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(' ');
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	
	Serial.print(" = ");
	Serial.print(now.unixtime());
	Serial.print("s / ");
	Serial.print(now.unixtime() / 86400L);
	Serial.print("d since 1970");
	
	Serial.println();
}

void showTimeSpan(const char* txt, const TimeSpan& ts) {
	if (txt == "*") {
		LapseTimeDiff = " ";
		LapseTimeDiff = LapseTimeDiff + ts.days();
		LapseTimeDiff = LapseTimeDiff + " days ";
		LapseTimeDiff = LapseTimeDiff + ts.hours();
		LapseTimeDiff = LapseTimeDiff + " hours ";
		LapseTimeDiff = LapseTimeDiff + ts.minutes();
		LapseTimeDiff = LapseTimeDiff + " minutes ";
		LapseTimeDiff = LapseTimeDiff + ts.seconds();
		return;
}
		Serial.print(txt);
		Serial.print(" ");
		Serial.print(ts.days(), DEC);
		Serial.print(" days ");
		Serial.print(ts.hours(), DEC);
		Serial.print(" hours ");
		Serial.print(ts.minutes(), DEC);
		Serial.print(" minutes ");
		Serial.print(ts.seconds(), DEC);
		Serial.print(" seconds (");
		Serial.print(ts.totalseconds(), DEC);
		Serial.print(" total seconds)");
		Serial.println();

}