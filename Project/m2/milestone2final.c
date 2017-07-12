/*
I declare that the attached assignment is wholly my own work in accordance with Seneca Academic Policy. No
part of this assignment has been copied manually or electronically from any other source (including web
sites) or distributed to other students

Name: Saif Husain Khan       Student ID: 125444158
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 10

int getvalidinteger(int low, int high);
int getvalidcharacter(char low, char high);
void initplayer(int* playerscore, int playerprizes[], unsigned int*prizecount, char* playername, int* playerposition);
void seedrandom();
int Get_Random(int a, int b);
unsigned int playerroll();
char gettiletype(unsigned int index);
char getdisplaytile(unsigned int index, unsigned int playerposition, char playername);
void displayBoard(unsigned int size, unsigned int playerposition, char playername);
void winprize(int playerprizes[], unsigned int *prizecount);
void wingrandprize(int playerprizes[], unsigned int* prizecount);
int loseitem(int playerprizes[], unsigned int* prizecount);
int checkout(int* playerscore, int playerprizes[], unsigned int* prizecount);
int playgame(unsigned int boardsize, int *playerscore, int playerprizes[], unsigned int *prizecount, char *playername, int *playerposition);
char getdisplaytile(unsigned int, unsigned int, char);

int main(void){

	seedrandom();
	int pScore = 0;
	unsigned int pCount = 0;
	int hiscore = 100;
	int pPosition = 0;
	int pPrizes[SIZE] = {0};
	int boardsize;
	int a = 0;
	int b;
	int c=2;
    char input = 'o';
	char pName;
    char name;


	while (input != 'q'){
		printf("Welcome to CHECKOUT\n");
		printf("Main Menu\n\n");
		printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
		scanf("%s", &input);

		if (input == 'p'){
			printf("Number of players is 1\n");

			initplayer(&pScore, pPrizes, &pCount, &pName, &pPosition);
			printf("Enter board size: ");
			scanf("%d", &boardsize);

			playgame(boardsize, &pScore, pPrizes, &pCount, &pName, &pPosition);
			a = a + pPosition;


			while (&pPosition != 0){
				c = playgame(boardsize, &pScore, pPrizes, &pCount, &pName, &a);

				if (c==1){
					printf("You won the game!\n");
					hiscore = pScore;
					name = pName;
					break;
				}
				else if (c==0){
					printf("Your score wasn't high enough\n");
					break;
				}

			}
		}
		else if (input == 'r')
			printf("Enter a letter to continue\n\n");
		else if (input == 's'){
			printf("--\n");
			printf("  \\ \n");
			printf("   --------\n");
			printf("    \\++++++|\n");
			printf("     \\=====|\n");
			printf("     0---  0\n");

			printf("HI SCORE: %d Player Name: %c\n\n", hiscore, name);
		}

	}
	printf("This game is so much more fun than bash...\n");
	return 0;
}

int getvalidinteger(int low, int high){

	int userInput = 0;

	printf("Select: ");
	scanf("%d", &userInput);

	while(userInput < low || userInput > high){
		printf("Invalid Input, try again: ");
		scanf("%d", &userInput);
	}
	return userInput;
}

int getvalidcharacter(char low, char high){

	char userInput;;

        printf("Select: ");
        scanf("%c", &userInput);

        while(userInput < low || userInput > high){
                printf("Invalid Input, try again: ");
                scanf("%c", &userInput);
        }
        return userInput;
}

void initplayer(int* playerscore, int playerprizes[], unsigned int*prizecount, char* playername, int* playerposition){

	*playerscore = 0;
	playerprizes[SIZE]=0;
	*prizecount = 0;
	*playerposition = 0;

	printf("Enter player ID: ");
	scanf("%s", &*playername);
}

void seedrandom(){
	srand(time(NULL));
}

int Get_Random(int a, int b){
        int ran = 0;
        ran = a + rand() % (b + 1 - a);
        return ran;
}

unsigned int playerroll(){
		int i, j, k, sum, userInput;
	printf("Your turn, how many dice will you roll? ");
	scanf("%d", &userInput);
	while (userInput <= 0 || userInput > 3){
		printf("Invalid Input, try again: ");
		scanf("%d", &userInput);
	}
	if (userInput == 3){
		seedrandom();
		i = Get_Random(1, 6);
		j = Get_Random(1, 6);
		k = Get_Random(1, 6);

		sum = i+j+k;
		printf("You rolled: %d %d %d\n", i, j, k);
		printf("Advancing %d spaces\n", sum);
		return sum;
	}
	else if (userInput == 2){
		seedrandom();
		i = Get_Random(1, 6);
		j = Get_Random(1, 6);
		sum = i + j;
		printf("You rolled: %d %d\n", i, j);
		printf("Advancing %d spaces\n", sum);
		return sum;
	}
	else {
		seedrandom();
		i = Get_Random(1, 6);
		printf("You rolled: %d\n", i);
		printf("Advancing %d spaces\n", i);
		return i;
	}
}

char gettiletype(unsigned int index){

	char alphabet;
		if (index == 0){
			alphabet = 'C';
		}
		else if (index % 7 == 0){
			alphabet = 'G';
		}
		else if (index % 5 == 0){
			alphabet = 'L';
		}
		else if (index % 3 == 0){
			alphabet = 'W';
		}
		else{
			alphabet = ' ';
		}
	return alphabet;
}

char getdisplaytile(unsigned int index, unsigned int playerposition, char playername){

	if (index != playerposition){
		char alphabet = gettiletype(index);
		return alphabet;
	}
	else
		return playername;


}

void displayBoard(unsigned int size, unsigned int playerposition, char playername){

	int count;
	const int number = size;
	int i, j, a, b;
	int countA = ((number*4)-5);
	int countB = size;

	int ppos = 0;
	int k;
	ppos = playerposition;
	while (ppos > countA){
		ppos = ppos - (countA+1);
	}

	for (count = 0; count <= (size -1); count++){
		printf(" ___ ");
	}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("| %c |", getdisplaytile(count, ppos, playername));
		}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("|___|");
	}
	printf("\n"); //counter counter1

	for (j = 0; j < (number - 2); j++){
		printf(" ___ ");

		for (i = 0; i < (number - 2); i++)
			printf("     ");
		printf(" ___ ");

		printf("\n");
		printf("| %c |", getdisplaytile(countA, ppos, playername));
		for (i = 0; i < (number - 2); i++)
			printf("     ");
		printf("| %c |", getdisplaytile(countB, ppos, playername));
		printf("\n");

		printf("|___|");

		for (i = 0; i < (number - 2); i++)
			printf("     ");
		printf("|___|");

		printf("\n");
		countA--;
		countB++;
	}

	for (count = ((number*2)+(number-3)); count >= ((number*2)-2); count--)
		printf(" ___ ");
	printf("\n");

	for (count = ((number*2)+(number-3)); count >= ((number*2)-2); count--)
		printf("| %c |", getdisplaytile(count, ppos, playername));
	printf("\n");
	for (count = ((number*2)+(number-3)); count >= ((number*2)-2); count--)
		printf("|___|");
	printf("\n");
}

void winprize(int playerprizes[], unsigned int *prizecount){
	if (*prizecount < SIZE){
		seedrandom();
		int s = Get_Random(10, 100);
		*prizecount = *prizecount+1;

		for (int i = 0; i < SIZE; i++){
			if (playerprizes[i] == 0){
				playerprizes[i] = s;
				printf("You won a prize of %d!\n\n", s);
				break;
			}
		}
	}
	else
		printf("Inventory is already full!\n\n");
}

void wingrandprize(int playerprizes[], unsigned int* prizecount){

	if (*prizecount < SIZE){
		seedrandom();
		int s = Get_Random(100, 200);
		*prizecount = *prizecount+1;
		for (int i = 0; i < SIZE; i++){
			if (playerprizes[i] == 0){
				playerprizes[i] = s;
				printf("You won a grand prize of %d!\n\n", s);
				break;
			}
		}
	}
	else
		printf("Inventory is already full!");
}

int loseitem(int playerprizes[], unsigned int* prizecount){

	int itemsSeen, next, ret;
	if (*prizecount > 0){
		seedrandom();
		int a = Get_Random(1, *prizecount);
		int i = playerprizes[a-1];
		for (next = a - 1; next < *prizecount; next++){
		playerprizes[next] = playerprizes[next+1];
		}
		*prizecount -= 1;
		printf("You lose a prize valued at $%d!\n", i);
	}
	return ret;
}

int checkout(int* playerscore, int playerprizes[], unsigned int* prizecount){
	int i;
*playerscore=playerprizes[0]+playerprizes[1]+playerprizes[2]+playerprizes[3]+playerprizes[4]+playerprizes[5]+playerprizes[6]+playerprizes[7]+playerprizes[8]+playerprizes[9];

	if (*playerscore >= 200)
		i= 1;
	else
		i = 0;

	return i;
}

int playgame(unsigned int boardsize, int *playerscore, int playerprizes[], unsigned int *prizecount, char *playername, int *playerposition){

	displayBoard(boardsize, *playerposition, *playername);
	printf("Score: %d", *playerscore);

	printf("    Inventory(%d items): ", *prizecount);
	for (int i = 0; i < *prizecount; i++)
		printf("%d, ", playerprizes[i]);

	printf("\n");
	int a = playerroll();
	int c=2;

	int round = (boardsize*4-4);

	*playerposition = *playerposition+a;
	while (*playerposition >= round)
		*playerposition = *playerposition - (round);


	int name = *playername;
	int sum = 0;
	if (*playerposition == 0){
		c = checkout(playerscore, playerprizes, prizecount);
		printf("You checkedout!\n");
	}
	if (gettiletype(*playerposition) == ' ')
		printf("Nothing happens, go again.\n");
	if (gettiletype(*playerposition) == 'W')
		winprize(playerprizes, prizecount);
	if (gettiletype(*playerposition) == 'L')
		loseitem(playerprizes, prizecount);
	if (gettiletype(*playerposition) == 'G')
		wingrandprize(playerprizes, prizecount);


*playerscore=playerprizes[0]+playerprizes[1]+playerprizes[2]+playerprizes[3]+playerprizes[4]+playerprizes[5]+playerprizes[6]+playerprizes[7]+playerprizes[8]+playerprizes[9];
	printf("\n");

	return c;
}
