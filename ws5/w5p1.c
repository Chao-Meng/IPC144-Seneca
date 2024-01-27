/*
	==================================================
	Workshop #5 (Part-1):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define MAX_PATH 35
#define MIN_PATH 10
int max_lives=10;
int min_lives=1;
int num = 5;
int mov = 0;
int num_path = 0;

struct PlayerInfo
{
	int lives;
	char symbol;
	int treasure;
	int positions[MAX_PATH];
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
	struct PlayerInfo PlayerInfo1;
	struct GameInfo GameInfo1;
	
	printf("================================\n");
	printf("         Treasure Hunt!         ");
	printf("\n================================\n\n");
	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player:");
	scanf(" %c", &PlayerInfo1.symbol);
	
	
	do {
		printf("Set the number of lives:");
		scanf(" %d",&PlayerInfo1.lives);
		if (PlayerInfo1.lives < min_lives|| PlayerInfo1.lives>max_lives) {
			printf("     Must be between 1 and 10!\n");
		}
			
	} while (PlayerInfo1.lives<min_lives || PlayerInfo1.lives>max_lives);
		
	printf("Player configuration set-up is complete\n\n");
	printf("GAME Configuration\n");
	printf("------------------\n");

	do {
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d",&GameInfo1.path_length);
			if (GameInfo1.path_length < MIN_PATH|| GameInfo1.path_length > MAX_PATH|| GameInfo1.path_length%num!=0) {
				printf("     Must be a multiple of 5 and between 10-70!!!\n");
			}
	} while (GameInfo1.path_length < MIN_PATH || GameInfo1.path_length > MAX_PATH || GameInfo1.path_length % num!= 0);

	do {
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &mov);

		num_path =(int)((double) MAX_PATH/4*3);

		if (mov< PlayerInfo1.lives || mov>num_path) {
			printf("    Value must be between 3 and 26\n");
		}
		}while (mov< PlayerInfo1.lives || mov>num_path);

		printf("\nBOMB Placement");
		printf("\n--------------");
		printf("\nEnter the bomb positions in sets of 5 where a value");
		printf("\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.");
		printf("\n(Example: 1 0 0 1 1) NOTE: there are 35 to set!");
		
		int i = 0;
	
		printf("\n");
		for (i = 1; i <= MAX_PATH; i +=5) {
			printf("   Positions [%2d-%2d]:", i, i+num-1);
			scanf(" %d%d%d%d%d", &GameInfo1.bombs[i-1], &GameInfo1.bombs[i], &GameInfo1.bombs[i+1], &GameInfo1.bombs[i+2], &GameInfo1.bombs[i+3]);
		}
		printf("BOMB placement set");
		printf("\n\nTREASURE Placement");
		printf("\n------------------");
		printf("\nEnter the treasure placements in sets of 5 where a value");
		printf("\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.");
		printf("\n(Example: 1 0 0 1 1) NOTE: there are 35 to set!");
		printf("\n");
		for (i = 1; i <= MAX_PATH; i += 5) {
			printf("   Positions [%2d-%2d]:", i, i + num - 1);
			scanf(" %d%d%d%d%d", &GameInfo1.treasure[i-1], &GameInfo1.treasure[i], &GameInfo1.treasure[i+1], &GameInfo1.treasure[i+2], &GameInfo1.treasure[i+3]);
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
		printf(("\n   Path Length: %2d\n"), MAX_PATH);

		printf("   Bombs      : ");
		for (i = 0; i < MAX_PATH; i ++) {
			printf("%d", GameInfo1.bombs[i]);
		}
		printf("\n   Treasure   : ");
		for (i = 0; i < MAX_PATH; i++) {
			printf("%d", GameInfo1.treasure[i]);
		}
		
		printf("\n\n====================================");
		printf("\n~ Get ready to play TREASURE HUNT! ~");
		printf("\n====================================");

	



	     

	
	
	

	return 0;

}
