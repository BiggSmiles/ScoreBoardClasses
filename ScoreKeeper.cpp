//  ScoreKeeper.cpp
//
//
#include "ScoreKeeper.h"

#include "Team.h""

/*=================================================================================
constructor
=================================================================================*/
ScoreKeeper::ScoreKeeper() {
	//"I am the ScoreKeeper constructor!");
	}

/*=================================================================================
deconstructor
=================================================================================*/
ScoreKeeper::~ScoreKeeper() {
	//"ScoreKeeper deconstructor!");
	}

/*=================================================================================
gets the pin number for Buzzer
=================================================================================*/
bool ScoreKeeper::getBuzzerpin()
	{
	return _pBuzzerpin;
	}
	/*=================================================================================
	used to set the pin number for the Buzzer
	=================================================================================*/
void ScoreKeeper::setBuzzerpin(int p)
	{
	_pBuzzerpin = p;
	}
/*=================================================================================
Turn pin on or off for the Buzzer
=================================================================================*/
void ScoreKeeper::BuzzerpinWrite(bool p)
	{
	digitalWrite(_pBuzzerpin, p);
	}
/*=================================================================================
used to verify if points need to be subtracted
=================================================================================*/
int ScoreKeeper::getMinus() {
	return _pMinussk;
	}

/*=================================================================================
set true if a team has scored points
=================================================================================*/
void ScoreKeeper::setHasATeamBeenSelected(bool set) {
	_pTeamHasScored = set;
	}
/*=================================================================================
get bool for has a team scored
=================================================================================*/
bool ScoreKeeper::getHasATeamBeenSelected() {
	return _pTeamHasScored;
	}
/*=================================================================================
set number of points to be scored
=================================================================================*/
void ScoreKeeper::setPointsScored(int set) {
	_pPointssk = set;
	}
/*=================================================================================
get number of points to be scored
=================================================================================*/
int ScoreKeeper::getPointsScored() {
	return _pPointssk;
	}
/*=================================================================================
set true if points been entered
=================================================================================*/
void ScoreKeeper::setPointsHaveBeenEntered(bool set) {
	_pPointsHaveBeenEntered = set;
	}
/*=================================================================================
get bool for has points been entered
=================================================================================*/
bool ScoreKeeper::getPointsHaveBeenEntered() {
	return _pPointsHaveBeenEntered;
	}

/*=================================================================================
set true to subtract points
=================================================================================*/
void ScoreKeeper::setMinus(bool set) {
	_pMinussk = set;
	}
/*=================================================================================
gets the if we need to check for win By 2 points
=================================================================================*/
bool ScoreKeeper::getWinBy2()
	{
	return _pWinBy2sk;
	}
/*=================================================================================
used to set we need to check for win By 2 points
=================================================================================*/
void ScoreKeeper::setWinBy2(bool p)
	{
	_pWinBy2sk = p;
	}
/*=================================================================================
gets the if we need to check for win By exact points
=================================================================================*/
bool ScoreKeeper::getWinByExactScore()
	{
	return _pWinExactScoresk;
	}
/*=================================================================================
used to set we need to check for win By exact points
=================================================================================*/
void ScoreKeeper::setWinByExactScore(bool p)
	{
	_pWinExactScoresk = p;
	}


/*=================================================================================
used to set the pin number for the home led
=================================================================================*/
void ScoreKeeper::setScoredLEDpin(int p)
	{
	_pScoredLEDPin = p;
	pinMode(_pScoredLEDPin, OUTPUT);
	}
/*= ================================================================================
returns the pin number for the home led
================================================================================ = */
int ScoreKeeper::getScoredLEDpin()
	{
	return _pScoredLEDPin;
	}
/*=================================================================================
Turn pin on or off for the Home led pin
=================================================================================*/
void ScoreKeeper::ScoredLEDpinWrite(byte p)
	{
	digitalWrite(_pScoredLEDPin, p);
	}



/*=================================================================================
used to turn ON the led for team that  scored. To indicate they Scored
=================================================================================*/
void ScoreKeeper::setScoredLedON()
	{
	ScoredLEDpinWrite(LOW);
	}

/*=================================================================================
used to turn OFF the led for Home Team. To indicate they Scored
=================================================================================*/
void ScoreKeeper::setScoredLedOFF()
	{
	ScoredLEDpinWrite(HIGH);

	}


/*******************************************************************************************end Home LED */

/*=================================================================================
CHECK IF WE HAVE A WINNER
=================================================================================*/
byte ScoreKeeper::checkScoreforWinner(int t1, int t2)
	{
	int w2 = 0;

	if (_pWinBy2sk) {
		w2 = 2;
		}

	if (t1 >= _pScoreLimitsk + w2)
		{
		return 1;
		}
	if (t2 >= _pScoreLimitsk + w2)
		{
		return 2;
		}
	return 0;
	}
/***********************************************************************************
*  score the points
***********************************************************************************/
/*
int ScoreKeeper::score(int t)
	{
	if (_pMinussk)
		{
		if (_pPointssk > _pTotalScoresk)
			{
			Serial.print("add code to display error message: Cannot subtract points.");
			return 200;
			}

		_pTotalScoresk = _pTotalScoresk - _pPointssk;
		}
	else
		{
		_pTotalScoresk = _pTotalScoresk + _pPointssk;
		}

	return _pTotalScoresk;
	}

	*/