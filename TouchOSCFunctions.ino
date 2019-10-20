
void setDefaults()
	{
	//	 Serial.println("-----------  Setting Defaults _____________");
	if (eepSettings.debugSetup) {
		Serial.println("setDefaults(). . . Begin");
		}

	bool ok = getTime_Date();

	if (eepSettings.debugSetup) {
		//showDate("setup() -- date and Time: ");
		}

	if (ok == false)
		{
		if (eepSettings.debugSetup) {
			Serial.println("invalid date - Stopping");
			}
		//exit;
		}

	refreshRTCoscLabels();

	if (eepSettings.debugSetup) {
		Serial.println("setDefaults(). . .  set page 5 osc");
		}

	oscUpdateLabel(p5_lbstatus_addr, p5_lbstatus_txt);

	oscUpdateLabel(p5_lbdisplaytime_addr, p5_lbdisplaytime_OFF_txt);
	oscUpdateButton(p5_btndisplaytime_addr, false);
	eepSettings.displayTime = false;
	oscUpdateLabel(p3_lbdistancedial_addr, eepSettings.boardDistance);
	oscUpdateLabel(p3_lbdistancefeet_addr, 0);
	oscUpdateLabel(p3_lbdistanceinches_addr, 0);


	if (eepSettings.debugSetup) {
		if (eepSettings.debugSetup) {
			Serial.println(" . .  set debugSetup OSC controls  ON");
			}
		oscUpdateLabel(p5_lbdebugsetup_addr, p5_lbdebugsetup_ON_txt);
		oscUpdateButton(p5_btndebugsetup_addr, true);
		}
	else
		{
		if (eepSettings.debugSetup) {
			Serial.println(" . . .  set debugSetup OSC controls  OFF");
			}
		oscUpdateLabel(p5_lbdebugsetup_addr, p5_lbdebugsetup_OFF_txt);
		oscUpdateButton(p5_btndebugsetup_addr, false);
		}


	if (eepSettings.debugLoop) {
		oscUpdateLabel(p5_lbdebugloop_addr, p5_lbdebugloop_ON_txt);
		oscUpdateButton(p5_btndebugloop_addr, true);
		}
	else
		{
		oscUpdateLabel(p5_lbdebugloop_addr, p5_lbdebugloop_OFF_txt);
		oscUpdateButton(p5_btndebugloop_addr, false);
		}

	if (eepSettings.debugRTC) {
		oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbbdebugrtc_ON_txt);
		oscUpdateButton(p5_btndebugrtc_addr, true);
		}
	else
		{
		oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbbdebugrtc_OFF_txt);
		oscUpdateButton(p5_btndebugrtc_addr, false);
		}

	oscUpdateLabel(p5_lbdebugeeprom_addr, p5_lbdebugeeprom_OFF_txt);
	oscUpdateButton(p5_btndebugeeprom_addr, false);

	oscUpdateLabel(p5_lbsave_addr, p5_lbsave_Yes_txt);
	oscUpdateButton(p5_btnsave_addr, false);
	sk.setWinBy2(eepSettings.winby2);
	if (eepSettings.winby2)
		{
		if (eepSettings.debugSetup) {
			Serial.println(" . .  set win By 2 OSC controls  ON");
			}
		oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_ON_txt);
		oscUpdateButton(p5_btnwinby2_addr, true);
		}
	else
		{
		if (eepSettings.debugSetup) {
			Serial.println(" . . .  set win By 2 OSC controls  OFF");
			}
		oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_OFF_txt);
		oscUpdateButton(p5_btnwinby2_addr, false);
		}

	sk.setWinByExactScore(eepSettings.exactscore);
	if (eepSettings.exactscore)
		{
		if (eepSettings.exactscore) {
			Serial.println(" . .  set Exact score OSC controls  ON");
			}
		oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_ON_txt);
		oscUpdateButton(p5_btnexactscore_addr, true);
		}
	else
		{
		if (eepSettings.debugSetup) {
			Serial.println(" . . .  set Exact Score  OSC controls  OFF");
			}
		oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_OFF_txt);
		oscUpdateButton(p5_btnexactscore_addr, false);
		}

	if (eepSettings.debugSetup) {
		Serial.println("setDefaults(). . . END");
		}

	}
