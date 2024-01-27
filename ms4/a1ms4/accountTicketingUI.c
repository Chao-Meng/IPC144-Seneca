/*
	==================================================
	Assignment:  1
	Milestone:   4
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include "account.h"
#include "accountTicketingUI.h" 
#include "commonHelpers.h"

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
	
}
void displayAccountDetailRecord(const struct Account* account)
{
	char strA[20] = { 'A','G','E','N','T','\0' };
	char strC[20] = { 'C','U','S','T','O','M','E','R', '\0' };
	char Type[20] = { 0 };
	if (account->accountType == 'A') {
		strcpy(Type, strA);
	}
	if (account->accountType == 'C') {
		strcpy(Type, strC);
	}
	int i = 0;
	char password[10] = { 0 };
	for (i = 0; i < strlen(account->login.password); i++) {
		if (i % 2 == 1) {
			password[i] = '*';
		}
		else {
			password[i] = account->login.password[i];
		}
	}
	printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s", account->accountNumber, Type,
		account->person.fullName, account->person.yearBorn, account->person.familyIncome,
		account->person.homeCountry, account->login.userName, password);
	//login->password
}

void applicationStartup(struct Account account[], int maxnum){
	for (;;) {
		int iMenuLoginRet = menuLogin(account, maxnum);
		if (iMenuLoginRet == -1) {
			break;
		} else if (iMenuLoginRet != -2) {
			menuAgent(account, maxnum, &account[iMenuLoginRet]);
		}
	}
}

int menuLogin(const struct Account account[], int maxnum) {
	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");
	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printf("----------------------------------------------\n\n");
	printf("Selection: ");
	int num = getIntFromRange(0,1);
	int accountnumber = 0;
	int i = -1;
	int flag = 0;
	char answer = 0;
	if (num == 0) {
		printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
		answer = getCharOption("yYnN");
		printf("\n");
		if (answer == 'y' || answer == 'Y') {
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
		}
		else {
			i = -2;
		}

	} else if (num == 1) {
		printf("\nEnter your account#: ");
		scanf("%d", &accountnumber);
		
		for (i = 0; i < maxnum; i++) {
			if (accountnumber == account[i].accountNumber && account[i].accountType=='A') {
				flag = 1;
				printf("\n");
				break;
			}
		}
		if (flag != 1) {
			i = -2;
		}
	}
	if (flag != 1 && num == 1) {
		printf("ERROR:  Login failed!\n\n");
		clearStandardInputBuffer();
		pauseExecution();
	}
	return i;
}

void menuAgent(struct Account account[], int maxnum, const struct Account* acc) {
	for (;;) {
		char strC[20] = { 'C','U','S','T','O','M','E','R', '\0' };
		char strA[20] = { 'A','G','E','N','T','\0' };
		char Type[20] = { 0 };
		if (acc->accountType == 'A') {
			strcpy(Type, strA);
		}
		if (acc->accountType == 'C') {
			strcpy(Type, strC);
		}
		printf("%5s: %s (%5d)\n", Type, acc->person.fullName, acc->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		int num = getIntFromRange(0, 4);
		int i = 0;
		int accountnumber = 0;
		int iEmptyIndex = -1;
		switch (num) {
		case 0:
			printf("\n### LOGGED OUT ###\n\n");
			return;
		case 1:
			for (i = 0; i < maxnum; i++) {
				if (account[i].accountNumber <= 0) {
					iEmptyIndex = i;
					break;
				}
			}
			if (iEmptyIndex == -1) {
				printf("ERROR: Account listing is FULL, call ITS Support!\n");
			}
			else {
				printf("\n");
				getAccount(&account[iEmptyIndex]);
				//printf("\n%5s: %s (%5d)\n", "AGENT", account[i].person.fullName, account[i].accountNumber);
			}
			break;
		case 2:
			printf("\nEnter the account#: ");
			scanf("%d", &accountnumber);
			printf("\n");
			int iFinded = findAccountIndexByAcctNum(accountnumber, account, maxnum, 0);
			if (iFinded != -1) {
				updateAccount(&account[iFinded]);
			}
			else {
				printf("ERROR\n"); 
			}
			break;
		case 3:
			printf("\nEnter the account#: ");
			scanf("%d", &accountnumber);
			if (accountnumber == acc->accountNumber) {
				printf("\nERROR: You can't remove your own account!\n\n");
				clearStandardInputBuffer();
				pauseExecution();
				break;
			}
			else {
				int iFinded = findAccountIndexByAcctNum(accountnumber, account, maxnum, 0);
				if (iFinded != -1) {
					displayAccountDetailHeader();
					displayAccountDetailRecord(&account[iFinded]);
					printf("\n");
					clearStandardInputBuffer();
					printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
					char option = getCharOption("yYnN");
					if (option == 'Y' || option == 'y') {
						account[iFinded].accountNumber = 0;
						printf("\n*** Account Removed! ***\n\n");
						pauseExecution();
						
					}
				}
			}
			break;
		case 4:
			printf("\n");
			displayAllAccountDetailRecords(account, maxnum);
			//printf("\n");
			break;
		default:
			break;
		}
	}
}

int findAccountIndexByAcctNum(int accountnumber, const struct Account account[], int maxnum, int number) {
	if (number != 0) {
		printf("Enter the account#:");
		scanf("%d", &accountnumber);
	}

	int i = 0;
	int iFinded = 0;
	for (i = 0; i < maxnum; i++) {
		if (accountnumber == account[i].accountNumber) {
			iFinded = 1;
			break;
		}
	}
	if (iFinded == 0) {
		i = -1;
	}
	return i;
}

void  displayAllAccountDetailRecords(const struct Account account[], int maxnum) {
	int i = -1;
	displayAccountDetailHeader();
	for (i = 0; i < maxnum; i++) {
		if (account[i].accountNumber > 0) {
			displayAccountDetailRecord(&account[i]);
			printf("\n");
		}
	}
	printf("\n");
	pauseExecution();
}

// Pause execution until user enters the enter key
void pauseExecution(void) {
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}