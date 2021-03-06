/*
I declare that the attached assignment is wholly my own work in
accordance withSeneca Academic Policy. No part of this assignment has been copied
manually orelectronically from any other source (including web sites) or
distributed toother students
Name: Saif Husain Khan   Student ID: 125444158
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 10

void displayinstructions(void){
	printf("*******************\n");
 	printf("*Full Game Rules*\n");
	printf("*******************\n");
	printf("Up to 8 players compete to be the first to obtain $500\n");
	printf("Games takes place on a square board with 5 tile types\n");
	printf("->Empty Tile: No Effect\n");
	printf("->Win Tile (W): Win a random prize\n");
	printf("->Lose Tile (L): Lose a random prize\n");
	printf("->Grand Prize (G): Win a grand prize\n");
	printf("->Checkout Tile (C): Sells all your prizes for cash\n");

	printf("Players can roll 1-3 dice to determine how many tiles they move each turn\n");
	printf("If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back\n\n");
}

void clearbuffer(){
	while (getchar() != '\n');
}

void displayhighestscore(void){
	int score;
	char name;
	char playername[15];

	FILE *fp = fopen("leaderboard.dat","r");
	if (fp != NULL){
		printf("test1\n");

		while(!feof(fp)){
//			printf("test2\n");
			fscanf(fp, "GAME:%*d %[^(](%c)-%d%*c",playername,&name,&score);
		}
		fclose(fp);
	}
	else
		printf("Unsuccessful to open the file!\n");

	printf("*************************\n");
	printf("Player With the Highest Score\n");
	printf("*************************\n");
	printf("Player Name	ID	Score\n");
	printf("%s	(%c)	$%d\n\n", playername,name,score);
}

struct Player{
        char name;
        int playerscore;
        int playerprizes[SIZE];
        int prizecount;
        int playerposition;
        char f_name[31];
};

void addtoleaderboard(int game, struct Player* champion){
	FILE *fp = fopen("leaderboard.dat","a");
	if(fp != NULL){
		fprintf(fp, "GAME:%d %c(%c)-%d\n", game, champion->name, champion->name,champion->playerscore);
		fclose(fp);
	}
	else
		printf("Error! Cannot open the file!");
}

int getvalidinteger(int input, int low, int high){
	//input = 0;
	//printf("Select: ");
	//scanf("%d", &input);
	while(input < low || input > high){
	printf("Invalid input, try again: ");
	scanf("%d", &input);
	}
	return input;
}

int getValidCharacter(char low, char high){
        char input;;
        printf("Select: ");
        scanf("%c", &input);
        while(input < low || input > high){
        printf("Invalid input, try again: ");
        scanf("%c", &input);
        }
        return input;
}

void initplayer(struct Player *player){
	printf("Enter player ID: ");
	scanf("%s", &player->name);
	player->playerscore = 0;
	for (int a = 0; a < SIZE; a++)
	player->playerprizes[a]=0;
	player->prizecount = 0;
	player->playerposition = 0;

}

void seedrandom(){
	srand(time(NULL));
}

int Get_Random(int x, int y){
        int random = 0;
        random = x + rand() % (y + 1 - x);
        return random;
}

unsigned int playerroll(char playingplayer){
	int x, y, z, sum, input;
	printf("%c's turn, how many dice will you roll: ",playingplayer);
	scanf("%d", &input);
	input = getvalidinteger(input,1, 3);

	if(input == 3){
		seedrandom();
		x = Get_Random(1, 6);
		y = Get_Random(1, 6);
		z = Get_Random(1, 6);
		sum = x+y+z;
		printf("You rolled: %d %d %d\n", x, y, z);
		//printf("Advancing %d spaces\n", sum);
		return sum;
	}

	else if(input == 2){
		seedrandom();
		x = Get_Random(1, 6);
		y = Get_Random(1, 6);
		sum = x + y;
		printf("You rolled: %d %d\n", x, y);
		//printf("Advancing %d spaces\n", sum);
		return sum;
	}

	else{
		seedrandom();
		x = Get_Random(1, 6);
		printf("You rolled: %d\n", x);
		//printf("Advancing %d spaces\n", x);
		return x;
	}
}

char gettiletype(unsigned int index){
char letter;
	if (index == 0){
		letter = 'C';
	}
	else if (index % 7 == 0){
		letter = 'G';
	}
	else if (index % 5 == 0){
		letter = 'L';
	}
	else if (index % 3 == 0){
		letter = 'W';
	}
	else{
		letter = ' ';
	}
	return letter;
}

char getdisplaytile(unsigned int index, struct Player players[], unsigned int playerCount, int playingplayer){
	char letter;
	int a =0;
	if(index == players[playingplayer].playerposition){
		letter = players[playingplayer].name;
	}

	else if(index != players[playingplayer].playerposition){
		while (a < playerCount){
	if (players[a].playerposition == index){
		letter = players[a].name;
	break;
	}
	else
	letter = gettiletype(index);
	a++;
	}
	}
	return letter;
}

void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount, int playingplayer){
	int Calculate;
	const int number = size;
	int a, b, c, d;
	int variable = ((number*4)-5);
	int variable1 = size;
	int playerposition = 0;
	int k;

//The function to print the top row

	for(Calculate = 0; Calculate <= (size -1); Calculate++){
		printf(" ___ ");
	}
		printf("\n");
	for(Calculate = 0; Calculate <= (size -1); Calculate++){
		printf("| %c |", getdisplaytile(Calculate, players, playerCount, playingplayer));
	}
		printf("\n");
	for(Calculate = 0; Calculate <= (size -1); Calculate++){
		printf("|___|");
	}
		printf("\n");

//The function to print the middle row

	for(b = 0; b < (number - 2); b++){
		printf(" ___ ");

	for(a = 0; a < (number - 2); a++)
		printf("     ");
		printf(" ___ ");

		printf("\n");
		printf("| %c |", getdisplaytile(variable, players, playerCount, playingplayer));

	for(a = 0; a < (number - 2); a++)
		printf("     ");
		printf("| %c |", getdisplaytile(variable1, players, playerCount, playingplayer));

		printf("\n");
		printf("|___|");

	for(a = 0; a < (number - 2); a++)
		printf("     ");
		printf("|___|");

		printf("\n");

		variable--;
		variable1++;
	}

//The function to print the bottom row

	for(Calculate = ((number*2)+(number-3)); Calculate >= ((number*2)-2); Calculate--)
		printf(" ___ ");
		printf("\n");
	for(Calculate = ((number*2)+(number-3)); Calculate >= ((number*2)-2); Calculate--)
		printf("| %c |", getdisplaytile(Calculate, players, playerCount, playingplayer));
		printf("\n");
	for(Calculate = ((number*2)+(number-3)); Calculate >= ((number*2)-2); Calculate--)
		printf("|___|");
		printf("\n");
}

void winprize(struct Player* player){
	if (player->prizecount < SIZE){
			seedrandom();
			int i = Get_Random(10, 100);
			player->prizecount = player->prizecount + 1;

	for (int a = 0; a < SIZE; a++){
	if (player->playerprizes[a] == 0){
			player->playerprizes[a] = i;
			printf("You won a prize valued at $%d\n", i);
	break;
	}
	}
	}
	else
	printf("Inventory is already full!\n\n");
}

void addprize(struct Player* player, int i){
	if (player->prizecount < SIZE){
		seedrandom();
		player->prizecount = player->prizecount + 1;
	for (int a = 0; a < SIZE; a++){
	if (player->playerprizes[a] == 0){
			player->playerprizes[a] = i;
	break;
	}
	}
	}
	else
	printf("Inventory is already full!\n\n");
}

void wingrandprize(struct Player *player){
	if(player->prizecount < SIZE){
		seedrandom();
		int i = Get_Random(100, 200);
		player->prizecount = player->prizecount + 1;
	for (int a = 0; a < SIZE; a++){
	if (player->playerprizes[a] == 0){
			player->playerprizes[a] = i;
			printf("You won a grand prize valued at $%d\n", i);
	break;
	}
	}
	}
	else
	printf("Inventory is already full!");
}

int loseitem(struct Player* player){
	int itemsSeen, variable, temp, i;
	if (player->prizecount > 0){
		seedrandom();
		int a = Get_Random(1, player->prizecount);
		i = player->playerprizes[a-1];
		for (variable = a - 1; variable < player->prizecount; variable++){
		player->playerprizes[variable] = player->playerprizes[variable+1];
		}
		player->prizecount -= 1;
		printf("You lost a prize valued at $%d\n", i);
	}
	return i;
}

int stealitem(struct Player* player){
	int itemsSeen, variable, temp, i;
	if (player->prizecount > 0){
		seedrandom();
		int a = Get_Random(1, player->prizecount);
		i = player->playerprizes[a-1];
	for (variable = a - 1; variable < player->prizecount; variable++){
		player->playerprizes[variable] = player->playerprizes[variable+1];
	}
		player->prizecount -= 1;
	}
	return i;
}

int checkout(struct Player *player){
	int i;
player->playerscore=player->playerprizes[0]+player->playerprizes[1]+player->playerprizes[2]+player->playerprizes[3]+player->playerprizes[4]+player->playerprizes[5]+player->playerprizes[6]+player->playerprizes[7]+player->playerprizes[8]+player->playerprizes[9];
	if (player->playerscore >= 200)
		i = 1;
	else
		i = 0;
	return i;
}

int playgame(unsigned int boardsize, struct Player players[], unsigned int playerCount, int playingplayer){
	int z=2;
	int x = 0;
	displayBoard(boardsize, players, playerCount, playingplayer);
	int i = playerroll(players[playingplayer].name);
	int lap = (boardsize*4-4);
	i += players[playingplayer].playerposition;
	while(i >= lap)
		i = i - (lap);
	players[playingplayer].playerposition = i;
	int sum = 0;
	if (i == 0){
		z = checkout(&players[playingplayer]);
		printf("You checkedout for $%d\n", players[playingplayer].playerscore);
	}
	if (gettiletype(i) == ' ')
		printf("You do nothing.\n");
	if (gettiletype(i) == 'W')
		winprize(&players[playingplayer]);
	if (gettiletype(i) == 'L')
		loseitem(&players[playingplayer]);
	if (gettiletype(i) == 'G')
		wingrandprize(&players[playingplayer]);

players[playingplayer].playerscore=players[playingplayer].playerprizes[0]+players[playingplayer].playerprizes[1]+players[playingplayer].playerprizes[2]+players[playingplayer].playerprizes[3]+players[playingplayer].playerprizes[4]+players[playingplayer].playerprizes[5]+players[playingplayer].playerprizes[6]+players[playingplayer].playerprizes[7]+players[playingplayer].playerprizes[8]+players[playingplayer].playerprizes[9];

	return z;
}

int main(void){

seedrandom();
int boardsize=0;
char input = 'o';
int score = 100;
char name;
int x = 0;
int y;
int z=2;
int playerCount =0;
int a;
int b = 0;
int Thegame = 0;

        while(input != 'q'){
                printf("Welcome to CHECKOUT\n");
                printf("Main Menu\n\n");
                printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
                scanf("%s", &input);

        if(input == 'p'){
		Thegame++;
                printf("Enter number of players: ");
                scanf("%d", &playerCount);

        while(playerCount < 1 || playerCount > 8){
                printf("Invalid userinput of players,please try again: ");
                scanf("%d", &playerCount);
        }

        struct Player players[playerCount];
        if(playerCount < 1 || playerCount > 8)
                clearbuffer();
        for(a =0; a <playerCount; a++)
	        {printf("\nThe name of player:");
		scanf("%s",players[a].f_name);
		}
        for(a =0; a <playerCount; a++)
	        initplayer(&players[a]);
                printf("Enter board size: ");
		scanf("%d", &boardsize);
                boardsize = getvalidinteger(boardsize, 5, 15);

        int playingplayer=0;
        while(z != 0 || z != 1){
                z = playgame(boardsize, players, playerCount, playingplayer);

        if(z==1){
	printf("%c checkedout with $%d\n", players[playingplayer].name,players[playingplayer].playerscore);
        for(int w=0; w < playerCount; w++){
        if(players[playingplayer].playerscore >= players[w].playerscore){
        score = players[playingplayer].playerscore;
        name = players[playingplayer].name;
	printf("%c won the game!\n", players[w].name);
        addtoleaderboard(Thegame, &players[playingplayer]);
	}
        }

	if (players[playingplayer].playerscore >= 500){
		printf("Congratulations %c, you won the game!\n", players[playingplayer].name);
		break;
	}
	}

	else if(z == 0){
                printf("___\n");
                printf("   \\_______\n");
                printf("    \\++++++|\n");
                printf("     \\=====|\n");
                printf("     0---  0\n");

	 printf("%c checkedout with $%d\n", players[playingplayer].name,players[playingplayer].playerscore);

	for(int w=0; w < playerCount; w++){
        if(players[playingplayer].playerscore >= players[w].playerscore){
        score = players[playingplayer].playerscore;
        name = players[playingplayer].name;
        printf("%c won the game!\n", players[w].name);
        addtoleaderboard(Thegame, &players[playingplayer]);
	}
	}
	printf("You still have not won the game yet\n");
	players[playingplayer].playerprizes[SIZE-1] = 0;
	}

	int k = 0;
        while (k <= playerCount){
        if(players[playingplayer].playerposition == players[k].playerposition){
        if(players[playingplayer].name != players[k].name){
                printf("You landed on the same tile as %c\n", players[k].name);
                printf("You move back one tile\n");

        if (players[k].prizecount > 0){
                int a = stealitem(&players[k]);
                printf("You stole a prize from %c\n", players[k].name);
                addprize(&players[playingplayer], a);
                printf("A prize of %d was added to %c's inventory\n", a, players[playingplayer].name);
        }

        else{
        int i =0;
        while(i < playerCount){
        if(players[i].name != players[playingplayer].name && players[i].prizecount < 1 && players[i].playerposition == players[playingplayer].playerposition)
                printf("You were unable to steal from %c!\n", players[i].name);
                i++;
        }
        }

        for (int r=0; r<playerCount; r++){
                int x = players[playingplayer].playerposition -= 1;

  if (players[playingplayer].name == players[r].name){
        if (gettiletype(x) == 'W'){
                winprize(&players[playingplayer]);
        break;
        }

        else if(gettiletype(x) == 'G'){
                wingrandprize(&players[playingplayer]);
                break;
        }
        else if(gettiletype(x) == 'L'){
                loseitem(&players[playingplayer]);
        break;
        }
        break;
        }
        }
        }
	}
        k++;
        }
        playingplayer++;

        if (playingplayer == playerCount)
                playingplayer = 0;
        }
        }

        else if (input == 'r')
		displayinstructions();
        else if (input == 's')
		displayhighestscore();
	}
    printf("This game is so much more fun than bash...\n");
        return 0;

}

