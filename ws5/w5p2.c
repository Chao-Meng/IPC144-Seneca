/*
	==================================================
	Workshop #5 (Part-2):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define MAX_PATH 70
#define MIN_PATH 10
int max_lives = 10;
int min_lives = 1;
int num = 5;
int mov = 0;
int num_path = 0;
struct PlayerInfo
{
	int lives;
	char symbol;
	int treasure;
	char history_positions[MAX_PATH];
};
struct GameInfo
{
	int max_mov;
	int path_length;
	int bombs[MAX_PATH];
	int treasure[MAX_PATH];
};

int main()
{
	struct PlayerInfo PlayerInfo1 = { 0 };
	struct GameInfo GameInfo1;
	printf("================================\n");
	printf("         Treasure Hunt!         \n");
	printf("================================\n\n");
	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf(" %c", &PlayerInfo1.symbol);
	do {
		printf("Set the number of lives: ");
		scanf(" %d", &PlayerInfo1.lives);
		if (PlayerInfo1.lives < min_lives || PlayerInfo1.lives>max_lives) {
			printf("     Must be between 1 and 10!\n");
		}
	} while (PlayerInfo1.lives<min_lives || PlayerInfo1.lives>max_lives);

	printf("Player configuration set-up is complete\n\n");
	printf("GAME Configuration\n");
	printf("------------------\n");
	do {
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &GameInfo1.path_length);
		if (GameInfo1.path_length < MIN_PATH || GameInfo1.path_length > MAX_PATH || GameInfo1.path_length % num != 0) {
			printf("     Must be a multiple of 5 and between 10-70!!!\n");
		}
	} while (GameInfo1.path_length < MIN_PATH || GameInfo1.path_length > MAX_PATH || GameInfo1.path_length % num != 0);
	do {
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &mov);
		num_path = (int)((double)GameInfo1.path_length / 4 * 3);

		if (mov< PlayerInfo1.lives || mov>num_path) {
			printf("    Value must be between 3 and 15\n");
		}
	} while (mov< PlayerInfo1.lives || mov>num_path);

	printf("\nBOMB Placement");
	printf("\n--------------");
	printf("\nEnter the bomb positions in sets of 5 where a value");
	printf("\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.");
	printf("\n(Example: 1 0 0 1 1) NOTE: there are %2d to set!", GameInfo1.path_length);
	int i = 0;
	printf("\n");
	for (i = 1; i <= GameInfo1.path_length; i += 5) {
		printf("   Positions [%2d-%2d]: ", i, i + num - 1);
		scanf(" %d%d%d%d%d", &GameInfo1.bombs[i - 1], &GameInfo1.bombs[i], &GameInfo1.bombs[i + 1], &GameInfo1.bombs[i + 2], &GameInfo1.bombs[i + 3]);
	}
	printf("BOMB placement set");
	printf("\n\nTREASURE Placement");
	printf("\n------------------");
	printf("\nEnter the treasure placements in sets of 5 where a value");
	printf("\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.");
	printf("\n(Example: 1 0 0 1 1) NOTE: there are %2d to set!", GameInfo1.path_length);
	printf("\n");
	for (i = 1; i <= GameInfo1.path_length; i += 5) {
		printf("   Positions [%2d-%2d]: ", i, i + num - 1);
		scanf(" %d%d%d%d%d", &GameInfo1.treasure[i - 1], &GameInfo1.treasure[i], &GameInfo1.treasure[i + 1], &GameInfo1.treasure[i + 2], &GameInfo1.treasure[i + 3]);
	}
	printf("TREASURE placement set");
	printf("\n\nGAME configuration set-up is complete...\n");
	printf("\n------------------------------------");
	printf("\nTREASURE HUNT Configuration Settings");
	printf("\n------------------------------------");
	printf("\nPlayer:");
	printf("\n   Symbol     : %c", PlayerInfo1.symbol);
	printf("\n   Lives      : %d", PlayerInfo1.lives);
	printf("\n   Treasure   : [ready for gameplay]");
	printf("\n   History    : [ready for gameplay]");
	printf("\n\nGame:");
	printf(("\n   Path Length: %2d\n"), GameInfo1.path_length);
	printf("   Bombs      : ");
	for (i = 0; i < GameInfo1.path_length; i++) {
		printf("%d", GameInfo1.bombs[i]);
	}
	printf("\n   Treasure   : ");
	for (i = 0; i < GameInfo1.path_length; i++) {
		printf("%d", GameInfo1.treasure[i]);
	}
	printf("\n\n====================================");
	printf("\n~ Get ready to play TREASURE HUNT! ~");
	printf("\n====================================\n\n");
	int j = 0;
	int mov_num = 0;
	int mov_rem = 10;
	int d = 0;
	char position[MAX_PATH];
	int re_position[MAX_PATH] = { 0 };
	for (d = 0; d <= GameInfo1.path_length; d++) {
		position[d] = '-';
	}
	printf("  ");
	/*for (j = 0; j <= GameInfo1.path_length; j++)
	{
		printf("%c", ' ');
	}
	printf("\n");
	printf("  ");*/
	for (j = 0; j < GameInfo1.path_length; j++)
	{
		printf("%c", position[j]);
	}
	printf("\n");
	printf("  ");
	for (j = 1; j <= GameInfo1.path_length; j++) {
		if (j % 10 != 0) {
			printf("|");
		}
		else {

			printf("%d", j / 10);
		}
	}
	printf("\n");
	printf("  ");
	for (j = 1; j <= GameInfo1.path_length; j++) {

		printf("%d", j % 10);
	}
	printf("\n+---------------------------------------------------+\n");
	printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", PlayerInfo1.lives, PlayerInfo1.treasure, mov_rem);//
	printf("+---------------------------------------------------+\n");

	int min_mov = 1;

	int k = 0;
	char a;
	int b = 0;
	int f = 0;
	do {
		printf("Next Move [%d-%d]: ", min_mov, GameInfo1.path_length);
		scanf("%d", &mov_num);


		if (mov_num < min_mov || mov_num>GameInfo1.path_length) {
			printf("  Out of Range!!!\n");
		}
		else {
			int re_mov_num = 0; 
			int iLen = 0;
			for (iLen = 0; iLen < MAX_PATH; iLen++) {
				if (mov_num == re_position[iLen]) {
					re_mov_num = 1;
					break;
				}
			}
			if (re_mov_num == 1)

			{
				printf("\n===============> Dope! You've been here before!\n\n");
				printf("  ");
				for (k = 1; k <mov_num; k++) {
					printf("%c", ' ');
				}

				int h = GameInfo1.path_length - 1 - k;//
				printf("%c", PlayerInfo1.symbol);
				for (h = mov_num; h <GameInfo1.path_length; h++) {//
					printf("%c", ' ');//
				}
				printf("\n");//

			    //printf("%c\n", PlayerInfo1.symbol);
			
				printf("  ");//
				for (j = 0; j < GameInfo1.path_length; j++)
				{
					//if (j == mov_num) {//The original method does not apply in this part
					//	printf("%c", a);//
					//}
					//else {
					//	printf("%c", '-');
					//}
					if (j == mov_num - 1) {
					
						PlayerInfo1.history_positions[b] = position[b];
						printf("%c", position[j]);

					}
					else {

						printf("%c", position[j]);
					}
				}
				printf("\n");
				printf("  ");//
				for (j = 1; j <= GameInfo1.path_length; j++) {
					if (j % 10 != 0) {
						printf("|");
					}
					else {
						printf("%d", j / 10);
					}
				}
				printf("\n");
				printf("  ");
				for (j = 1; j <= GameInfo1.path_length; j++) {
					printf("%d", j % 10);
				}
				printf("\n+---------------------------------------------------+\n");
				printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", PlayerInfo1.lives, PlayerInfo1.treasure, mov_rem);
				printf("+---------------------------------------------------+\n");
			}
			else {
				if (GameInfo1.bombs[mov_num - 1] == GameInfo1.treasure[mov_num - 1]) {
					if (GameInfo1.bombs[mov_num - 1] == 1) {

						a = '&';
					}
					else {
						a = '.';
					}
				}
				else {
					if (GameInfo1.bombs[mov_num - 1] == 1 && GameInfo1.treasure[mov_num - 1] == 0) {
						a = '!';
					}
					if (GameInfo1.treasure[mov_num - 1] == 1 && GameInfo1.bombs[mov_num - 1] == 0) {
						a = '$';
					}
				}
				switch (a) {
				case'.':
					printf("\n===============> [%c] ...Nothing found here... [%c]\n\n", a, a);
					break;
				case'!':
					PlayerInfo1.lives--;
					printf("\n===============> [%c] !!! BOOOOOM !!! [%c]\n\n", a, a);
					break;
				case'$':
					PlayerInfo1.treasure++;
					printf("\n===============> [%c] $$$ Found Treasure! $$$ [%c]\n\n", a, a);
					break;
				case'&':
					PlayerInfo1.lives--;
					PlayerInfo1.treasure++;
					printf("\n===============> [%c] !!! BOOOOOM !!! [%c]", a, a);
					printf("\n===============> [%c] $$$ Life Insurance Payout!!! [%c]\n\n", a, a);
					break;
				}
				if (PlayerInfo1.lives == 0) {
					printf("No more LIVES remaining!\n\n");
				}
				if (mov_num == 0) {
					printf("No more MOVES remaining!\n\n");
				}

				printf("  ");
				for (k = 1; k < mov_num; k++) {
					printf("%c", ' ');
				}
				
				printf("%c", PlayerInfo1.symbol);
				int h = GameInfo1.path_length - 1 - k;//
				for (h = mov_num; h <GameInfo1.path_length; h++) {//
					printf("%c", ' ');//
				}
				printf("\n");//
				printf("  ");
				for (j = 0; j < GameInfo1.path_length; j++)
				{
					if (j == mov_num - 1) {
						position[j] = a;
						PlayerInfo1.history_positions[b] = position[b];
						printf("%c", position[j]);

					}
					else {

						printf("%c", position[j]);
					}
				}
				printf("\n");
				printf("  ");
				for (j = 1; j <= GameInfo1.path_length; j++) {
					if (j % 10 != 0) {
						printf("|");
					}
					else {

						printf("%d", j / 10);
					}
				}
				printf("\n");
				printf("  ");

				for (j = 1; j <= GameInfo1.path_length; j++) {
					printf("%d", j % 10);
				}
				printf("\n+---------------------------------------------------+\n");
				printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", PlayerInfo1.lives, PlayerInfo1.treasure, --mov_rem);
				printf("+---------------------------------------------------+\n");
			}
		}
		b = mov_num;

		for (f = 0; f < MAX_PATH; f++) {
			if (re_position[f] == 0) {
				re_position[f] = b;
				break;
			}
		}
	} while (PlayerInfo1.lives != 0 && mov_rem != 0);

	printf("\n##################\n");
	printf("#   Game over!   #\n");
	printf("##################\n\n");
	printf("You should play again and try to beat your score!");
	return 0;
}
