



#include <PCF8574.h>
#include <Adafruit_BME280.h>
#include <SonicSensor.h>
#include <RTClib.h>
#include "WeatherSetup.h"
#include "OSCconstants.h"
#include <Wire.h>
#include <AT24CX.h>
#include <SLIPEncodedUSBSerial.h>
#include <SLIPEncodedSerial.h>
#include <OSCTiming.h>
#include <OSCMessage.h>
#include <OSCMatch.h>
#include <OSCData.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <ESP8266wifi.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>

#include "Team.h"
#include "ScoreKeeper.h"

ScoreKeeper sk;

Team Visitor;

Team Home;
// EEPROM object
AT24CX mem;

/*================================================================================*/

bool testModeNo7SegmentAttached = false; // set to true to test without 7 segments

/*=================================================================================*/

/*===========================================================================

touch osc stuff
============================================================================*/
OSCMessage msgIN;  //all TouchOSC messages are recieved here
int valueIn = 0;   // used in OSCMsgReceive function

/*===========================================================================
				  Port extender - PCF8574
============================================================================*/

enum PCFenum
	{
	PIN0,             // used to indicate if team scored last
	PIN1,          // used to indicate if team scored last
	PIN2,                
	PIN3,
	PIN4,
	pcfVisitorLed,   // leds to indicate The visitor team scored
	pcfHomeLED,      // leds to indicate The home team scored
	PIN7,// used to exit the set distance loop

	pinON = 0,
	pinOFF
	};
#define nodemcu_Pin_for_pcf 10   // used to monitor interrupt from PCF8574 index 12 is gpio10


// Initialize a PCF8574 at I2C-address 0x3A, using SDA, SCL and testWire for the I2C-bus

volatile bool distanceExit = false;



PCF8574 pcf(0x3A, nodemcu_Pin_for_pcf, extPinPressed);

unsigned long timeElapsed;


/*==============================================================================
sonic sensor
//==============================================================================*/

SonicSensorClass ss(D3, D4);     // green to iopin D3/gpio00 and blue to iopin D4/gpio2

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		WIFIF
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
WiFiUDP Udp;
const int serverPort = 8000; //from Iphone TouchOSC (incoming port)
const int destPort = 9000;    //To iphone TouchOSC (outgoing port)

/**************************************
handling delays/timing
***************************************/

unsigned long lWaitMillis = 60000;   // controlled how often  the temperature data is captured - 60000 about one minute

/*=======================================================================
define other constants here
=======================================================================*/

const char* ssid = "ScoreBoard";
const char* password = "cornhole";

const byte tDur = 20;     // team blink delay
const byte tLoop = 3;     // number of blinks


/*===============================================================================
	real time clock setup  for using date and time
===============================================================================*/

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
#define DS3231_ADDRESS 0x68  //  0x57 is the address for the at24C32 memory
DateTime now;   // used for current time
String today = "";  // todays date
String LapseTimeDiff = "";			 // posted to field 3 in tksp
byte hoursIn = 0;
byte minutesIn = 0;
byte secondsIn = 0;
int yearIn = 0;
byte monthIn = 0;
byte dayIn = 0;

int minuteCount = 0;
bool displaytimenow = false; // once set to true time will be displayed and New game will reset to false

/*=================================================================================
global variables
====================================================================================*/

char str[100];
char str1[40];
char REV[] = "2.2.0";  // change as need be - displayed on scoreboard on phone
bool firstRound = true;

// move to pcf uint8_t nodemcu_Pin_for_pcf = D2;      // button to exit measurement loop
//
//  location (plus eeAddress) in eeprom for vaiables
//
byte sZone = 300;				// time zone offset -5 est and -6 dst
byte sFirstEepromSetup = 1;		// 0 = post and 1 = already setup with default eepsetting value
byte sdebug = 2;			// set to  0 for off and 1 for on
byte sdebugEeprom = 3;			// set to  0 for off and 1 for on
byte sdebugLoop = 4;			// set to  0 for off and 1 for on
byte sdebugRTC = 5;			// set to  0 for off and 1 for on
byte syear = 200;
byte smonth = 20;
byte sday = 30;
byte shour = 40;
byte sminutes = 50;
byte sseconds = 60;
byte sdayLightSavesChange = 70;  //  true if in DST timne period
byte sdislayTime = 71;
byte swinby2 = 80;
//byte sminutesForSetup = 86;
byte sboarddistance = 86;

