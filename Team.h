// TeamClass.h

#ifndef _Team_h
#define _Team_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Team
	{
		protected:
		int _pTeamScore = 0;
		bool _pLastToScore = false;
		String _pTeamName = "";

		public:
		   // constructors
		Team();

		// methods
		void resetTeamScoreToZero();

		int getTeamScore();

		bool AddToTeamScore(int p, bool minus);

		void setTeamName(String n);
		String getTeamName();

		void setLastToScore(bool l);
		bool getLastToScore();
		// deconstructor
		~Team();
	};
#endif
