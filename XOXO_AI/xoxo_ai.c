#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "xoxo_ai.h"

int main()
{
	tableXO myTable[3][3];
	int i, j, playerMove, winner;
	char repeat;
	do
	{
		playerMove = winner = 0; // playerMove = 0 human, playerMove = 1 robot
		char k = 1;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				myTable[i][j].id = k++;
				myTable[i][j].owned = 0;
				myTable[i][j].c = '_';
			}
		do{
			drawTable(myTable, playerMove, 0);
			input(myTable, playerMove);
			if (playerMove) playerMove = 0;
			else playerMove = 1;
			#ifdef _WIN32
				system("cls");
			#elif
				system("clear");
			#endif
		} while (checkGame(myTable, playerMove, &winner) == 0);
		drawTable(myTable, playerMove, 1);
		printWinner(winner);
		printf("\nPlay again (Y/N)?: ");
		scanf("%c", &repeat);
	} while (repeat == 'Y' || repeat == 'y');
	return 0;
}
void printWinner(int winner)
{
	printf("%s", winner == 3 ? "\nIt's a draw!\n" : winner == 1 ? "\nWinner is P1!\n" : "\nWinner is P2!\n");;
}
void drawTable(tableXO myTable[][3], int playerMove, int ending)
{
	#ifdef _WIN32
		system("cls");
	#elif
		system("clear");
	#endif
	// if game is not done, draw table, ask for input
	if (ending == 0)
	{
		printf("%2cPlayer %d - %c\n\n", ' ', playerMove ? 2 : 1, playerMove ? 'Y' : 'X');
		drawTableMain(myTable);
		printf("\nInput number [1-9]: ");
	}
	// game ended
	else
	{
		printf("The match has ended\n\n");
		drawTableMain(myTable);
	}
}
void drawTableMain(tableXO myTable[][3])
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		printf("%5c", ' ');
		for (j = 0; j < 3; j++)
			printf(" %c", myTable[i][j].c);
		putchar('\n');
	}
}
void input(tableXO myTable[][3], int playerMove)
{
	int fieldNum = 0, write = 0;
	char fieldNumHuman[50];
	static int firstTurn = 1;
	if (playerMove == 0) // human
	{
		do{
			do{
				drawTable(myTable, playerMove, 0);
				fgets(fieldNumHuman, 50, stdin);
			} while (strlen(fieldNumHuman) - 1 != 1 || (*fieldNumHuman <= 48 || *fieldNumHuman >= 58));
			fieldNum = *fieldNumHuman - '0';
		} while (checkInputField(myTable, fieldNum, playerMove) == 0);
	}
	else// robot
	{
		// first turn
		if (firstTurn == 1)
		{
			do{
				srand((int)time(NULL));
				fieldNum = rand() % 10;		
			} while (checkInputField(myTable, fieldNum, playerMove) == 0);
			firstTurn = 0;
		}
		// next
		else
		{
			// if there is potential for robot move, write in
			if (fieldNum = AIinputfield(myTable, 2))
			{
				write = checkInputField(myTable, fieldNum, playerMove);
			}
			// else, protect field from human
			else
			{
				fieldNum = AIinputfield(myTable, 1);
				// if there is potential field
				if (fieldNum)
					write = checkInputField(myTable, fieldNum, playerMove);
				// else, random field, end
				else
					do{
						srand((int)time(NULL));
						fieldNum = rand() % 10;
					} while (checkInputField(myTable, fieldNum, playerMove) == 0);
			}
		}
	}
}
int AIinputfield(tableXO myTable[][3], int playerMove)
{
	int i, j, n, potential;

	// horizontal
	for (i = 0; i < 3; i++)
	{
		potential = n = 0;
		for (j = 0; j < 3; j++)
		{
			if (myTable[i][j].owned == playerMove)
				n++;
			else {
				if (myTable[i][j].owned == 0)
					potential = myTable[i][j].id;
			}
		}
		if (n == 2 && potential != 0)
			return potential;
	}

	// vertical
	for (i = 0; i < 3; i++)
	{
		potential = n = 0;
		for (j = 0; j < 3; j++)
		{
			if (myTable[j][i].owned == playerMove)
				n++;
			else {
				if (myTable[j][i].owned == 0)
					potential = myTable[j][i].id;
			}
		}
		if (n == 2 && potential != 0)
			return potential;
	}

	// diagonal
	potential = n = 0;
	for (i = 0; i < 3; i++)
	{
		if (myTable[i][i].owned == playerMove)
			n++;
		else {
			if (myTable[i][i].owned == 0)
				potential = myTable[i][i].id;
		}
		if (n == 2 && potential != 0)
			return potential;
	}
	potential = n = 0;
	for (i = 0; i < 3; i++)
	{
		if (myTable[i][2-i].owned == playerMove)
			n++;
		else {
			if (myTable[i][2-i].owned == 0)
				potential = myTable[i][2-i].id;
		}
		if (n == 2 && potential != 0)
			return potential;
	}
	potential = n = 0;
	return potential;
}

int checkGame(tableXO myTable[][3], int playerMove, int *winner)
{
	int i, j, n, m, k, l, countOwned, player;
	n = m = k = l = countOwned = 0;
	if (playerMove) player = 1;
	else player = 2;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) // horizontal
			if (myTable[i][j].owned == player) n++;
		for (j = 0; j < 3; j++) // vertical
			if (myTable[j][i].owned == player) m++;
		if (myTable[i][i].owned == player) k++; // diagonal 1
		if (myTable[2 - i][i].owned == player) l++; // diagonal 2
		if (n == 3 || m == 3 || k == 3 || l == 3)
		{
			*winner = player;
			break;
		}
		n = m = 0;
	}
	k = l = 0;
	if (*winner == 0)
	{
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				if (myTable[i][j].owned)
					countOwned++;
		if (countOwned == 9) *winner = 3;
		countOwned = 0;
	}
	return *winner;
}
int checkInputField(tableXO myTable[][3], int fieldNum, int playerMove)
{
	int i, j, checked = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (myTable[i][j].id == fieldNum)
				if (myTable[i][j].owned == 0)
				{
					switch (playerMove)
					{
					case 0:
						myTable[i][j].c = 'X';
						myTable[i][j].owned = 1;
						break;
					case 1:
						myTable[i][j].c = 'Y';
						myTable[i][j].owned = 2;
						break;
					}
					checked = 1;
					break;
				}
	return checked;
}