byte sexactscore = 92;



//
// when adding to eepSetting - Make sure you change all areas in EEPROM_functions
//

typedef struct P_settings {
	int Zone = 0;					// time zone offset -5 est and -6 dst
	byte setDate = 0;		// if true will set to compile date
	byte setDate2 = 0;		// if true will set to coded date
	byte FirstEepromSetup = 0;		// false = donot do init again and true = do the initializings
	byte debug = 0;				// set to  0 for off and 1 for on
	byte debugEeprom = 0;			// set to  0 for off and 1 for on
	byte debugLoop = 0;			// set to  0 for off and 1 for on
	byte debugRTC = 0;			// set to  0 for off and 1 for on
	byte debugSetup = 0;			// set to  0 for off and 1 for on

	byte day = 0; // last saved day
	byte month = 0; // last saved month
	int year = 0; // last saved year

	byte hour = 0;  // last saved hour
	byte minutes = 0;  // last saved minutes
	byte seconds = 0;  // last saved seconds
	byte dayLightSavesChange = true; // true if dst
	byte displayTime = false;  // if true the display will change to time of day
	bool winby2 = false;
//	long minutesForSetup = 2; //
	byte boardDistance = 27; //
	byte exactscore = false;

	} settings;
settings eepSettings;

void setup()
	{
	Serial.begin(115200);
	delay(1000);

	if (testModeNo7SegmentAttached) {
		Serial.println("***********************  in test mode -- set testModeNo7SegmentAttached to control  test mode");
		}

	
	WiFi.mode(WIFI_AP);

	//
	//  Start UDP server
	//

	Udp.begin(serverPort);

	delay(500);

//	bme.begin();
	delay(150);
	if (!bme.begin()) {
		if (testModeNo7SegmentAttached) {
			Serial.println("BME Begin Failed ");
			}
		}

	//
	//  set up shiftregistors
	//
	pinMode(MOSI, OUTPUT); // pin on 74HC595 (SER/13)
	pinMode(SCK, OUTPUT);  // pin on 74HC595 (SRCLK/11)
	pinMode(SS, OUTPUT);  // pin on 74HC595 (RCLK/12) aka latchpin
	digitalWrite(SCK, HIGH);
	digitalWrite(SS, HIGH);
	
	//
	// initialize the sonic sensor
	//

	//
	//  port externder
	//
	

	pcf.pinMode(pcfHomeLED, OUTPUT);
	pcf.pinMode(pcfVisitorLed, OUTPUT);
//	pcf.pinMode(PIN3, OUTPUT);
	pinMode(nodemcu_Pin_for_pcf, INPUT_PULLUP);

	pcf.begin();

	timeElapsed = millis();

	//
	// setup for new game
	//

	startNewGame();

	}

void extPinPressed()
	{
	distanceExit = true;
	}

void loop()
	{
	yield();

		/*=================================================================================

		=================================================================================*/

	if (distanceExit==true) {

		Serial.println("---------------------------------------Loop Test of interrupt button - Pressed ");
		distanceExit = false;
		return;
		}

	OSCMsgReceive();
//	delay(50);
	
	}
