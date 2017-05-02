#include "stdafx.h"
#include "Card.h"


Card::Card()
{
	rows.push_back(new Row(RED));
	rows.push_back(new Row (YELLOW));
	rows.push_back(new Row (GREEN));
	rows.push_back(new Row(BLUE));
}


Card::~Card()
{
	cout << "Destructor for a card is called\n";
	for (int i = 0; i < rows.size(); i++) {
		delete rows.at(i);
	}
}

void Card::printCard()
{
	for (unsigned short i = 0; i < rows.size(); i++) {
		cout << i+1<< ") "<<  setw(6)<<rows.at(i)->getColour() << " field: ";	//the setw(value) gives the text 'value' characters space so they're printed out even, using #include <iomanip>.
		for (unsigned short j = 0; j < rows.at(i)->getFields().size(); j++) {
			if (rows.at(i)->getFields().at(j)->isPossibleToCrossOut()) {
				cout << setw(4)<< rows.at(i)->getFields().at(j)->getFieldNumber() << " ";
			}
			else if (rows.at(i)->getFields().at(j)->isCrossedOut()) {
				cout << setw(4) << "X" << " ";
			}
			else {
				cout << setw(4) << "-" << " ";
			}

		}
		cout << "	locked? -" << rows.at(i)->isRowLocked();
		cout << endl;
	}
}

vector<Row*>& Card::getRows()
{
	return rows;
}

ostream & operator<<(ostream & os, const Card & card)
{
	os << "Card..\n";
	for (unsigned short i = 0; i < card.rows.size();i++) {
		os << *card.rows.at(i) << endl;
	}
	return os;
}
