#include "stdafx.h"
#include "Player.h"

#define SINGLEONE 100
#define SINGLEFIVE 50
#define THREEOFAKINDONE 1000
#define THREEOFAKINDTWO 200
#define THREEOfAKINDTHREE 300
#define THREEOFAKINDFOUR 400
#define THREEOFAKINDFIVE 500
#define THREEOFAKINDSIX 600

Player::Player()
{
	for (int i = 0; i < 6;i++)
	{
		this->dice[i] = Dice();
	}
	this->isEnd = false;
	this->diceLeft = 6;
	this->currentScore = 0;
	this->totalScore = 0;
	this->diceYouWant = 0;
	this->isRightDieDiceNumber = true;
}


Player::~Player()
{
}

void Player::PlayerQuit()
{
	exit(1);
}

bool Player::isOops()
{
	//if not exist 1 or 5, and not exist 3 of a kind ,Oops£¡

	int countNum[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			countNum[dice[i].points - 1]++;
		}
	}
	bool isExistThreeOfAKind = false;
	for (int i = 0; i < 6; i++)
	{
		if (countNum[i] >= 3)
		{
			isExistThreeOfAKind = true;
		}
	}
	if (countNum[0] == 0 && countNum[4] == 0 && !isExistThreeOfAKind)
		return true;
	else
		return false;
}

bool Player::isExistSixOfAkind()
{
	int countNum[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			countNum[dice[i].points - 1]++;
		}
	}
	bool isSixOfAkind = true;
	for (int i = 0; i < 6; i++)
	{
		if (countNum[i] != 1)
		{
			isSixOfAkind = false;
		}
	}
	return isSixOfAkind;
}

bool Player::isExistThreePairs()
{
	int countNum[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			countNum[dice[i].points - 1]++;
		}
	}
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (countNum[i] == 2)
		{
			count++;
		}
	}
	if (count==3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::isExistTwoXThreeOfAKind()
{
	int countNum[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			countNum[dice[i].points - 1]++;
		}
	}
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (countNum[i] == 3)
		{
			count++;
		}
	}
	if (count == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::PlayerRoll()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 6; i++)
	{
		this->dice[i].points = rand() % 6 + 1;
	}
	//when all dices is set aside ,we will start again, as bonus.
	
	if (this->isAllDicesIsSetAside())
	{
		this->resetAllDicesState();
	}
	cout << "\n           ";
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			cout << "[" << this->dice[i].points << "]  ";
		}
		else
		{
			cout << "[x]  ";
		}
	}
	cout << endl;
	cout << "            1    2    3    4    5    6" << endl << endl;
	if (this->isOops())
	{
		cout << "           Oops, you just farkled " <<this->strName<< endl;
		cout << "----------------------------------------------------------\n\n\n" << endl;;
		//this->totalScore = 0;
		this->isEnd = true;
	}
}