void OSCMsgReceive()
	{
	OSCMessage msgIN;
	int size = 0;

	if ((size = Udp.parsePacket()) > 0) {
		while (size--)
			msgIN.fill(Udp.read());
		if (!msgIN.hasError()) {
			valueIn = msgIN.getFloat(0);
			oscUpdateLabel(p1_lblstatus2_addr, p1_lblstatus2_txt);   // reset the lbstatusvisitor label in touchosc scoreboard
			//Serial.println();
			static bool waitForMore = false;

			if (msgIN.fullMatch(PatternMach_page3)) {  // page buton pressed for pase 3 (Dist)
				//Serial.println("------------------Pattern matches Page 3");
				return;
				}
			
			if (msgIN.fullMatch(PatternMach_page6)) {  // page buton pressed for pase 6 (RTC)
				//Serial.println("------------------Pattern matches Page 6");
				refreshRTCoscLabels(); // only when the page is button is pressed
				return;
				}
			int bytesReturned = msgIN.match(PatternMach_page3_rtr);

//			Serial.print("                           Any Rotatary Control from   Page 3 bytes: ");
//			Serial.println(bytesReturned);

			if (bytesReturned) {
				//Serial.print("xxxxxxxxxxxxxxxxxxxxxxxxxAny Rotatary Control from   Page 3 bytes: ");
				//Serial.println(bytesReturned);
				}
			bytesReturned = msgIN.match(PatternMach_page6_rtr);
			if (bytesReturned) {
				//Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxAny Rotatary Control from  Page 6 bytes: ");
				//Serial.println(bytesReturned);

				}
			msgIN.route(p1_btnnewgame_addr, Newgame);
			msgIN.route(p1_btn2graybags_addr, TeamRight);
			msgIN.route(p1_btn1redbags_addr, TeamLeft);
			msgIN.route(p1_btncancelpointsentered_addr, CancelPoint);
			msgIN.route(p1_mpbn1_addr, N1);
			msgIN.route(p1_mpbn2_addr, N2);
			msgIN.route(p1_mpbn3_addr, N3);
			msgIN.route(p1_mpbn4_addr, N4);
			msgIN.route(p1_mpbn5_addr, N5);
			msgIN.route(p1_mpbn6_addr, N6);
			msgIN.route(p1_mpbn7_addr, N7);
			msgIN.route(p1_mpbn8_addr, N8);
			msgIN.route(p1_mpbn9_addr, N9);
			msgIN.route(p1_mpbn10_addr, N10);
			msgIN.route(p1_mpbn11_addr, N11);
			msgIN.route(p1_mpbn12_addr, N12);
			msgIN.route(p1_btnminuspoint_addr, setMinus);
			// page 2 temp
			msgIN.route(p2_btndisplay_addr, FutureOption1);   // DispayTemp);

			// page 3

			msgIN.route(p3_rtrdistancedial_addr, displayDistanceDialed);
			msgIN.route(p3_btnsetdistancedial_addr, storeCorrectDistance);
			msgIN.route(p3_btnstartmeasuring_addr, FutureOption2); // setBoardToCorrectDistance); //

			msgIN.route(p5_btndisplaytime_addr, displayTime_Toggle);
			msgIN.route(p5_btndebugrtc_addr, debugRTC_Toggle);
			msgIN.route(p5_btndebugeeprom_addr, debugEEPROM_Toggle);
			msgIN.route(p5_btndebugsetup_addr, debugsetup_Toggle);
			msgIN.route(p5_btndebugloop_addr, debugloop_Toggle);
			msgIN.route(p5_btnforceeeprominit_addr, forceEEPROM_Init_Toggle);
			msgIN.route(p5_btnsave_addr, p5save);
			msgIN.route(p5_btnwinby2_addr, winBy2);
			msgIN.route(p5_btnexactscore_addr, exactscore);

			msgIN.route(p6_monthdial_addr, GetMonth);
			msgIN.route(p6_daydial_addr, GetDay);
			msgIN.route(p6_yeardial_addr, GetYear);
			msgIN.route(p6_hoursdial_addr, GetHour);
			msgIN.route(p6_minutesdial_addr, GetMinutes);

			msgIN.route(p6_btnsetdate_addr, SetDate);
			msgIN.route(p6_btnsettime_addr, SetTime);
			msgIN.route(p6_btnrefreshtime_addr, SetRefreshtime);
			msgIN.route(p6_btnshowondisplay_addr, SetShowOnDisplay);

			if ((sk.getHasATeamBeenSelected()) && (sk.getPointsHaveBeenEntered()))
				{
				checkStatus();
				checkforWinner();
				}
			if (displaytimenow) {
				displayTime();
				}
			}
		}
	}

