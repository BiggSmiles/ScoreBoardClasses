
//
//  do the time stuff
//

//******************************************************** set Hour  *********************
void oscPage3Hour(byte v)
{
	//Serial.print("Get Hours: "); Serial.println(oschoursIn);
	//sprintf(str1, "%d", v);
	//strcpy(str, str1);

	oscUpdateLabel(p6_lbhours_addr, v);
}
//******************************************************** set Minutes  *********************
void oscPage3Minutes( byte v)
{
	//Serial.print("Get Minutes: "); Serial.println(oscminutesIn);
//	sprintf(str1, "%d", v);
//	strcpy(str, str1);
	oscUpdateLabel(p6_lbminutes_addr, v);
}


//******************************************************** set Seconds  *********************
void oscPage3Seconds( byte v)
{
	//Serial.print("Get Secounds: "); Serial.println(oscsecondsIn);
////	sprintf(str1, "%d", v);
//	strcpy(str, str1);
	oscUpdateLabel(p6_lbseconds_addr, v);
}


void refreshRTCdatetinestatuslabel(byte m, byte d, int y, byte h, byte m1, byte s)
{

	char str15[15];
	char str75[75];
	strcpy(str75, "Date: ");
	sprintf(str15, "%d", m);
	if (m < 10) { strcat(str75, "0"); }

	strcat(str75, str15);
	strcat(str75, "/");

	if (d < 10) { strcat(str75, "0"); }

	sprintf(str15, "%d", d);
	strcat(str75, str1);


	strcat(str75, "/");
	sprintf(str15, "%d", y);
	strcat(str75, str15);

	strcat(str75, " - Time: ");

	if (h < 10) {strcat(str75, "0");}
	sprintf(str15, "%d", h);

	strcat(str75, str15);

	strcat(str75, ":");

	if (m1 < 10) { strcat(str75, "0"); }

	sprintf(str15, "%d", m1);
	strcat(str75, str1);

		strcat(str75, ":");

	if (s < 10) {strcat(str75, "0");}

	sprintf(str15, "%d", s);
	strcat(str75, str15);
	if (eepSettings.dayLightSavesChange)
	{
		strcat(str75, " - DST");
	}
	else
	{
		strcat(str75, " - EST");
	}
	oscUpdateLabel(p6_lbdate_addr, str75);
}
void oscPage3SetDate()
{


	// use date data from touchosc and the current time data from the rtc clock

	rtc.adjust(DateTime(eepSettings.year, eepSettings.month, eepSettings.day, hoursIn, minutesIn, secondsIn));
	delay(100);

	bool ok = getTime_Date();

/*	sprintf(str, "%d", monthIn);
	oscUpdateLabel(p6_lbmonth_addr, str);

	sprintf(str, "%d", dayIn);
	oscUpdateLabel(p6_lbday_addr, str);

	sprintf(str, "%d", yearIn);
	oscUpdateLabel(p6_lbyear_addr, str);

	sprintf(str, "%d", hoursIn);
	oscUpdateLabel(p6_lbhours_addr, str);

	sprintf(str, "%d", minutesIn);
	oscUpdateLabel(p6_lbminutes_addr, str);

	sprintf(str, "%d", secondsIn);
	oscUpdateLabel(p6_lbseconds_addr, str);
	*/

	refreshRTCdatetinestatuslabel(monthIn, dayIn, yearIn, hoursIn, minutesIn, secondsIn);
}

void oscPage3SetTime()
{
/*
	now = rtc.now();  // get time from RTC module
	yearIn = now.year();
	monthIn = now.month();
	dayIn = now.day();
*/
	//  set the time from the touchosc data and the date info from the rtc module

	bool ok = getTime_Date();
	refreshRTCdatetinestatuslabel(monthIn, dayIn, yearIn, hoursIn, minutesIn, secondsIn);

	delay(10);
}
void display_time() {
	getTime_Date();
	pushDataOutToDisplay(hoursIn, minutesIn);
	DisplayNumber(minutesIn / 10);  // team 2 seq 2 - side 2
	DisplayNumber(minutesIn % 10);  // team 2 seq 1 - side 2

									//	Serial.print("T1 Seg 2- side 2: "); Serial.print(minutesIn/10); Serial.print("  team 1 seq 1 - side 2 > "); Serial.println(minutesIn%10);
	DisplayNumber(hoursIn / 10);   // team 1 seq 2 - side 2
	DisplayNumber(hoursIn % 10);   // team 1 seq 1 - side 2


	DisplayNumber(minutesIn / 10);  // team 2 seq 2 - side 1
	DisplayNumber(minutesIn % 10);  // team 2 seq 1 - side 1

									//	 Serial.print("T1 Seg 2- side 1: "); Serial.print(hoursIn/10); Serial.print("  team 1 seq 1 - side 1 > "); Serial.println(hoursIn%10);
	DisplayNumber(hoursIn / 10);   // team 1 seq 2 - side 1
	DisplayNumber(hoursIn % 10);   // team 1 seq 1 - side 1
	
	}
