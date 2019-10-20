// ScoreKeeper.h
//
//  ScoreKeeper controls the game; just like in the real world.
//
//	.Update the score
//     . before the update can happen, A team has to selected and points have to be select. If points need to be subtracted
//       from score? The minus button needs to be pressed after the team is selected, but before the points are selected.
//
//  .Cancel entries
//    Use this button to cancel activity before the points are scored
//
//  .New Game
//    Use this to start a new scoring session.
//
//  . Declare winner
//    if first team to reach 21 points will be declared the winner. Unless the "Win by 2" option is selected. The the winning
//      score must be Greated than 20 and 2 points grateter than the other teams points
//
#include <Arduino.h>

#include "Team.h"

#ifndef _ScoreKeeper_h
#define _ScoreKeeper_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ScoreKeeper
	{
		protected:
		int _pTotalScoresk = 0;
		int _pPointssk = 0;
		bool _pMinussk = false;
		const int _pScoreLimitsk = 21;
		bool _pWinBy2sk = false;
		bool _pWinExactScoresk = false;
		bool _pTeamHasScored = false;

		bool _pPointsHaveBeenEntered = false;
		bool _pScoredLEDPin = 4;
	//	int _pHomeLEDpin = 4;
	//	int _pVisitorLEDpin = 4;
		int _pBuzzerpin = 4;
		public:

		/*=================================================================================
		CONSTRUCTORS
		=================================================================================*/
		ScoreKeeper();

		/*=================================================================================
		METHODS
		=================================================================================*/
		

		int getMinus(); // used to see if user wants to subtract points
		void setMinus(bool set); // Sets the boolean to true to subtract points

		void setPointsScored(int set);  //  set number of points to be scored 
		int getPointsScored();          //  get the points enter for this scoring

		void setPointsHaveBeenEntered(bool set);
		bool getPointsHaveBeenEntered();

		byte checkScoreforWinner(int t1, int t2);
		void setWinBy2(bool set);
		bool getWinBy2();

		void setWinByExactScore(bool set);
		bool getWinByExactScore();

		bool getHasATeamBeenSelected();
		void setHasATeamBeenSelected(bool y);

		void setScoredLEDpin(int p);
		int getScoredLEDpin();
		void setScoredLedON();
		void setScoredLedOFF();
		void ScoredLEDpinWrite(byte p);

		void setBuzzerpin(int p);
		bool getBuzzerpin();

		void BuzzerpinWrite(bool p);
/*====  notes ================================================================================================================
Before points casn be updated to a team score.  Things have to happen: A team button has to e pressed, and Points have to be pressed. Does not matter the sequence.

To subtract points from a team score. Then have to be done in order: Press team button, then the minus button, then the points


=============================================================================================================================*/
		/*=================================================================================
		DECONSTRUCTOR
		=================================================================================*/
		~ScoreKeeper();
	};
#endif