void checkforWinner()
	{
	byte winner = sk.checkScoreforWinner(Visitor.getTeamScore(), Home.getTeamScore());

	//Serial.print(".............................Check for winner: "); Serial.println(winner);

	if (winner == 0) {
		return;
		}

	switch (winner)
		{
		case 1:  // vistors
			oscUpdateLabel(p1_lbt1status_addr, winr);  // report team 1 won
			oscUpdateLabel(p1_lbt2status_addr, "");  // Clear label  team 2
		//	Serial.println("--------------------------------------------------------> Visiting team won game");
			setHomeLastToScoreLEDoff();
			setVisitorLastToScoreLEDon();

			delay(1000);
			break;

		default:   // home
			oscUpdateLabel(p1_lbt2status_addr, winr);  //  report team 2 won
			oscUpdateLabel(p1_lbt1status_addr, "");  // Clear label team 1
			//Serial.println("--------------------------------------------------------------> Home team won game");
			setHomeLastToScoreLEDon();
			setVisitorLastToScoreLEDoff();

			delay(1000);
			break;
		}
	}
void FutureOption1(OSCMessage &msg, int addrOffset)
	{
	//   delete this function when you get the temp working
	oscUpdateLabel(p2_lbforecast_addr, futureMsg);
	}
void DispayTemp(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("--> display Temp on scoreboard");
	
	ServerUpdate();
	
	}

void SetShowOnDisplay(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("--> display time on scoreboard");
	displaytimenow = true;
	}
void displayTime()
	{
	static int saveminutes = minutesIn;
	bool ok = getTime_Date();
	if (saveminutes != minutesIn) {
		pushDataOutToDisplay(hoursIn, minutesIn);
		}

	}


void Newgame(OSCMessage &msg, int addrOffset)
	{

	displaytimenow = false;
	startNewGame();
	}

void CancelPoint(OSCMessage &msg, int addrOffset)
	{
	doCancelPoints();
	if (testModeNo7SegmentAttached) {
		Serial.println("-- Cancel Points --");
		}


	}

void doCancelPoints() {
	Visitor.setLastToScore(false);
	Home.setLastToScore(false);
	sk.setHasATeamBeenSelected(false);
	sk.setPointsHaveBeenEntered(false);
	sk.setMinus(false);
	sk.setPointsScored(0);
	oscUpdateLabel(p1_lblstatus_addr, pointsCancelled);
	}

void setMinus(OSCMessage &msg, int addrOffset)
	{
	//Serial.println("--> Minus points");
	sk.setMinus(true);
	}
void N1(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(1);
	sk.setPointsHaveBeenEntered(true);
	return;
	}
void N2(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(2);
	sk.setPointsHaveBeenEntered(true);
	}
void N3(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(3);
	sk.setPointsHaveBeenEntered(true);
	}
void N4(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(4);
	sk.setPointsHaveBeenEntered(true);
	}
void N5(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(5);
	sk.setPointsHaveBeenEntered(true);
	}
void N6(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(6);
	sk.setPointsHaveBeenEntered(true);
	}
void N7(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(7);
	sk.setPointsHaveBeenEntered(true);
	}
void N8(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(8);
	sk.setPointsHaveBeenEntered(true);
	}
void N9(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(9);
	sk.setPointsHaveBeenEntered(true);
	}
void N10(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(10);
	sk.setPointsHaveBeenEntered(true);
//	firstNumber = 1;
//	secondNumber = 0;
	}
void N11(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(11);
	sk.setPointsHaveBeenEntered(true);
//	firstNumber = 1;
//	secondNumber = 1;
	}

void N12(OSCMessage &msg, int addrOffset) {
	sk.setPointsScored(12);
	sk.setPointsHaveBeenEntered(true);
	//firstNumber = 1;
	//secondNumber = 2;
	}

void TeamRight(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("--> Team gray bags Side Display");
	Home.setLastToScore(true);
	Visitor.setLastToScore(false);
	sk.setHasATeamBeenSelected(true);
	}
void TeamLeft(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("--> Team red bags Side Display");
	Visitor.setLastToScore(true);
	Home.setLastToScore(false);
	sk.setHasATeamBeenSelected(true);

	}
