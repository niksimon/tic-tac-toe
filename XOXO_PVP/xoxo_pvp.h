#ifndef xoxo_pvp_h_
#define xoxo_pvp_h_

typedef struct{
	int owned;
	char id,c;
}tableXO;
void drawTable(tableXO myTable[][3], int playerMove,int ending);
void drawTableMain(tableXO myTable[][3]);
void input(tableXO myTable[][3], int playerMove);
int checkGame(tableXO myTable[][3], int playerMove, int *winner);
int checkInputField(tableXO myTable[][3], char *fieldNum, int playerMove);
void printWinner(int winner);

#endif