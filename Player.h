#pragma once
#include "Dice.h"
#include <stdlib.h>
#include <time.h>

class Player
{
public:
	Player();
	~Player();
	Dice dice[6];
	int diceLeft;
	void PlayerQuit();
	void PlayerRoll();
	void PlayerCountScore(int dieDiceNum);
	bool isAllDicesIsSetAside();
	bool isExistThreePairs();
	bool isExistTwoXThreeOfAKind();
	bool isExistSixOfAkind();
	void resetAllDicesState();
	bool isOops();
	bool isRightDieDiceNumber;
	bool isEnd;
	char strName[20];
	int totalScore;
	int currentScore;
	int diceYouWant;
};