void winBy2(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("Win  by 2 btn");
	switch (eepSettings.winby2)
		{
		case false:
			oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_ON_txt);
			oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_ON_txt);
			oscUpdateButton(p5_btnwinby2_addr, true);
			eepSettings.winby2 = true;
			sk.setWinBy2(true);
			break;
		default:
			oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_OFF_txt);
			oscUpdateLabel(p5_lbwinby2_addr, p5_lbwinby2_OFF_txt);
			oscUpdateButton(p5_btnwinby2_addr, false);
			eepSettings.winby2 = false;
			sk.setWinBy2(false);
			break;
		}
	}
void exactscore(OSCMessage &msg, int addrOffset)
	{
//	Serial.println("Exact Score btn");
	switch (eepSettings.exactscore)
		{
		case false:
			oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_ON_txt);
			oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_ON_txt);
			oscUpdateButton(p5_btnexactscore_addr, true);
			eepSettings.exactscore = true;
			
			break;
		default:
			oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_OFF_txt);
			oscUpdateLabel(p5_lbexactscore_addr, p5_lbexactscore_OFF_txt);
			oscUpdateButton(p5_btnexactscore_addr, false);
			eepSettings.exactscore = false;
			break;
		}
	}


void setStatusWaiting() {
	oscUpdateLabel(p1_lblstatus_addr, Waiting_on_next_update);
	if (testModeNo7SegmentAttached) {
		Serial.print("---");
		Serial.println(Waiting_on_next_update);
		}


	}  // eof setStatusWaiting

 /****************************************************************************************************************
	   * The LED Display has 8 digits and are display from left to right.
	   * A call to DisplayNumber() will shift the previous number to right one display digit.
	   * The Display Number will convert the 'Number' to proper display segments.
*************************************************************************************************************************/
void DisplayNumber(unsigned int Number)
	{
//	Serial.print("display number: "); Serial.println(Number);
	const byte ledsLatchaPin = SS;   // 9shiftregister data  pin 12
	const byte  ledsClockPin = SCK;   // 8shiftregister data  pin 11
	const byte  ledsDataPin = MOSI;   //7 shiftregister data  pin 14

		//const int DISPLAYNUMBERS[] = { 1,79,18,6,76,36,32,15,0,12 };	//anode
	const uint8_t DISPLAYNUMBERS[] = { 0b10000001,0b11110011,0b01001001,0b01100001,0b00110011,0b00100101,0b00000111,0b11110001,0b00000001,0b00110001,0b11111111 };

	//dec_digits[]

	//int DISPLAYNUMBERS[] = {64,121,36,48,25,18,2,120,0,24};  //anode

	// if (Number != 0) {Serial.print("Number to Display:"); Serial.print(Number); Serial.print("   -> Found in Array:");
	//Serial.println(DISPLAYNUMBERS[Number]);delay(2000);}

	digitalWrite(ledsLatchaPin, LOW);

	shiftOut(ledsDataPin, ledsClockPin, MSBFIRST, DISPLAYNUMBERS[Number]);
	digitalWrite(ledsLatchaPin, HIGH);
	}
