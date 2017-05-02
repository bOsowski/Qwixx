#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Card.h"
#include "Die.h"
#include <vector>

using namespace std;

class Player
{

	Card card;
	int totalScore = -1;
	string m_name;
	short m_misthrows = 0;
	friend ostream& operator<<(ostream& os, const Player& player);
	bool crossOutNumber(const int & numberToCrossOut, const unsigned short & row, const vector<Die*>& const dice, vector<Player*>& players);

public:
	bool operator > (const Player& other) const;	//overriding the > operator to allow for sorting with the algorithm library
	Player(const string& name);
	~Player();
	void moveAsActivePlayer(const vector<Die*>& const dice, vector<Player*>& players);
	bool attemptCommonMove(const vector<Die*>& const dice, vector<Player*>& players);
	bool attemptSecondaryMove(const vector<Die*>& const dice, vector<Player*>& players);
	Card& getCard();
	short& getMisthrows();
	string& getName();
	int& getTotalScore();
	void setTotalScore(const int& const scoreToSet);
};


#endif