void oscUpdateLabel(char * adr, char value[])
	{
	//Serial.print("oscUpdateLabel: value: "); Serial.println(value);
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	////delay(120);
	}
void oscUpdateLabel(char * adr, int value)
	{
	char str[10] = "";
	sprintf(str, "%d", value);
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	////delay(120);
	}

void oscUpdateLabel(char * adr, size_t value)
	{
	char str[20] = "";
	sprintf(str, "%d", value);
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	////delay(120);
	}

void oscUpdateLabel(char * adr, double value)
	{

	char str[20] = "";
	sprintf(str, "%6.2f", value);
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	////delay(120);
	}
void oscUpdateLabel(char * adr, float value)
	{

	char str[20] = "";
	sprintf(str, "%3f", value);
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	////delay(120);
	}
void oscUpdateButton(char * adr, byte v)
	{
	OSCMessage msgBtn(adr);
	msgBtn.add(v);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgBtn.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgBtn.empty(); // free space occupied by message
	////delay(120);
	}

void SetRefreshtime(OSCMessage &msg, int addrOffset) {
	refreshRTCoscLabels();
	}

void refreshRTCoscLabels() {
	char str[15] = "";

	if (eepSettings.debugRTC) {
	//	Serial.println("refreshRTCoscLabels() - Refresh was pressed");
		}

	bool ok = getTime_Date();

	//	Serial.print("refresh - Month: "); Serial.print(monthIn); Serial.print("  Day: "); Serial.print(dayIn); Serial.print("  Year: "); Serial.print(yearIn);
	//	Serial.print("  Hour: "); Serial.print(hoursIn); Serial.print("  Minutes: "); Serial.print(minutesIn); Serial.print("  Seconds: "); Serial.println(secondsIn);

//	sprintf(str, "%d", monthIn);
	oscUpdateLabel(p6_lbmonth_addr, monthIn);
//	sprintf(str, "%d", dayIn);
	oscUpdateLabel(p6_lbday_addr, dayIn);
//	sprintf(str, "%d", yearIn);
	oscUpdateLabel(p6_lbyear_addr, yearIn);
	delay(1);
//	sprintf(str, "%d", hoursIn);
	oscUpdateLabel(p6_lbhours_addr, hoursIn);
	delay(1);
//	sprintf(str, "%d", minutesIn);
	oscUpdateLabel(p6_lbminutes_addr, minutesIn);
	refreshRTCdatetinestatuslabel(monthIn, dayIn, yearIn, hoursIn, minutesIn, secondsIn);
	//storeValuesToEeprom();
	}

void setBtndebugsetdatecompileD6(OSCMessage &msg, int addrOffset)
	{

	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	delay(50);

	now = rtc.now();  // get time from RTC module
	hoursIn = now.hour();
	minutesIn = now.minute();
	secondsIn = now.second();
	yearIn = now.year();
	monthIn = now.month();
	dayIn = now.day();
//	sprintf(str10, "%d", monthIn);
	oscUpdateLabel(p6_lbmonth_addr, monthIn);
//	sprintf(str10, "%d", dayIn);
	oscUpdateLabel(p6_lbday_addr, dayIn);
//	sprintf(str10, "%d", yearIn);
	oscUpdateLabel(p6_lbyear_addr, yearIn);
	delay(50);
//	sprintf(str10, "%d", hoursIn);
	oscUpdateLabel(p6_lbhours_addr, hoursIn);
	delay(1);
//	sprintf(str10, "%d", minutesIn);
	oscUpdateLabel(p6_lbminutes_addr, minutesIn);

	//	oscSetDateTimeFromCompileTimeD6();
	}

void setbtnsetdatetimefromeepromD5(OSCMessage &msg, int addrOffset)
	{

	rtc.adjust(DateTime(eepSettings.year, eepSettings.month, eepSettings.day, eepSettings.hour, eepSettings.minutes, eepSettings.seconds));

	delay(50);

	//	oscSetDateTimeFromEEPROMvaluesD5(true); //light the button
	delay(150);
	now = rtc.now();  // get time from RTC module
	hoursIn = now.hour();
	minutesIn = now.minute();
	secondsIn = now.second();
	yearIn = now.year();
	monthIn = now.month();
	dayIn = now.day();
	//sprintf(str10, "%d", monthIn);
	oscUpdateLabel(p6_lbmonth_addr, monthIn);
//	sprintf(str10, "%d", dayIn);
	oscUpdateLabel(p6_lbday_addr, dayIn);
//	sprintf(str10, "%d", yearIn);
	oscUpdateLabel(p6_lbyear_addr, yearIn);
	delay(5);
//	sprintf(str10, "%d", hoursIn);
	oscUpdateLabel(p6_lbhours_addr, hoursIn);
	delay(1);
//	sprintf(str10, "%d", minutesIn);
	oscUpdateLabel(p6_lbminutes_addr, minutesIn);
	}
