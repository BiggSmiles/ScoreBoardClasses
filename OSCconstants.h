// OSCconstants.h

#ifndef _OSCCONSTANTS_h
#define _OSCCONSTANTS_h
/*
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
*/

const char Gray_bags[] = " Gray bags";
char Red_bags[] = " Red bags";
char Now_press_points[] = "- Now press points ";
char Points[] = " Points ";
char Now_press_team[] = " - Now press team";
char Waiting_on_next_update[] = " Waiting on next update";
char pointsCancelled[] = " Entries Cancelled";
char CANNOTSUBTRACTPOINTS[] = "Cannot subtract ";
char futureMsg[] = "future Option";
char winner[] = "Winner";
char good[] = "Good";
char luck[] = "Luck";
char newg[] = "New";
char game[] = "Game";
char stat[] = "Status";
char winr[] = "Winner";

/*							*/
/*  OSC Message formats		*/
/*							*/

char PatternMach_page1[] = "/1"; // page DIst
char PatternMach_page3[] = "/3"; // page DIst
char PatternMach_page3_rtr[] = "/3/rtr*"; // page DIst
char PatternMach_page6[] = "/6"; // page RTC
char PatternMach_page6_rtr[] = "/6/rtr*"; // page RTC rotatary controls

// page 1

char p1_btn1redbags_addr[] = "/1/btnt1redbags";

char p1_lbt1status_txt[] = "Good";
char p1_lbt1status_addr[] = "/1/lbt1status";

char p1_lbl1score_txt[] = "0";
char p1_lblt1score_addr[] = "/1/lblt1score";

char p1_home_txt[] = "0";
char p1_LedVisitorsScored_addr[] = "/1/ledt1";

char p1_lblstatus_txt[] = "Status";
char p1_lblstatus_displayTime_txt[] = "Time Displaying";
char p1_lblstatus_addr[] = "/1/lblstatus";

char p1_lblstatus2_txt[] = "Use minus sign to subtract points";
char p1_lblstatus2_txt_err[] = "Error: points entered greater than score.";
char p1_lblstatus2_addr[] = "/1/lblstatus2";

char p1_btn2graybags_addr[] = "/1/btnt2graybags";

char p1_lbt2status_txt[] = "Luck";
char p1_lbt2status_addr[] = "/1/lbt2status";

//char p1_lbl2score_txt[] = "0";
char p1_lblt2score_addr[] = "/1/lblt2score";

//char p1_2_txt[] = "0";
char p1_LedHomeScored_addr[] = "/1/ledt2";

char p1_lbrev_text[] = "Rev 2.1";
char p1_lbrev_addr[] = "/1/lbrev";

/*
Multi push button
*/

char p1_mpbn1_addr[] = "/1/mpbn/1/1";
char p1_mpbn2_addr[] = "/1/mpbn/2/1";
char p1_mpbn3_addr[] = "/1/mpbn/3/1";
char p1_mpbn4_addr[] = "/1/mpbn/4/1";

char p1_mpbn5_addr[] = "/1/mpbn/1/2";
char p1_mpbn6_addr[] = "/1/mpbn/2/2";
char p1_mpbn7_addr[] = "/1/mpbn/3/2";
char p1_mpbn8_addr[] = "/1/mpbn/4/2";
char p1_mpbn9_addr[] = "/1/mpbn/1/3";
char p1_mpbn10_addr[] = "/1/mpbn/2/3";
char p1_mpbn11_addr[] = "/1/mpbn/3/3";
char p1_mpbn12_addr[] = "/1/mpbn/4/3";

char p1_mpbutton_txt[] = "mpbutton";
char p1_mpbutton_addr[] = "/1/mpbn";

char p1_btnnewgame_addr[] = "/1/btnnewgame";
char p1_btncancelpointsentered_addr[] = "/1/btncancelpointsentered";

char p1_btnminuspoint_addr[] = "/1/btnminuspoint";
char p1_refreshdisplay_addr[] = "/1/btnrefreshdisplay";

// Page 2
char p2_lbtemp_txt[] = "01";
char p2_lbtemp_addr[] = "/2/lbtemp";

char p2_lbhumidity_txt[] = "02";
char p2_lbhumidity_addr[] = "/2/lbhumidity";

char p2_lbheatindex_txt[] = "03";
char p2_lbheatindex_addr[] = "/2/lbheatindex";

char p2_lbalititude_txt[] = "04";
char p2_lbalititude_addr[] = "/2/lbalititude";

char p2_lbpressure_txt[] = "05";
char p2_lbpressure_addr[] = "/2/lbpressure";

char p2_lbdewpoint_txt[] = "06";
char p2_lbdewpoint_addr[] = "/2/lbdewpoint";

char p2_lbforecast_txt[] = "07";

char p2_lbforecast_addr[] = "/2/lbforecast";
char p2_btndisplay_addr[] = "/2/btndisplaytemp";

// Page 3

char p3_rtrdistancedial_addr[] = "/3/rtrdistancedial";
char p3_btnsetdistancedial_addr[] = "/3/btnsetdistancedial";
char p3_btnstartmeasuring_addr[] = "/3/btnstartmeasuring";

