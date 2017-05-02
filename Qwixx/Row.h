#ifndef ROW_H
#define ROW_H

#include "Colour.h"
#include "Field.h"
#include <vector>
#include <iostream>

using namespace std;

class Row
{
private:
	Colour m_colour;
	unsigned short crossedOutFields = 0;
	vector<Field*> fields;
	friend ostream& operator<<(ostream& os, const Row& row);
	bool m_isRowLocked = false;
	bool isToBeLockedDuringNextTurn = false;

public:
	bool getIsToBeLockedDuringNextTurn();
	void setToBeLockedDuringNextTurn(bool status);
	void incrementCrossedOutFields();
	bool isRowLocked();
	void lockRow();
	bool isRowLockable();
	Row(const Colour& colour);	//this will occupy the fields also, based on the colour.
	~Row();
	vector<Field*> getFields();
	Colour getColour();
};

#endif

