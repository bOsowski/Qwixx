#include "stdafx.h"
#include "Die.h"


bool Die::isActive()
{
	return m_isActive;
}

void Die::setInactive()
{
	m_isActive = false;
}

int Die::getOutput()
{
	return output;
}

void Die::throwDie() {
	int throwResult = (rand() % numberOfFaces + 1);
	cout << "A " << m_colour << " die was thrown. It landed on "<< throwResult<<endl;

	output = throwResult;
}

Colour Die::getColour()
{
	return m_colour;
}

//Overriding the default constructor.
Die::Die(const Colour& const colour)
{
	m_colour = colour;
}