void p5save(OSCMessage &msg, int addrOffset) {
	static bool t = false;

	switch (t)
		{
		case false:
			oscUpdateLabel(p5_lbsave_addr, p5_lbsave_Saving_txt);
			oscUpdateButton(p5_btnsave_addr, true);
			storeValuesToEeprom();
			t = true;
			delay(150);
			oscUpdateLabel(p5_lbsave_addr, p5_lbsave_Saved_txt);
			//		oscUpdateButton(p5_btnsave_addr, false);
			t = false;
			delay(150);
			oscUpdateLabel(p5_lbsave_addr, p5_lbsave_Yes_txt);
			oscUpdateButton(p5_btnsave_addr, false);
			t = false;
			break;
		default:
			oscUpdateLabel(p5_lbsave_addr, p5_lbsave_Yes_txt);
			oscUpdateButton(p5_btnsave_addr, false);
			t = false;
			break;
		}

	}


void SetDate(OSCMessage &msg, int addrOffset)
	{
	if (eepSettings.debugRTC) {
		Serial.println("SetDate() - Set date was pressed");
		}
	Serial.print("b4 set date - Month: "); Serial.print(eepSettings.month); Serial.print("  Day: "); Serial.print(eepSettings.day); Serial.print("  Year: "); Serial.print(eepSettings.year);
	Serial.print("  Hour: "); Serial.print(hoursIn); Serial.print("  Minutes: "); Serial.print(minutesIn); Serial.print("  Seconds: "); Serial.println(secondsIn);

	oscPage3SetDate();

	Serial.print("After set date - Month: "); Serial.print(monthIn); Serial.print("  Day: "); Serial.print(dayIn); Serial.print("  Year: "); Serial.print(yearIn);
	Serial.print("  Hour: "); Serial.print(hoursIn); Serial.print("  Minutes: "); Serial.print(minutesIn); Serial.print("  Seconds: "); Serial.println(secondsIn);

	delay(10);
	}

void SetTime(OSCMessage &msg, int addrOffset)
	{

	if (eepSettings.debugRTC) {
		Serial.println("SetTime() - Set Time was pressed");
		}
	Serial.print("b4 Set time - Month: "); Serial.print(monthIn); Serial.print("  Day: "); Serial.print(dayIn); Serial.print("  Year: "); Serial.print(yearIn);
	Serial.print("  Hour: "); Serial.print(eepSettings.hour); Serial.print("  Minutes: "); Serial.print(eepSettings.minutes); Serial.print("  Seconds: "); Serial.println(eepSettings.seconds);

	oscPage3SetTime();
	Serial.print("after set time - Month: "); Serial.print(monthIn); Serial.print("  Day: "); Serial.print(dayIn); Serial.print("  Year: "); Serial.print(yearIn);
	Serial.print("  Hour: "); Serial.print(hoursIn); Serial.print("  Minutes: "); Serial.print(minutesIn); Serial.print("  Seconds: "); Serial.println(secondsIn);

	delay(10);
	}

/*
void SetSignTimeOn(OSCMessage &msg, int addrOffset)
{

if (eepSettings.debugRTC) { Serial.println("SetSignTimeOn() - Set Time ON was pressed. "); }

//	CheckLight_1_ON_Hours( eepSettings.TOD_Sign_ON_Hour,eepSettings.TOD_Sign_ON_Minutes, eepSettings.TOD_Sign_OFF_Hour, eepSettings.TOD_Sign_OFF_Minutes);

//	oscPage1( eepSettings.dowIn);
}*/


void GetMonth(OSCMessage &msg, int addrOffset) {

	eepSettings.month = valueIn;							// store for later use
	oscUpdateLabel(p6_lbmonth_addr, valueIn);
	
	}
void setBtnshowinfo(OSCMessage &msg, int addrOffset) {
	//oscPage1(eepSettings.dowIn);
	}

