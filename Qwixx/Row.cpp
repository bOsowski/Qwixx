#include "stdafx.h"
#include "Row.h"

bool Row::getIsToBeLockedDuringNextTurn()
{
	return isToBeLockedDuringNextTurn;
}

void Row::setToBeLockedDuringNextTurn(bool status)
{
	isToBeLockedDuringNextTurn = status;
}

void Row::incrementCrossedOutFields()
{
	crossedOutFields++;
}

bool Row::isRowLocked()
{
	return m_isRowLocked;
}

void Row::lockRow()
{
	m_isRowLocked = true;
}

bool Row::isRowLockable()
{
	if (crossedOutFields > 4) {
		return true;
	}
	return false;
}

Row::Row(const Colour & colour)
{
	m_colour = colour;
	cout << "Creating " << colour << " fields\n";
	//pushing the appropriate fields onto the row. Red and Yellow rows have a common field layout.
	if (colour == RED || colour == YELLOW) {
		for (unsigned short i = 2; i <= 12; i++) {
			fields.push_back(new Field(i));
		}
	}
	//Green and Blue rows have common field layout.
	else if (colour == GREEN || colour == BLUE) {
		for (unsigned short i = 12; i >= 2; i--) {
			fields.push_back(new Field(i));
		}
	}

}

Row::~Row()
{
	cout << "Destructor for a " << m_colour << " row is called.\n";
	for (unsigned short i = 0; i < fields.size(); i++) {
		delete fields.at(i);
	}
}

vector<Field*> Row::getFields()
{
	return fields;
}

Colour Row::getColour()
{
	return m_colour;
}


ostream & operator<<(ostream & os, const Row & row)
{
	os << row.m_colour << " row.\n";
	//also include all fields to the outstream..
	for (unsigned short i = 0; i < row.fields.size(); i++) {
		os << "Field: " << *row.fields.at(i) << endl;
	}

	return os;
}
