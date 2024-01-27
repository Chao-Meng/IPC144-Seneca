/*
	==================================================
	Workshop #2 (Part-2):
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
#define CENTS_DIMES 10
#define CENTS_NICKELS 5
#define CENTS_PENNIES 1
int main() {
	//DECLARE CONSTANS
	//const int CENTS_TOONIES = 200;
	double amount, fee, rate = 0.05;
	int balance, toonies, loonies, quarters, dimes, nickels, pennies;
	printf("Change Maker Machine\n");
	printf("====================\n");
	printf("Enter dollars and cents amount to convert to coins: $");
	scanf("%lf", &amount);

	printf("Service fee (5.0 percent): %.2lf\n", fee = amount * rate);
	printf("Balance to dispense: $%.2lf\n", amount = amount - fee);

	balance = amount * CENTS_LOONIES;

	//calaculate toonies
	toonies = balance / CENTS_TOONIES;
	balance = balance % CENTS_TOONIES;//balance%=200
	printf("\n$2.00 Toonies  X %d (remaining: $%.2lf)", toonies, (double)balance / CENTS_LOONIES);

	//caculate loonies
	loonies = balance / CENTS_LOONIES;
	balance = balance % CENTS_LOONIES;
	printf("\n$1.00 Loonies  X %d (remaining: $%.2lf)\n", loonies, (double)balance / CENTS_LOONIES);

	quarters = balance / CENTS_QUARENTS;
	balance = balance % CENTS_QUARENTS;
	printf("$0.25 Quarters X %d (remaining: $%.2lf)\n", quarters, (double)balance / CENTS_LOONIES);

	dimes = balance / CENTS_DIMES;
	balance = balance % CENTS_DIMES;
	printf("$0.10 Dimes    X %d (remaining: $%.2lf)\n", dimes, (double)balance / CENTS_LOONIES);

	nickels = balance / CENTS_NICKELS;
	balance = balance % CENTS_NICKELS;
	printf("$0.05 Nickels  X %d (remaining: $%.2lf)\n", nickels, (double)balance / CENTS_LOONIES);

	pennies = balance / CENTS_PENNIES;
	balance = balance % CENTS_PENNIES;
	printf("$0.01 Pennies  X %d (remaining: $%.2lf)\n\n", pennies, (double)balance / CENTS_LOONIES);
	printf("All coins dispensed!");


	return 0;
}