void GetDay(OSCMessage &msg, int addrOffset) {

	eepSettings.day = valueIn;

	oscUpdateLabel(p6_lbday_addr, valueIn);
	}
void GetYear(OSCMessage &msg, int addrOffset) {

	eepSettings.year = valueIn;

	oscUpdateLabel(p6_lbyear_addr, valueIn);
	}
void GetHour(OSCMessage &msg, int addrOffset) {

	eepSettings.hour = valueIn;

	oscUpdateLabel(p6_lbhours_addr, valueIn);
	}
void GetMinutes(OSCMessage &msg, int addrOffset) {

	eepSettings.minutes = valueIn;

	oscUpdateLabel(p6_lbminutes_addr, valueIn);

	}

void GetSeconds(OSCMessage &msg, int addrOffset) {

	eepSettings.seconds = valueIn;

	oscUpdateLabel(p6_lbseconds_addr, valueIn);
	}


void debugloop_Toggle(OSCMessage &msg, int addrOffset)
	{


	switch (eepSettings.debugLoop)
		{
		case false:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbdebugloop_ON_txt);
			oscUpdateLabel(p5_lbdebugloop_addr, p5_lbdebugloop_ON_txt);
			oscUpdateButton(p5_btndebugloop_addr, true);
			eepSettings.debugLoop = true;
			break;
		default:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbdebugloop_OFF_txt);
			oscUpdateLabel(p5_lbdebugloop_addr, p5_lbdebugloop_OFF_txt);
			oscUpdateButton(p5_btndebugloop_addr, false);
			eepSettings.debugLoop = false;
			break;
		}
	}


void debugEEPROM_Toggle(OSCMessage &msg, int addrOffset)
	{
	switch (eepSettings.debugEeprom)
		{
		case false:
		//	oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbdebugeeprom_ON_txt);
			oscUpdateLabel(p5_lbdebugeeprom_addr, p5_lbdebugeeprom_ON_txt);
			oscUpdateButton(p5_btndebugeeprom_addr, true);
			eepSettings.debugEeprom = true;
			break;
		default:
			//oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbdebugeeprom_OFF_txt);
			oscUpdateLabel(p5_lbdebugeeprom_addr, p5_lbdebugeeprom_OFF_txt);
			oscUpdateButton(p5_btndebugeeprom_addr, false);
			eepSettings.debugEeprom = false;
			break;
		}
	}

void debugsetup_Toggle(OSCMessage &msg, int addrOffset)
	{

	switch (eepSettings.debugSetup)
		{
		case false:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbdebugsetup_ON_txt);
			oscUpdateLabel(p5_lbdebugsetup_addr, p5_lbdebugsetup_ON_txt);
			oscUpdateButton(p5_btndebugsetup_addr, true);
			eepSettings.debugSetup = true;   
			break;
		default:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbdebugsetup_OFF_txt);
			oscUpdateLabel(p5_lbdebugsetup_addr, p5_lbdebugsetup_OFF_txt);
			oscUpdateButton(p5_btndebugsetup_addr, false);
			eepSettings.debugSetup = false;
			break;
		}
	}


void displayTime_Toggle(OSCMessage &msg, int addrOffset)
	{
	if (eepSettings.debugRTC) {
		Serial.print("displayTime_Toggle(): "); Serial.println(eepSettings.displayTime);
		}

	switch (eepSettings.displayTime)
		{
		case false:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbstatus_DT_ON_txt);
			oscUpdateLabel(p5_lbdisplaytime_addr, p5_lbdisplaytime_ON_txt);
			oscUpdateButton(p5_btndisplaytime_addr, true);
			eepSettings.displayTime = true;
			oscUpdateLabel(p1_lblstatus_addr, p1_lblstatus_displayTime_txt);      //Waiting on next update
			display_time();
			break;
		default:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbstatus_DT_OFF_txt);
			oscUpdateLabel(p5_lbdisplaytime_addr, p5_lbdisplaytime_OFF_txt);
			oscUpdateButton(p5_btndisplaytime_addr, false);
			eepSettings.displayTime = false;
			setStatusWaiting();
			//oscUpdateLabel(p1_lblstatus_addr, *Waiting_on_next_update);      //Waiting on next update
			break;
		}
	}

