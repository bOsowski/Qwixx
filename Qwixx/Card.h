#ifndef CARD_H
#define CARD_H

#include <vector>
#include "Row.h"
#include <iomanip>

using namespace std;

class Card
{
private:
	vector<Row*> rows;
	friend ostream& operator<<(ostream& os, const Card& card);


public:
	Card();
	~Card();
	void printCard();
	vector<Row*>& getRows();
};

#endif;