void Player::PlayerCountScore(int dieDiceNum)
{
	dieDiceNum = dieDiceNum - 1;
	int d[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		if (!this->dice[i].isSetAside)
		{
			d[i] = this->dice[i].points;
		}
	}

	if (dieDiceNum>=0&&dieDiceNum<=5)
	{
		if (d[dieDiceNum] != 1 && d[dieDiceNum] != 5)
		{
			cout << "Please enter only scoring values." << endl;
			return;
		}
		else
		{
			if (d[dieDiceNum] == 1)
			{
				this->currentScore = SINGLEONE;
				this->totalScore += SINGLEONE;
			}
			if (d[dieDiceNum] == 5)
			{
				this->currentScore = SINGLEFIVE;
				this->totalScore += SINGLEFIVE;
			}
			this->dice[dieDiceNum].isSetAside = true;
		}
		this->diceLeft--;
	}
	else if ((dieDiceNum + 1) >= 10 && (dieDiceNum + 1) <= 99)
	{
		dieDiceNum = dieDiceNum + 1;
		int d1 = dieDiceNum % 10;
		dieDiceNum = dieDiceNum / 10;
		int d2 = dieDiceNum % 10;

		this->dice[d1 - 1].isSetAside = true;
		this->dice[d2 - 1].isSetAside = true;

		int temp = this->dice[d1 - 1].points + this->dice[d2 - 1].points;
		if (temp==2)
		{//select two 1, add 200 point
			this->currentScore = 200;
			this->totalScore += 200;
		}
		else if (temp == 6)
		{//select one 1, one 5,add 150 point
			this->currentScore = 150;
			this->totalScore += 150;
		}
		else if (temp==10)
		{//select two 5 ,add 100
			this->currentScore = 100;
			this->totalScore += 100;
		}
		this->diceLeft -= 2;
	}
	else if ((dieDiceNum+1) >= 100 && (dieDiceNum+1) <= 999)
	{
		dieDiceNum = dieDiceNum + 1;
		int d1 = dieDiceNum % 10;
		dieDiceNum = dieDiceNum / 10;
		int d2 = dieDiceNum % 10;
		dieDiceNum = dieDiceNum / 10;
		int d3 = dieDiceNum;

		this->dice[d1-1].isSetAside = true;
		this->dice[d2-1].isSetAside = true;
		this->dice[d3-1].isSetAside = true;
		if ((this->dice[d1-1].points==this->dice[d2-1].points)&&(this->dice[d1-1].points==this->dice[d3-1].points)&&(this->dice[d2-1].points==this->dice[d3-1].points))
		{
			switch (this->dice[d1 - 1].points)
			{
			case 1:
				this->currentScore = THREEOFAKINDONE;
				this->totalScore += THREEOFAKINDONE;
				break;
			case 2:
				this->currentScore = THREEOFAKINDTWO;
				this->totalScore += THREEOFAKINDTWO;
				break;
			case 3:
				this->currentScore = THREEOfAKINDTHREE;
				this->totalScore += THREEOfAKINDTHREE;
				break;
			case 4:
				this->currentScore = THREEOFAKINDFOUR;
				this->totalScore += THREEOFAKINDFOUR;
				break;
			case 5:
				this->currentScore = THREEOFAKINDFIVE;
				this->totalScore += THREEOFAKINDFIVE;
				break;
			case 6:
				this->currentScore = THREEOFAKINDSIX;
				this->totalScore += THREEOFAKINDSIX;
				break;
			default:
				break;
			}
		}
		else
		{
			int countNum[6] = { 0 };
			countNum[dice[d1 - 1].points-1]++;
			countNum[dice[d2 - 1].points - 1]++;
			countNum[dice[d3 - 1].points - 1]++;
			if (countNum[0]+countNum[4]!=3)
			{
				return;
			}
			else
			{
				this->currentScore = countNum[0] * 100 + countNum[4] * 50;
				this->totalScore += this->currentScore;
			}
			
		}
			
			cout << "currentScore :" << this->currentScore << " totalScore :" << this->totalScore << endl;
			this->diceLeft = this->diceLeft - 3;
			
	}
	else if ((dieDiceNum + 1) >= 1000 && (dieDiceNum + 1) <= 9999)
	{
		dieDiceNum = dieDiceNum + 1;
		int d1 = dieDiceNum % 10;
		dieDiceNum = dieDiceNum / 10;
		int d2 = dieDiceNum % 10;
		dieDiceNum = dieDiceNum / 10;
		int d3 = dieDiceNum%10;
		dieDiceNum = dieDiceNum / 10;
		int d4 = dieDiceNum;
		int countNum[6] = { 0 };
		
		countNum[dice[d1 - 1].points - 1]++;
		countNum[dice[d2 - 1].points - 1]++;
		countNum[dice[d3 - 1].points - 1]++;
		countNum[dice[d4 - 1].points - 1]++;

		if (countNum[0] + countNum[4] != 4)
		{
			return;
		}
		else
		{
			if (countNum[0]==4)
			{
				this->currentScore = 1100;
			}
			else if (countNum[4]==4)
			{
				this->currentScore = 550;
			}
			else
			{
				this->currentScore = countNum[0] * 100 + countNum[4] * 50;
			}
			this->totalScore += this->currentScore;
			this->diceLeft = this->diceLeft - (countNum[0] + countNum[4]);
			cout << "currentScore :" << this->currentScore << " totalScore :" << this->totalScore << endl;
		}

		dieDiceNum++;
		int r = dieDiceNum % 10;
		while (r)
		{
			this->dice[r-1].isSetAside = true;
			r = dieDiceNum % 10;
			dieDiceNum = dieDiceNum / 10;
		}

	}
	else if ((dieDiceNum + 1) >= 10000 && (dieDiceNum + 1) <= 99999)
	{
		int countNum[6] = { 0 };
		for (int i = 0; i < 6; i++)
		{
			if (!this->dice[i].isSetAside)
			{
				countNum[dice[i].points - 1]++;
			}
		}

		dieDiceNum++;
		int r = dieDiceNum % 10;
		while (r)
		{
			this->dice[r - 1].isSetAside = true;
			r = dieDiceNum % 10;
			dieDiceNum = dieDiceNum / 10;
		}

		this->currentScore = countNum[0] * 100 + countNum[4] * 50;
		this->totalScore += this->currentScore;
		this->diceLeft = this->diceLeft - (countNum[0] + countNum[4]);
		cout << "currentScore :" << this->currentScore << " totalScore :" << this->totalScore << endl;
	}
	else if ((dieDiceNum + 1) >= 100000 && (dieDiceNum + 1) <= 999999)
	{//extra function
		if (isExistSixOfAkind())
		{
			cout << "you are instant winer!" << endl;
			system("pause");
		}
		if (isExistThreePairs())
		{
			this->currentScore = 1000;
			this->totalScore += 1000;
		}
		if (isExistTwoXThreeOfAKind())
		{
			this->currentScore = 2000;
			this->totalScore += 2000;
		}
		cout << "currentScore :" << this->currentScore << " totalScore :" << this->totalScore << endl;
	}
	else
	{
		cout << "Please enter only scoring values." << endl;
		//this->isRightDieDiceNumber = true;
		return ;
	}
	this->isRightDieDiceNumber = false;
}

bool Player::isAllDicesIsSetAside()
{
	bool isAll = true;
	for (int i = 0; i < 6;i++)
	{
		if (this->dice[i].isSetAside==false)
		{
			isAll = false; break;
		}
	}
	return isAll;
}

void Player::resetAllDicesState()
{
	for (int i = 0; i < 6; i++)
	{
		this->dice[i].isSetAside = false;
	}
	this->diceLeft = 6;
}