/****************************************************************************************************************
* The LED Display has 8 digits and are display from left to right.
* A call to DisplayNumber() will shift the previous number to right one display digit.
*****************************************************************************************************************/
void pushDataOutToDisplay(byte visitor, byte home)  //byte home, byte visitor)
	{
	static byte lh = 1;  // will make the display on start show zero scores when = 1
	static byte lv = 0;

	if (testModeNo7SegmentAttached) {
		if ((lh == home) && (lv == visitor)) {
			Serial.println("********************************  same score do not display*******************");
			}
		else
			{
			Serial.print("\n-----------------------------------------------score: Team Home: ");
			Serial.print(home);
			Serial.print("   Team Vistor: ");
			Serial.println(visitor);
			lh = home;
			lv = visitor;

			}

		return;
		}


	if ((lh == home) && (lv == visitor)) {
		//Serial.println("********************************  same score do not display*******************");
		return;
		}

	lh = home;
	lv = visitor;

	// use all 8 segments
	DisplayNumber(visitor / 10);  // team 2 seq 2 - side 2
	DisplayNumber(visitor % 10);  // team 2 seq 1 - side 2

								// Serial.print("T1 Seg 2- side 2: "); Serial.print(home/10); Serial.print("  team 1 seq 1 - side 2 > "); Serial.println(home%10);
	DisplayNumber(home / 10);   // team 1 seq 2 - side 2
	DisplayNumber(home % 10);   // team 1 seq 1 - side 2

								 // Serial.print("T2 Seg 2- side 1: "); Serial.print(visitor/10); Serial.print("  team 2 seq 1 - side 1 > "); Serial.println(visitor%10);
	DisplayNumber(visitor / 10);  // team 2 seq 2 - side 1
	DisplayNumber(visitor % 10);  // team 2 seq 1 - side 1

								//  Serial.print("T1 Seg 2- side 1: "); Serial.print(home/10); Serial.print("  team 1 seq 1 - side 1 > "); Serial.println(home%10);
	DisplayNumber(home / 10);   // team 1 seq 2 - side 1
	DisplayNumber(home % 10);   // team 1 seq 1 - side 1
								 //  Serial.println("   Finished");
	}

/*
*     timer for blinking Team 2 7-segments
*     all ground wires on the 74HC595 shift registers for Team2 are tied together
*       by writing high to pin 7 we will break ground
*
*/
void blinkTeam(int winningTeam, int d, int l)
	{
	if (testModeNo7SegmentAttached) {
		Serial.print("Blink Team LED: ");
		switch (winningTeam)
			{
			case 1:
				{
				Serial.println("Home");
				break;
				}
			default:
				{
				Serial.println("Visitor");
				}

			}
		return;
		}

	//Serial.println("Blink Team LED");
	/*===============================================================================
	now blink the winning team led
	=================================================================================*/
	switch (winningTeam)
		{
		case 1:
			{
			int b = 0;
			for (b = 0; b < l; ++b)
				{
				//sk.HomeLEDpinWrite(true); //off
				setHomeLastToScoreLEDoff();
				delay(d);
				//sk.HomeLEDpinWrite(false);// on
				setHomeLastToScoreLEDon();
				delay(d);
				}
			//sk.HomeLEDpinWrite(false);  // make sure they are lite
			setHomeLastToScoreLEDoff();
			delay(d);
			break;
			}
		default:
			{
			/*
			*     timer for blinking Team 2 7-segments
			*     all ground wires on the 74HC595 shift registers for Team2 are tied together
			*       by writing high to pin 7 we will break ground
			*/
			int b = 0;
			for (b = 0; b < l; ++b)                                                      //for (b=0; b < 10; ++b)
				{
				//sk.VisitorLEDpinWrite(true);
				setVisitorLastToScoreLEDon();
				delay(d);
				setVisitorLastToScoreLEDoff();
				}
			setVisitorLastToScoreLEDoff(); // make sure they are lite
			break;
			}
		}
	/*================================================================
	  now lite the winning teams led
	  ===============================================================*/
	setHomeLastToScoreLEDoff();
	setVisitorLastToScoreLEDoff();
	if ((winningTeam) == 1) {
		//sk.HomeLEDpinWrite(false); // on
		setHomeLastToScoreLEDon();
		}
	else {
		//sk.VisitorLEDpinWrite(false); // on
		setVisitorLastToScoreLEDon();
		}
	}

