#ifndef xoxo_ai_h_
#define xoxo_ai_h_

typedef struct{
	int owned, id;
	char c;
}tableXO;
void drawTable(tableXO myTable[][3], int playerMove, int ending);
void drawTableMain(tableXO myTable[][3]);
void input(tableXO myTable[][3], int playerMove);
int checkGame(tableXO myTable[][3], int playerMove, int *winner);
int checkInputField(tableXO myTable[][3], int fieldNum, int playerMove);
void printWinner(int winner);
int AIinputfield(tableXO myTable[][3], int playerMove);

#endif