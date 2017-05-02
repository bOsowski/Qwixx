#include "stdafx.h"
#include "Field.h"


Field::Field(const short& const fieldNumber){
	//cout << "Field " << fieldNumber << " created.\n";
	m_fieldNumber = fieldNumber;
	possibleToCrossOut = true;
	crossedOut = false;
}


Field::~Field()
{
	cout << "Destructor for a field " << m_fieldNumber << " is called.\n";
}

short& Field::getFieldNumber()
{
	return m_fieldNumber;
}

bool Field::isCrossedOut()
{
	return crossedOut;
}

bool Field::isPossibleToCrossOut()
{
	return possibleToCrossOut;
}

void Field::makeNotPossibleToCrossOut()
{
	possibleToCrossOut = false;
}

void Field::crossOut()
{
	crossedOut = true;
}

ostream & operator<<(ostream & os, const Field & field)
{
	os << "Field number: " << field.m_fieldNumber << ", possible to cross out: " <<boolalpha<< field.possibleToCrossOut<< ", crossedOut: " << field.crossedOut;	//enabling boolalpha makes 1s display as true, 0s as false.
	return os;
}
