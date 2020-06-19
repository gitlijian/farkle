// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Player.h"

void getTotalScore(Player *p)
{
	p->isEnd = true;
	cout << "Your total score :" << p->totalScore << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

	//Player*  p = new Player[3];
	//cout << "            Hello, welcome to dice game!\n Please input 3 players's name:";
	//
	//for (int i = 0; i < 3;i++)
	//{
	//	cin >> p[i].strName;
	//}

	int targetScore = 0;
	cout << "Please input target socre:";
	cin >> targetScore;

	Player *p = new Player[2];
	
	for (int i = 0; i < 2;i++)
	{
		cout << "Please input the " << i + 1 << "st player's name:";
		cin >> p[i].strName;
	}

	int i = 0;

	while (i<2)
	{
		while (1)
		{
			cout << "************************************************************" << endl;
			cout << "           FARKLE :: A dice game for 2 players" << endl;
			cout << "************************************************************" << endl;
			cout << "Chery1 Total: " << p[i].totalScore << "  Current:" << p[i].currentScore << "  Dice Left:" << p[i].diceLeft << endl;
			cout << "************************************************************" << endl;
			cout << "It's your turn " << p[i].strName << endl;

			cout << "Do you want to [q]uit, [r]oll or [s]core? ";

			char ch;
			cin >> ch;
			int dieDiceNumber = 0;

			if (ch == 'q')
			{
				p[i].PlayerQuit();
			}
			else if (ch == 'r')
			{
				p[i].PlayerRoll();
				if (p[i].isEnd&&i < 2)
				{//next player
					i++;
					break;
				}
			}
			else if (ch == 's')
			{
				getTotalScore(&p[i]); 
				if (p[i].isEnd&&i < 2)
				{//next player
					i++;
					break;
				}
			}
			else
			{
				cout << "You input a wrong order!" << endl;
				break;
			}

			cout << "Please select the dice you want using the number under\nthe die. Do not include spaces. press Enter to finish." << endl;

			while (p[i].isRightDieDiceNumber)
			{
				cout << "\nthe dice you want are:";
				cin >> dieDiceNumber;
				p[i].PlayerCountScore(dieDiceNumber);
			}
			
			p[i].isRightDieDiceNumber = true;

			if (p[i].totalScore >= targetScore)
			{//if currentScore>=targetScore ,now palyer is winer.
				cout << "The player:" << p[i].strName << " is winer!" << endl;
				system("pause");
				break;
			}
			cout << "\n\n\n" << endl;
		}
	}

	if (p[0].totalScore>p[1].totalScore)
	{
		cout << "The winer is " << p[0].strName << endl;
	}
	else if (p[0].totalScore==p[1].totalScore)
	{
		cout << "Your points are the same." << endl;
	}
	else
	{
		cout << "The winer is " << p[1].strName << endl;
	}

	delete[]p;
	p = NULL;

	system("pause");
	return 0;
}

