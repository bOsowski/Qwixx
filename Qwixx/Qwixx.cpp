// Qwixx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Player.h"
#include "Die.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

//function prototypes
bool comparePtr(Player* a, Player* b);
int getScoreForRow(Row* row);
void displayScores(vector<Player*>& players);
bool isGameFinished(const vector<Die*>& const dice, const vector<Player*>& const players);
int startUp(vector<Player*>& player);
void setUpDice(vector<Die*>& const dice);

//main
int main()
{
	//variables
	bool playing = false;
	vector<Player*> players;
	vector<Die*> dice;



	srand((unsigned short)time(NULL));
	setUpDice(dice);
	playing = true;
	unsigned short currentPlayer = startUp(players);

	while (playing != false) {
		players.at(currentPlayer)->moveAsActivePlayer(dice, players);

		//check if any players have a row that is meant to be locked right now. If yes, lock it for all players.
		for (unsigned short i = 0; i < players.size(); i++) {
			for (int r = 0; r < players.at(i)->getCard().getRows().size(); r++) {
				if (players.at(i)->getCard().getRows().at(r)->getIsToBeLockedDuringNextTurn()) {
					for (unsigned short j = 0; j < players.size(); j++) {
						players.at(j)->getCard().getRows().at(r)->lockRow();
					}
					players.at(i)->getCard().getRows().at(r)->setToBeLockedDuringNextTurn(false);
				}
			}

		}

		//if the game is finished, change playing boolean to false.
		isGameFinished(dice, players) ? playing = false : playing = true;

		//make the next player the active player.
		currentPlayer == players.size() - 1 ? currentPlayer = 0 : currentPlayer++;
	}

	displayScores(players);

	cin.ignore();
	cin.ignore();
    return 0;
}

//functions
int startUp(vector<Player*>& players) {
	cout << "Welcome to Qwixx! Very simple - and very great!\n\n";

	short numberOfPlayers = 0;
	do {
		cout << "Enter the number of players (2 - 5) >> ";
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 2 || numberOfPlayers > 5);

	for (unsigned short i = 0; i < numberOfPlayers; i++) {
		cout << "Enter player " << i+1 << "'s name>> ";
		string name;
		cin >> name;
		players.push_back(new Player(name));
	}

	//print out the players
	for (int i = 0; i < players.size(); i++) {
		cout << *players.at(i);
	}

	return (rand() % players.size());
}

bool isGameFinished(const vector<Die*>& const dice, const vector<Player*>& const players)
{
	for (unsigned short i = 0; i < players.size(); i++) {
		if (players.at(i)->getMisthrows() >= 4) {
			cout << string(50, '\n');
			cout << "The game is finished because "<< players.at(i)->getName()<< " reached 4 misthrows!\n\n";
			return true;
		}
	}

	unsigned short amountOfInactiveDies = 0;
		for (unsigned short i = 0; i < dice.size(); i++) {
			if (!dice.at(i)->isActive()) {
				amountOfInactiveDies++;
			}
		}
		if (amountOfInactiveDies >= 2) {
			cout << string(50, '\n');
			cout << "The game is finished because 2 or more dies have become inactive!\n\n";
			return true;
		}

		return false;

}

void setUpDice(vector<Die*>& const dice) {
	dice.push_back(new Die(WHITE));
	dice.push_back(new Die(WHITE));
	dice.push_back(new Die(RED));
	dice.push_back(new Die(YELLOW));
	dice.push_back(new Die(GREEN));
	dice.push_back(new Die(BLUE));
}

void displayScores(vector<Player*>& players) {
	cout << "Below is the breakdown of scores for each player: \n\n";

	for (Player* player: players) {
		player->getCard().printCard();
		int totalScore = player->getMisthrows()*(-5);	//set the total score to the penelty for misthrows.
		cout << player->getName()<<", "<<totalScore*-1 << " is subtracted from you for all your misthrows!\n\n";
		for (Row* row: player->getCard().getRows()) {
			int totalScoreForRow = getScoreForRow(row);
			cout << "Total score for " << row->getColour() << " row: " << totalScoreForRow <<endl;	//print out the score for the current row.
			totalScore += totalScoreForRow;
		}
		cout << endl;
		cout << " Your total score is: " << totalScore<<endl<<endl;
		player->setTotalScore(totalScore);
	}

	//print out a highscore table.
	sort(players.begin(), players.end(), comparePtr);//sort the players from highest to lowest.
	cout << "---------- HighScores ----------\n\n";
	for (Player* player : players) {
		cout << player->getName() << ", your total score is " << player->getTotalScore() << endl;
	}

}
//the below function is used in conjunction with the sort to sort the players.
bool comparePtr(Player* a, Player* b) {
	return (*a > *b);
}

int getScoreForRow(Row* const row) {
	int secondDifferenceToAdd = 0;
	int totalFieldScore = 0;
	for (Field* field: row->getFields()) {
		if (field->isCrossedOut()) {
			++secondDifferenceToAdd;	//increment the second difference by 1
			totalFieldScore += secondDifferenceToAdd;	//add the incremented second diference to the total score for the row.
		}
	}
	//add the points for the locked row.
	if (row->isRowLocked()) {
		++secondDifferenceToAdd;
		totalFieldScore += secondDifferenceToAdd;
	}

	return totalFieldScore;
}




void destroyAllPlayers(const vector<Player*>& players) {
	for (short i = 0; i < players.size(); i++) {
		delete players.at(i);
	}
}