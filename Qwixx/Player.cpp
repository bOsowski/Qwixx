#include "stdafx.h"
#include "Player.h"

void Player::moveAsActivePlayer(const vector<Die*>& const dice, vector<Player*>& players)
{

	cout << string(50, '\n');
	cout << m_name << ", you are now the active player.\nYou have "<<4-m_misthrows<<" misthrows left.\n";
		//throw all the dice
		cout << "Throwing all active dice..\n\n";
		for (unsigned short i = 0; i < dice.size(); i++) {
			if (dice.at(i)->isActive()) {
				dice.at(i)->throwDie();
			}
		}

		bool firstMoveAttempted = attemptCommonMove(dice, players);

		//ask other players to perform their passive move..
		for (unsigned short i = 0; i < players.size(); i++) {
			if (players.at(i) != this) {

				cout << string(50, '\n');
				cout << "Player "<<players.at(i)->m_name<<endl<<endl;
				players.at(i)->attemptCommonMove(dice, players);
			}
		}

		cout << string(50, '\n');
		bool secondMoveAttempted = attemptSecondaryMove(dice, players);


		//if the player didn't use any of his moves, increment his misthrow
		if (!firstMoveAttempted && !secondMoveAttempted) {
			m_misthrows++;
		}
}

bool Player::attemptCommonMove(const vector<Die*>& const dice, vector<Player*>& players)
{
	cout << endl;
	card.printCard();
	cout << "0) Pass.\n";
	bool isTheMovePossible;
	unsigned short choice;
	do {
		cout << "What row would you like to cross out " << dice.at(0)->getOutput() + dice.at(1)->getOutput() << " on?>> ";
		cin >> choice;
		isTheMovePossible = crossOutNumber(dice.at(0)->getOutput() + dice.at(1)->getOutput(), choice - 1, dice, players);
		if (!isTheMovePossible) {
			cout << "You can't make this move!\n";
		}
	} while (isTheMovePossible != true && choice != 0);
	if (choice == 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Player::attemptSecondaryMove(const vector<Die*>& const dice, vector<Player*>& players)
{

	cout << "Player " << m_name << ", as you are the active player, you might perform a secondary move.\n" <<
		"You might combine any of the white die with any of the coloured die to get a number which\n" <<
		"you can place on the same colour row as the coloured die you've picked.\n\n";

	cout << endl;
	card.printCard();
	cout << endl;

	bool isTheMovePossible;
	unsigned short firstChosenDie;
	unsigned short secondChosenDie;

	do {
		//display all the die outputs..
		for (unsigned short i = 0; i < dice.size(); i++) {
			if (dice.at(i)->isActive()) {
				cout << i + 1 << ") " << setw(7) << dice.at(i)->getColour() << " die, output: " << dice.at(i)->getOutput() << endl;
			}

		}
reChooseFirstDie:
		cout << "Choose first die(white only) (0 = pass) >> ";
		cin >> firstChosenDie;
		if (firstChosenDie == 0) {
			break;
		}
		else if (firstChosenDie != 1 && firstChosenDie != 2) {
			cout << "wrong input!\n";
			goto reChooseFirstDie;;
		}
reChooseSecondDie:
		cout << "Choose second die(coloured only) (0 = pass) >> ";
		cin >> secondChosenDie;
		if (secondChosenDie == 0) {
			break;
		}
		else if (secondChosenDie < 3 || secondChosenDie > 6 || !dice.at(secondChosenDie-1)->isActive()) {
			cout << "wrong input!\n";
			goto reChooseSecondDie;
		}

		isTheMovePossible = crossOutNumber(dice.at(firstChosenDie-1)->getOutput() + dice.at(secondChosenDie-1)->getOutput(), dice.at(secondChosenDie - 1)->getColour(), dice, players);

	} while (isTheMovePossible != true && firstChosenDie != 0 && secondChosenDie != 0);

	if (firstChosenDie == 0 || secondChosenDie == 0) {
		return false;
	}
	else {
		return true;
	}

}

Card& Player::getCard()
{
	return card;
}

short& Player::getMisthrows()
{
	return m_misthrows;
}

string& Player::getName()
{
	return m_name;
}

int& Player::getTotalScore()
{
	return totalScore;
}

void Player::setTotalScore(const int & const scoreToSet)
{
	totalScore = scoreToSet;
}

bool Player::crossOutNumber(const int & numberToCrossOut, const unsigned short & row, const vector<Die*>& const dice, vector<Player*>& players)
{
	//if the row specified is bigger than the largest row index, return incorrect input.
	if (row > 3) {
		return false;
	}

	unsigned short fieldIndex;
	//get the field index with the specified value.
	for (unsigned short f = 0; f < card.getRows().at(row)->getFields().size(); f++) {
		if (card.getRows().at(row)->getFields().at(f)->getFieldNumber() == numberToCrossOut) {
			fieldIndex = f;
			break;
		}
	}

	//don't allow the player to lock the row if the conditions aren't met.
	if (fieldIndex == card.getRows().at(row)->getFields().size()-1 && !card.getRows().at(row)->isRowLockable()) {
		cout << "You are trying to lock the row without having 5 fields crossed out first!\n";
		return false;
	}

	if (card.getRows().at(row)->getFields().at(fieldIndex)->isPossibleToCrossOut() && !card.getRows().at(row)->isRowLocked()) {
		card.getRows().at(row)->getFields().at(fieldIndex)->crossOut();
		card.getRows().at(row)->getFields().at(fieldIndex)->makeNotPossibleToCrossOut();
		//make all fields behind the crossed out field not possible to be crossed out.
		for (short i = fieldIndex -1; i >= 0; i--) {
			if (!card.getRows().at(row)->getFields().at(i)->isCrossedOut() || !card.getRows().at(row)->getFields().at(i)->isCrossedOut()) {
				card.getRows().at(row)->getFields().at(i)->makeNotPossibleToCrossOut();
			}
			//if the field has already been crossed out or marked impossible to cross out, break the loop because all other fields behind it should be marked as impossible to cross out already.
			else {
				break;
			}

		}


		//if the player is trying to lock the row.. Set the die of the row's colour to inactive and set that row to inactive for all other players.
		if (fieldIndex == card.getRows().at(row)->getFields().size()-1) {
			
			dice.at(row+2)->setInactive();	//skip the 2 white dice that are at the start of the array and set the die of the locked row to be inactive.


			//set the row to be locked during next turn so it's locked by the main class at the end of the turn.
			//this alows other players to lock that row during their passive turn and still get the points for it, as specified in the instructions.
			card.getRows().at(row)->setToBeLockedDuringNextTurn(true);
		}


		card.getRows().at(row)->incrementCrossedOutFields();//increment the crossedOutFields in the chosen row and return as a valid input.
		return true;
	}
	else {
		return false;
	}
}

bool Player::operator> (const Player & other) const
{
	return (totalScore > other.totalScore);
}

Player::Player(const string & name)
{
	m_name = name;
}

Player::~Player()
{
}

ostream & operator<<(ostream & os, const Player & player)
{
	os << "Player's name: " << player.m_name << ", Player's misthrows: " << player.m_misthrows << endl;
	os << "Card: " << player.card << endl;
	return os;
}
