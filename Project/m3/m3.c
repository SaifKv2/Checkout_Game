

/*
I declare that the attached assignment is wholly my own work in accordance with Seneca Academic Policy. No
part of this assignment has been copied manually or electronically from any other source (including web
sites) or distributed to other students

Name: Saif Husain Khan        Student ID: 125444158
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 10

struct Player{
	char username;
	int userScore;
	int prizes[MAX];
	int pcnt;
	int ppos;
    char f_name[31];

};

int getvalidinteger(int userInput, int low, int high);
int getvalidcharacter(char low, char high);
void initplayer(struct Player *player);
void seedrandom();
int Get_Random(int a, int b);
unsigned int playerroll(char recentplyr);
char gettiletype(unsigned int index);
char getdisplaytile(unsigned int index, struct Player players[], unsigned int playerCount, int recentplyr);
void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount, int recentplyr);
void winprize(struct Player* player);
void addprize(struct Player* player, int a);
void wingrandprize(struct Player *player);
int loseitem(struct Player* player);
int stealitem(struct Player* player);
int checkout(struct Player *player);
int playgame(unsigned int boardsize, struct Player players[], unsigned int playerCount,  int recentplyr);

void clearbuffer(){
	while (getchar() != '\n');
}

int main(void){

	seedrandom();
	int boardsize=0;
	int hiscore = 100;
	char name;
	int a = 0;
	int b;
	int c=2;
	int pCount =0;
	char input = 'o';
	int k;
	int p = 0;
    int Thegame = 0;


	while (input != 'q'){
		printf("Welcome to CHECKOUT\n");
		printf("Main Menu\n\n");
		printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
		scanf("%s", &input);

		if (input == 'p'){
			printf("Enter number of players: \n");
			scanf("%d", &pCount);
			while (pCount < 1 || pCount > 8){
				printf("Invalid number of players, try again: ");
				scanf("%d", &pCount);
			}
			struct Player players[pCount];
			if (pCount < 1 || pCount > 8)
				clearbuffer();
			for (k =0; k <pCount; k++)
				initplayer(&players[k]);
			printf("Enter board size: ");
			scanf("%d", &boardsize);
			boardsize = getvalidinteger(boardsize, 5, 15);

			int recentplyr=0;
			while (c != 0 || c != 1){
				c = playgame(boardsize, players, pCount, recentplyr);

				printf("\n");
				if (c==1){
					for (int d = 0; d < pCount; d++){
					if (players[d].userScore >= 200)
						printf("%c won the game!\n", players[d].username);
					}
					hiscore = players[recentplyr].userScore;
					name = players[recentplyr].username;
					break;
				}
				else if (c==0){
					printf("You didnt win the game\n");
					break;
				}

				int j = 0;
				while (j <= pCount){
					if (players[recentplyr].ppos == players[j].ppos){
						if (players[recentplyr].username != players[j].username){
							printf("You landed on the same tile as %c\n", players[j].username);
							printf("You move back one tile\n");
							if (players[j].pcnt > 0){
								int z = stealitem(&players[j]);
								printf("You stole an item from %c\n", players[j].username);
								addprize(&players[recentplyr], z);
								printf("A prize of %d was added to %c's inventory\n", z, players[recentplyr].username);
							}
							else{
								int i =0;
								while (i < pCount){
									if (players[i].username != players[recentplyr].username && players[i].pcnt < 1 && players[i].ppos == players[recentplyr].ppos)
										printf("You were unable to steal from %c\n", players[i].username);
									i++;
								}
							}
							for (int x=0; x<pCount; x++){
								int a = players[recentplyr].ppos -= 1;
								if (players[recentplyr].username == players[x].username){
									if (gettiletype(a) == 'W'){
										winprize(&players[recentplyr]);
										break;
									}
									else if (gettiletype(a) == 'G'){
										wingrandprize(&players[recentplyr]);
										break;
									}
									else if (gettiletype(a) == 'L'){
										loseitem(&players[recentplyr]);
										break;
									}
									break;
								}
							}
						}
					}
					j++;
				}
				recentplyr++;

				if (recentplyr == pCount)
					recentplyr = 0;
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

int getvalidinteger(int userInput, int low, int high){

	while(userInput < low || userInput > high){
		printf("Invalid input, try again: ");
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


void initplayer(struct Player *player){

	printf("Enter player ID: ");
	scanf("%s", &player->username);

	player->userScore = 0;

	for (int i=0; i < MAX; i++)
        player->prizes[i]=0;

	player->pcnt = 0;
	player->ppos = 0;
}

void seedrandom(){
	srand(time(NULL));
}

int Get_Random(int a, int b){
        int ran = 0;
        ran = a + rand() % (b + 1 - a);
        return ran;
}

unsigned int playerroll(char recentplyr){
	int i, j, k, sum, userInput;

	printf("%c's turn, how many dice will you roll? ", recentplyr);
	scanf("%d", &userInput);

	userInput = getvalidinteger(userInput,1, 3);

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

char getdisplaytile(unsigned int index, struct Player players[], unsigned int playerCount, int recentplyr){
	char alphabet;
	int i =0;
	if (index == players[recentplyr].ppos){
		alphabet = players[recentplyr].username;

	}
	else if (index != players[recentplyr].ppos){
		while (i<playerCount){
			if (players[i].ppos == index){
				alphabet = players[i].username;
				break;
			}
			else
				alphabet = gettiletype(index);
			i++;
		}
	}
	return alphabet;
}

void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount, int recentplyr){
	int count;
	const int number = size;
	int i, j, a, b;
	int countA = ((number*4 )-5);
	int countB = size;

	int ppos = 0;
	int k;

	for (count = 0; count <= (size -1); count++){
		printf(" ___ ");
	}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("| %c |", getdisplaytile(count, players, playerCount, recentplyr));
	}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("|___|");
	}
	printf("\n");

	for (j = 0; j < (number - 2); j++){
		printf(" ___ ");

		for (i = 0; i < (number - 2); i++)
			printf("     ");
		printf(" ___ ");

		printf("\n");
		printf("| %c |", getdisplaytile(countA, players, playerCount, recentplyr));
		for (i = 0; i < (number - 2); i++)
			printf("     ");
		printf("| %c |", getdisplaytile(countB, players, playerCount, recentplyr));
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
		printf("| %c |", getdisplaytile(count, players, playerCount, recentplyr));
	printf("\n");
	for (count = ((number*2)+(number-3)); count >= ((number*2)-2); count--)
		printf("|___|");
	printf("\n");


}

void winprize(struct Player* player){
	if (player->pcnt < MAX){
		seedrandom();
		int s = Get_Random(10, 100);
		player->pcnt = player->pcnt + 1;

		for (int i = 0; i < MAX; i++){
			if (player->prizes[i] == 0){
				player->prizes[i] = s;
				printf("You won a prize of %d!\n\n", s);
				break;
			}
		}
	}
	else
		printf("Inventory is already full!\n\n");
}
void addprize(struct Player* player, int a){
	if (player->pcnt < MAX){
		seedrandom();
		player->pcnt = player->pcnt + 1;

		for (int i = 0; i < MAX; i++){
			if (player->prizes[i] == 0){
				player->prizes[i] = a;
				break;
			}
		}
	}
	else
		printf("Inventory is already full!\n\n");
}

void wingrandprize(struct Player *player){
	if (player->pcnt < MAX){
		seedrandom();
		int s = Get_Random(100, 200);
		player->pcnt = player->pcnt + 1;
		for (int i = 0; i < MAX; i++){
			if (player->prizes[i] == 0){
				player->prizes[i] = s;
				printf("You won a grand prize of %d!\n\n", s);
				break;
			}
		}
	}
	else
		printf("Inventory is already full!");
}

int loseitem(struct Player* player){
	int itemsSeen, next, ret, i;
	if (player->pcnt > 0){
		seedrandom();
		int a = Get_Random(1, player->pcnt);
		i = player->prizes[a-1];
		for (next = a - 1; next < player->pcnt; next++){
		player->prizes[next] = player->prizes[next+1];
		}
		player->pcnt -= 1;
		printf("You lose a prize valued at $%d!\n", i);
	}
	return ret;
}
int stealitem(struct Player* player){
	int itemsSeen, next, ret, i;
	if (player->pcnt > 0){
		seedrandom();
		int a = Get_Random(1, player->pcnt);
		i = player->prizes[a-1];
		for (next = a - 1; next < player->pcnt; next++){
		player->prizes[next] = player->prizes[next+1];
		}
		player->pcnt -= 1;
	}
	return ret;
}

int checkout(struct Player *player){
	int i;
player->userScore=player->prizes[0]+player->prizes[1]+player->prizes[2]+player->prizes[3]+player->prizes[4]+player->prizes[5]+player->prizes[6]+player->prizes[7]+player->prizes[8]+player->prizes[9];

	if (player->userScore >= 200)
		i = 1;
	else
		i = 0;

	return i;
}

int playgame(unsigned int boardsize, struct Player players[], unsigned int playerCount,  int recentplyr){
	int c = 2;

	displayBoard(boardsize, players, playerCount, recentplyr);

	int a = playerroll(players[recentplyr].username);

	int lap = (boardsize*4-4);

	a += players[recentplyr].ppos;

	while (a >= lap)
		a = a - (lap);
	players[recentplyr].ppos = a;

	int sum = 0;


	if (a == 0){
		c = checkout(&players[recentplyr]);
		printf("You checkedout for $%d!\n", players[recentplyr].userScore);
	}
	if (gettiletype(a) == ' ')
		printf("Nothing happens\n");
	if (gettiletype(a) == 'W')
		winprize(&players[recentplyr]);
	if (gettiletype(a) == 'L')
		loseitem(&players[recentplyr]);
	if (gettiletype(a) == 'G')
		wingrandprize(&players[recentplyr]);
players[recentplyr].userScore=players[recentplyr].prizes[0]+players[recentplyr].prizes[1]+players[recentplyr].prizes[2]+players[recentplyr].prizes[3]+players[recentplyr].prizes[4]+players[recentplyr].prizes[5]+players[recentplyr].prizes[6]+players[recentplyr].prizes[7]+players[recentplyr].prizes[8]+players[recentplyr].prizes[9];

	return c;
}


