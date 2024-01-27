/*
	==================================================
	Workshop #2 (Part-1):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define CENTS_TOONIES 200
#define CENTS_LOONIES 100
#define CENTS_QUARENTS 25
int main() {
	//DECLARE CONSTANS
	//const int CENTS_TOONIES = 200;
	double amount;
	int balance, toonies, loonies, quarters;
	printf("Change Maker Machine\n");
	printf("====================\n");
	printf("Enter dollars and cents amount to convert to coins: $");
	scanf("%lf", &amount);
	balance = amount * CENTS_LOONIES;

	//calaculate toonies
	toonies = balance / CENTS_TOONIES;
	balance = balance % CENTS_TOONIES;//balance%=200
	printf("\n$2.00 Toonies  X %d (remaining: $%.2lf)", toonies,(double)balance/ CENTS_LOONIES);
	//caculate loonies
	loonies = balance / CENTS_LOONIES;
	balance = balance % CENTS_LOONIES;
	printf("\n$1.00 Loonies  X %d (remaining: $%.2lf)\n", loonies, (double)balance / CENTS_LOONIES);
	quarters = balance / CENTS_QUARENTS;
	balance = balance % CENTS_QUARENTS;
	printf("$0.25 Quarters X %d (remaining: $%.2lf)\n\n", quarters, (double)balance / CENTS_LOONIES);
	printf("Machine error! Thank you for letting me keep $%.2lf!\n", (double)balance / CENTS_LOONIES);


	return 0;
}