void checkStatus()
	{
	//
	//  before pointws can be posted these things have to occurr:
	//                 Team button pressed
	//                 Points button pressed
	//     optional:   minus button pressed
	//

	if ((sk.getHasATeamBeenSelected()) && (sk.getPointsHaveBeenEntered()))
		{
		if (testModeNo7SegmentAttached) {
			Serial.println("CheckStatus() - points entered and team selected");
			}
		byte t = 0;
		/*
		*     We can display the entered score
		*/

		/*======================================================================
		select the correct team for adding points
		======================================================================*/
		if (Home.getLastToScore())
			{
				bool err = Home.AddToTeamScore(sk.getPointsScored(), sk.getMinus());
				if (err) {
					char n[5] = "";
					sprintf(n, "%d", sk.getPointsScored());
					doCancelPoints();

					char s[20] = "";

					strcpy(s, CANNOTSUBTRACTPOINTS);
					strcat(s, n);
					strcat(s, Points);
					oscUpdateLabel(p1_lblstatus_addr, s);

					return;
					}

				oscUpdateLabel(p1_lblt2score_addr, Home.getTeamScore());
				oscUpdateButton(p1_LedHomeScored_addr, 1);  // turn led on
				oscUpdateButton(p1_LedVisitorsScored_addr, 0);	// turn led off
				blinkTeam(1, tLoop, tDur);

				////Home.setLastToScore(true);
				////Visitor.setLastToScore(false);

			//	Serial.println("Home Team scored");
				setHomeLastToScoreLEDon();
				setVisitorLastToScoreLEDoff();

				if (testModeNo7SegmentAttached) {
					Serial.print("Add points to Team Home: ");
					Serial.println(sk.getPointsScored());
					}

			}
		else
			{
			bool err = Visitor.AddToTeamScore(sk.getPointsScored(), sk.getMinus());
			if (err) {
				char n[5] = "";
				sprintf(n, "%d", sk.getPointsScored());
				doCancelPoints();

				char s[20] = "";

				strcpy(s, CANNOTSUBTRACTPOINTS);
				strcat(s, n);
				strcat(s, Points);
				oscUpdateLabel(p1_lblstatus_addr, s);

				return;
				}
			oscUpdateLabel(p1_lblt1score_addr, Visitor.getTeamScore());
			oscUpdateButton(p1_LedHomeScored_addr, 0);  // turn led off
			oscUpdateButton(p1_LedVisitorsScored_addr, 1);	// turn led on phone

			setHomeLastToScoreLEDoff();
			setVisitorLastToScoreLEDon();

			blinkTeam(2, tLoop, tDur);

			////Visitor.setLastToScore(true);
			////Home.setLastToScore(false);

		//	Serial.println("Visiting Team Scored");
			setHomeLastToScoreLEDoff();
			setVisitorLastToScoreLEDon();

			if (testModeNo7SegmentAttached) {
				Serial.print("Add points to Team Visitor: ");
				Serial.println(sk.getPointsScored());
				}
			}

		Visitor.setLastToScore(false);
		Home.setLastToScore(false);

		sk.setPointsScored(0);
		sk.setHasATeamBeenSelected(false);
		sk.setMinus(false);
		sk.setPointsHaveBeenEntered(false);

		}   // eod of process input data to display new score
	pushDataOutToDisplay(Home.getTeamScore(), Visitor.getTeamScore());   // display new scores
	setStatusWaiting();
	}
void startNewGame()
	{

//
//   set defualt values from eeprom or setup values
//

	setDefaults();

	distanceExit = false;
	Visitor.setLastToScore(false);
	Visitor.resetTeamScoreToZero();

	Home.setLastToScore(false);
	Home.resetTeamScoreToZero();

	sk.setMinus(false);
	sk.setPointsHaveBeenEntered(false);
	sk.setPointsScored(0);

	pushDataOutToDisplay(Home.getTeamScore(), Visitor.getTeamScore());   // display new scores

	blinkTeam(1, tLoop, tDur);
	blinkTeam(2, tLoop, tDur);

	setStatusWaiting();

	oscUpdateLabel(p1_lbrev_addr, REV);
	delay(20);
	oscUpdateLabel(p1_lblt2score_addr, 0);
	oscUpdateLabel(p1_lblt1score_addr, 0);

	oscUpdateLabel(p1_lbt1status_addr, p1_lbt1status_txt);  // good
	oscUpdateLabel(p1_lbt2status_addr, p1_lbt2status_txt);  // luck

	oscUpdateButton(p1_LedHomeScored_addr, 0);  // turn led off
	oscUpdateButton(p1_LedVisitorsScored_addr, 0);	// turn led off

	setHomeLastToScoreLEDoff();
	setVisitorLastToScoreLEDoff();

	if (testModeNo7SegmentAttached) {
		Serial.println("-------------------------  New Game ________________________");
		}

	}

