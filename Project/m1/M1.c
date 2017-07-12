

#include <stdio.h>
//function to return the tile type(letter) for a certain tile

char getTileType(unsigned int index);
void displayBoard(unsigned int size);

int main(void){
	int userinput;

	if (getTileType(153) != 'W')
		printf("153 should return W");
	else if (getTileType(65) != 'L')
		printf("65 should return L");
	else if (getTileType(49) != 'G')
		printf("49 should return G");
	else if (getTileType(0) != 'C')
		printf("0 should return C");
	else if (getTileType(105) != 'G')
		printf("105 should return G");
	else if (getTileType(79) != ' ')
		printf("79 should be space");
	else{
		printf("getTileType test passed!\n");
		printf("Enter board size: ");
		scanf("%d", &userinput);

		if (userinput == 1){
			printf(" ___ \n");
			printf("| C |\n");
			printf("|___|\n");
			printf("\n");
		}
		else if (userinput == 0)
			printf("\n");
		else
			displayBoard(userinput);
	}
	return 0;
}

char getTileType(unsigned int index){
	char C;
	char G;
	char L;
	char W;
	char skip = ' ';
	if (index == 0){
		return 'C';
	}
	if (index % 7 == 0){
		return 'G';
	}
	if (index % 5 == 0){
		return 'L';
	}
	if (index % 3 == 0){
		return 'W';
	}
	else{
		return skip;
	}
}

void displayBoard(unsigned int size){
	int count;
	const int num = size;
	int i, j, a, b;
	int countA = ((num*4)-5);
	int countB = size;


	for (count = 0; count <= (size -1); count++){
		printf(" ___ ");
	}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("| %c |", getTileType(count));
	}
	printf("\n");
	for (count = 0; count <= (size -1); count++){
		printf("|___|");
	}
	printf("\n");


	for (j = 0; j < (num - 2); j++){
		printf(" ___ ");

		for (i = 0; i < (num - 2); i++)
			printf("     ");
		printf(" ___ ");

		printf("\n");
		printf("| %c |", getTileType(countA));
			for (i = 0; i < (num - 2); i++)
				printf("     ");
			printf("| %c |", getTileType(countB));

			printf("\n");

			printf("|___|");

				for (i = 0; i < (num - 2); i++)
					printf("     ");
				printf("|___|");

				printf("\n");
				countA--;
				countB++;
	}


	for (count = ((num*2)+(num-3)); count >= ((num*2)-2); count--)
		printf(" ___ ");
	printf("\n");

	for (count = ((num*2)+(num-3)); count >= ((num*2)-2); count--)
		printf("| %c |", getTileType(count));
	printf("\n");
	for (count = ((num*2)+(num-3)); count >= ((num*2)-2); count--)
		printf("|___|");
	printf("\n");
}