void debugRTC_Toggle(OSCMessage &msg, int addrOffset)
	{

	switch (eepSettings.debugRTC)
		{
		case false:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbstatu_debug_RTCs_ON_txt);
			oscUpdateLabel(p5_lbdebugrtc_addr , p5_lbdisplaytime_ON_txt);
			oscUpdateButton(p5_btndebugrtc_addr, true);
			eepSettings.debugRTC = true;
			oscUpdateLabel(p1_lblstatus_addr, p1_lblstatus_displayTime_txt);      //Waiting on next update
			//display_time();
			break;
		default:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbstatu_debug_RTCs_OFF_txt);
			oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbdisplaytime_OFF_txt);
			oscUpdateButton(p5_btndebugrtc_addr, false);
			eepSettings.debugRTC = false;
			setStatusWaiting();
			//oscUpdateLabel(p1_lblstatus_addr, *Waiting_on_next_update);      //Waiting on next update
			break;
		}\
	}
	//switch (eepSettings.debugRTC)
	//	{
	//	case false:
	//		oscUpdateLabel(p5_lbstatus_addr, p5_lbstatu_debug_RTCs_ON_txt);
	//		if (eepSettings.displayTime)
	//			{
	//			oscUpdateLabel(p5_lbdisplaytime_addr, p5_lbdisplaytime_ON_txt);
	//			}
	//		else
	//			{
	//			oscUpdateLabel(p5_lbdisplaytime_addr, p5_lbdisplaytime_OFF_txt);
	//			}

	//		oscUpdateButton(p5_btndebugrtc_addr, true);
	//		eepSettings.debugRTC = true;
	//		break;
	//	default:
	//		oscUpdateLabel(p5_lbstatus_addr, p5_lbstatu_debug_RTCs_OFF_txt);
	//		oscUpdateLabel(p5_lbdebugrtc_addr, p5_lbbdebugrtc_OFF_txt);
	//		oscUpdateButton(p5_btndebugrtc_addr, false);
	//		eepSettings.debugRTC = false;
	//		break;
	//	}
	//}

void forceEEPROM_Init_Toggle(OSCMessage &msg, int addrOffset)
	{
	static bool t = false;

	switch (t)
		{
		case false:

			oscUpdateLabel(p5_lbforceeeprominit_addr, p5_lbforceeeprominit_ON_txt);
			oscUpdateButton(p5_btnforceeeprominit_addr, true);
			setupInitialEepSettings();
			delay(1000);
			eepSettings.FirstEepromSetup = true;
			storeValuesToEeprom();
			oscUpdateLabel(p5_lbforceeeprominit_addr, p5_lbforceeeprominit_OFF_txt);
			delay(500);
			oscUpdateButton(p5_btnforceeeprominit_addr, false);
			delay(500);
			fetchEepromValues();
			setDefaults();
			oscUpdateLabel(p5_lbstatus_addr, p5_lbstatus_force_EEPROM_txt);
			t = false;
			break;

		default:
			oscUpdateLabel(p5_lbstatus_addr, p5_lbforceeeprominit_OFF_txt);
			oscUpdateLabel(p5_lbforceeeprominit_addr, p5_lbforceeeprominit_OFF_txt);
			oscUpdateButton(p5_btnforceeeprominit_addr, false);
			t = false;
			break;
		}
	}

void updateTemp(float t, float hum, float a, float hidx, float p, double dp, int f)
	{
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
	char s[10] = "";

	sprintf(s, "%3.0f", t);
//	Serial.print(s);
	oscUpdateLabel(p2_lbtemp_addr, s);

	sprintf(s, "%3.0f", hum);
//	Serial.print(s);
	oscUpdateLabel(p2_lbhumidity_addr, s);

	sprintf(s, "%3.0f", hidx);
//	Serial.print(s);
	oscUpdateLabel(p2_lbheatindex_addr, s);

	sprintf(s, "%6.2f", a);
	oscUpdateLabel(p2_lbalititude_addr, s);

	sprintf(s, "%6.2f", p);
	oscUpdateLabel(p2_lbpressure_addr, s);

	sprintf(s, "%6.2f", dp);
	oscUpdateLabel(p2_lbdewpoint_addr, s);
	
	char w[100] = "";
	strcpy(w, weather[f]);
	oscUpdateLabel(p2_lbforecast_addr,w);
	}