void setHomeLastToScoreLEDoff()
	{
//	Serial.println("\nhome led off");
	pcf.digitalWrite(pcfHomeLED, pinOFF);    // off

	}
void setHomeLastToScoreLEDon()
	{
//	Serial.println("\nhome led on");
	pcf.digitalWrite(pcfHomeLED, pinON);    // on
	}
void setVisitorLastToScoreLEDoff()
	{
//	Serial.println("\nvisitor led off");
	pcf.digitalWrite(pcfVisitorLed, pinOFF);    // off
	}
void setVisitorLastToScoreLEDon()
	{
//		Serial.println("\nvisitor led on");

	pcf.digitalWrite(pcfVisitorLed, pinON);    // on
	}
void displayDistanceDialed(OSCMessage &msg, int addrOffset)
	{
//	oscUpdateLabel(p3_lbdistancedial_addr, valueIn);
	if (valueIn == eepSettings.boardDistance) // display the number after dial settles down
		{
		oscUpdateLabel(p3_lbdistancedial_addr, valueIn);
		}

	eepSettings.boardDistance = valueIn;

	}

void storeCorrectDistance(OSCMessage &msg, int addrOffset)
	{
	Serial.print("Set the dialed distance into memory-here: "); Serial.println(eepSettings.boardDistance);
	distanceExit = false;
//	eepSettings.boardDistance = valueIn;							// store for later use

//	eepSettings.boardDistance = 26;							// store for later use
	oscUpdateLabel(p3_lbdistancedial_addr, eepSettings.boardDistance);
	storeValuesToEeprom();
	}

void FutureOption2(OSCMessage &msg, int addrOffset)
	{
	//   delete this function when you get the temp working
	oscUpdateLabel("/3/label32", futureMsg);
	}

void setBoardToCorrectDistance(OSCMessage &msg, int addrOffset)
	{
	// remove the above code after getting function working

	startToMeasure();
	}
void startToMeasure()
	{
	float d = 0;
	int ft = 0;
	int  in = 0;
	long totalinchesofsetdistance = long(eepSettings.boardDistance * 12);
	distanceExit = false;

	Serial.print("Game Distance Feet: "); Serial.println(eepSettings.boardDistance);
	Serial.print(" or inches: "); Serial.println(totalinchesofsetdistance);

	while (distanceExit == false)
		{
		OSCMessage msgIN;
		int size = 0;

		if ((size = Udp.parsePacket()) > 0) {
			while (size--)
				msgIN.fill(Udp.read());
			if (!msgIN.hasError()) {
				valueIn = msgIN.getFloat(0);
				oscUpdateLabel(p1_lblstatus2_addr, p1_lblstatus2_txt);   // reset the lbstatusvisitor label in touchosc scoreboard
				//Serial.println();
				static bool waitForMore = false;

				if (msgIN.fullMatch(PatternMach_page3)) {  // page buton pressed for pase 3 (Dist)

					if (distanceExit) {

						Serial.println("---------------------------------------exit button pressed ");
						distanceExit = false;
						return;
						}
					d = ss.Read();


					yield();

				/*	if (d == 0) {
						Serial.println("exit d = 0: ");
						return;
						}
			*/
				//	Serial.print("\n d = "); Serial.print(d);
					ft = d / 12;
					in = (d - (ft * 12));
					//in = in / 10;

					pushDataOutToDisplay(in, ft);
					oscUpdateLabel(p3_lbdistancefeet_addr, ft);

					oscUpdateLabel(p3_lbdistanceinches_addr, in);

					if (d >= totalinchesofsetdistance)
						{
						Serial.print("-----------------DONE ft: "); Serial.print(ft); Serial.print("  In.: "); Serial.println(in);
						return;
						}


			//		Serial.print("Sonic ft: "); Serial.print(ft); Serial.print("  In.: "); Serial.println(in);
					delay(500);
					}
				Serial.println("---------------------------------------exit button pressed ");
				distanceExit = false;
				}
			}
		}
	}
