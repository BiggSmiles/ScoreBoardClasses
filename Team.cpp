//
//
//

#include "Team.h"
//#include "OSCMessage.h"
Team::Team() {
	Serial.println("I am the Team constructor!");
	}

Team::~Team() {
	Serial.println("I am the Team deconstructor!");
	}
void Team::setTeamName(String n)
	{
	_pTeamName = n;
	}
String Team::getTeamName()
	{
	return _pTeamName;
	}
void Team::setLastToScore(bool l)
	{
	_pLastToScore = l;
	}
bool Team::getLastToScore()
	{
	return _pLastToScore;
	}
//
//  either add or subtract points entered to a team score
//  parameters: Points, subtract points if true
//
bool  Team::AddToTeamScore(int p, bool minus)
	{
	/*=============================================
	  check for negative score
	=============================================*/
	if (minus)
		{
		p = -p;
		}

	////Serial.print("Score to add: "); Serial.println(p);
//	Serial.print("Score total: "); Serial.println(_pTeamScore + p);
	if ((_pTeamScore + p) < 0)
		{
		Serial.println("Score would be negative - cannot subtract points");
		return 1;
		}
	else
		{
		_pTeamScore = _pTeamScore + p;
		return 0;
		}
	}

int Team::getTeamScore()
	{
	return _pTeamScore;
	}
void Team::resetTeamScoreToZero()
	{
	_pTeamScore = 0;
	}