char p3_lbdistancedial_addr[] = "/3/lbdistancedial";
char p3_lbdistancefeet_addr[] = "/3/lbdistancefeet";
char p3_lbdistanceinches_addr[] = "/3/lbdistanceinches";



// Page 5
char p5_lbwinby2_addr[] = "/5/lbwinby2";
char p5_lbwinby2_ON_txt[] = "ON";
char p5_lbwinby2_OFF_txt[] = "OFF";
char p5_btnwinby2_addr[] = "/5/btnwinby2";

char p5_lbexactscore_addr[] = "/5/lbexactscore";
char p5_lbexactscore_ON_txt[] = "ON";
char p5_lbexactscore_OFF_txt[] = "OFF";
char p5_btnexactscore_addr[] = "/5/btnexactscore";

char p5_lbstatus_txt[] = "status";
char p5_lbstatus_DT_ON_txt[] = "Display Time - ON";
char p5_lbstatus_DT_OFF_txt[] = "Display Time - OFF";
char p5_lbstatu_debug_RTCs_ON_txt[] = "debug RTC -ON ";
char p5_lbstatu_debug_RTCs_OFF_txt[] = "debug RTC - OFF";
char p5_lbstatus_debug_Setup_ON_txt[] = "debug Setup - ON";
char p5_lbstatus_debug_Setup_OFF_txt[] = "debug Setup - OFF";
char p5_lbstatus_debug_loop_ON_txt[] = "debug LOOP - ON";
char p5_lbstatus_debug_loop_OFF_txt[] = "debug LOOP - OFF";
char p5_lbstatus_set_EEPROM_txt[] = "Set EEPROM _ DONE";

char p5_lbstatus_force_EEPROM_txt[] = "FORCE EEPROM Initialization _ DONE";
char p5_lbstatus_save_EEPROM_txt[] = "save EEPROM - SAVED";

char p5_lbstatus_addr[] = "/5/lbstatus";

char p5_lbdisplaytime_ON_txt[] = "ON";
char p5_lbdisplaytime_OFF_txt[] = "OFF";
char p5_lbdisplaytime_addr[] = "/5/lbdisplaytime";
char p5_btndisplaytime_addr[] = "/5/btndisplaytime";

char p5_lbbdebugrtc_ON_txt[] = "ON";
char p5_lbbdebugrtc_OFF_txt[] = "OFF";
char p5_lbdebugrtc_addr[] = "/5/lbdebugrtc";
char p5_btndebugrtc_addr[] = "/5/btndebugrtc";

char p5_lbdebugsetup_ON_txt[] = "ON";
char p5_lbdebugsetup_OFF_txt[] = "OFF";
char p5_lbdebugsetup_addr[] = "/5/lbdebugsetup";
char p5_btndebugsetup_addr[] = "/5/btndebugsetup";

char p5_lbdebugloop_ON_txt[] = "ON";
char p5_lbdebugloop_OFF_txt[] = "OFF";
char p5_lbdebugloop_addr[] = "/5/lbdebugloop";
char p5_btndebugloop_addr[] = "/5/btndebugloop";

char p5_lbdebugeeprom_ON_txt[] = "ON";
char p5_lbdebugeeprom_OFF_txt[] = "OFF";
char p5_lbdebugeeprom_addr[] = "/5/lbdebugeeprom";
char p5_btndebugeeprom_addr[] = "/5/btndebugeeprom";

char p5_lbforceeeprominit_ON_txt[] = "ON";
char p5_lbforceeeprominit_OFF_txt[] = "OFF";
char p5_lbforceeeprominit_addr[] = "/5/lbforceeeprominit";
char p5_btnforceeeprominit_addr[] = "/5/btnforceeeprominit";

char p5_lbsave_Yes_txt[] = "Yes";
char p5_lbsave_Saving_txt[] = "Saving";
char p5_lbsave_Saved_txt[] = "Saved";
char p5_lbsave_addr[] = "/5/lbsave";
char p5_btnsave_addr[] = "/5/btnsave";

// page 6

char p6_lbmonth_addr[] = "/6/lbmonth";
char p6_lbday_addr[] = "/6/lbday";
char p6_lbyear_addr[] = "/6/lbyear";
char p6_lbhours_addr[] = "/6/lbhours";
char p6_lbminutes_addr[] = "/6/lbminutes";
// rotary controls
char p6_monthdial_addr[] = "/6/rtrmonthdial";
char p6_daydial_addr[] = "/6/rtrdaydial";
char p6_yeardial_addr[] = "/6/rtryeardial";
char p6_hoursdial_addr[] = "/6/rtrhoursdial";
char p6_minutesdial_addr[] = "/6/rtrminutesdial";
//buttons
char p6_btnsetdate_addr[] = "/6/setdate";
char p6_btnsettime_addr[] = "/6/settime";
char p6_btnrefreshtime_addr[] = "/6/refreshtime";
char p6_btnshowondisplay_addr[] = "/6/showondisplay";

char p6_lbseconds_addr[] = "/6/lbseconds";
char p6_lbdate_addr[] = "/6/lbestdst";
#endif
