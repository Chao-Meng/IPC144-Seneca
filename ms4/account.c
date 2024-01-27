/*
	==================================================
	Assignment:  2
	Milestone:   4
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 8
#define ACCOUNT_BUFF_SIZE 100

#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "accountTicketingUI.h"
#include "commonHelpers.h" 

void getAccount(struct Account* account)
{
	printf("New Account Data (Account#:%5d)\n", account->accountNumber);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");
	printf("\n");
	getPerson(&account->person);

	if (account->accountType == 'A') {
		getUserLogin(&account->login);
	}
	else {
	}

	printf("*** New account added! ***\n\n");
}

void getPerson(struct Person* person)
{
	printf("Person Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter the person's full name (30 chars max): ");
	getCString(person->fullName, 0, 30);
	int curYear = currentYear();
	printf("Enter birth year (current age must be between 18 and 110): ");
	person->yearBorn = getIntFromRange(curYear - 110, curYear - 18);
	printf("Enter the household Income: $");
	person->familyIncome = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(person->homeCountry, 0, 30);
	upper(person->homeCountry, 30);
	printf("\n");
}

void getUserLogin(struct UserLogin* login)
{
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	for (;;) {
		printf("Enter user login (10 chars max): ");
		getCString(login->userName, 0, 10);
		size_t i = 0;
		int iCorrect = 1;
		for (; i < strlen(login->userName); i++) {
			if (login->userName[i] == ' ') {
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				iCorrect = 0;
				break;
			}
		}
		if (iCorrect == 1) {
			break;
		}
	}

	for (;;) {
		printf("Enter the password (must be %d chars in length): ",SIZE);
		getCString(login->password, SIZE, SIZE);
		size_t j = 0;
		int ix = 0;
		int ux = 0;
		int lx = 0;
		int px = 0;
		for (; j < strlen(login->password); j++) {
			if (isdigit(login->password[j])) {
				ix++;
			}
			if (isupper(login->password[j])) {
				ux++;
			}
			if (islower(login->password[j])) {
				lx++;
			}
			if (ispunct(login->password[j]) && (login->password[j] == '!' ||
				login->password[j] == '@' || login->password[j] == '#' ||
				login->password[j] == '$' || login->password[j] == '%' ||
				login->password[j] == '^' || login->password[j] == '&' ||
				login->password[j] == '*')) {
				px++;
			}
		}
		if (ix == 2 && ux == 2 && lx == 2 && px == 2) {
			break;
		}
		else {
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}
	}

	printf("\n");
}

void updateAccount(struct Account* account)
{
	for (;;) {
		printf("Update Account: %d (%-9s)\n", account->accountNumber, account->person.fullName);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		printf("2) Person\n");
		printf("3) Login\n");
		printf("0) Done\n");
		printf("Selection: ");
		
		for (;;) {
			int iSelect = -1;
			scanf("%d", &iSelect);
			switch (iSelect) {
			case 0:
				printf("\n");
				return;
			case 1:
				clearStandardInputBuffer();
				printf("\nEnter the account type (A=Agent | C=Customer): ");
				char newType = getCharOption("AC");
				if (newType == 'A') {
					account->accountType = 'A';
					printf("\nAgent type accounts require a user login.  Please enter this information now:\n\n");
					getUserLogin(&account->login);
				} else if (newType == 'C') {
					strcpy(account->login.userName, "");
					strcpy(account->login.password, "");
					account->accountType = 'C';
					printf("\n");
				}
				break;
			case 2:
				printf("\n");
				updatePerson(&account->person);
				break;
			case 3:
				if (account->accountType == 'C') {
					printf("\nERROR:  Customer account types don't have user logins!\n\n");
					break;
				}
				printf("\n");
				updateUserLogin(&account->login);
				printf("\n");
				break;
			default:
				printf("ERROR: Value must be between 0 and 3 inclusive: ");
				break;
			}
			if (iSelect >= 0 && iSelect <=3) {
				break;
			}
		}
	}
}

void updatePerson(struct Person* people)
{
	for (;;) {
		printf("Person Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Full name (current value: %s)\n", people->fullName);
		printf("2) Household Income (current value: $%.2lf)\n", people->familyIncome);
		printf("3) Country (current value: %s)\n", people->homeCountry);
		printf("0) Done\n");
		printf("Selection: ");
		
		for (;;) {
			int iSelect = -1;
			scanf("%d", &iSelect);
			printf("\n");
			switch (iSelect) {
			case 0:
				return;
			case 1:
				clearStandardInputBuffer();
				printf("Enter the person's full name (30 chars max): ");
				getCString(people->fullName, 0, 30);
				printf("\n");
				break;
			case 2:
				printf("Enter the household Income: $");
				people->familyIncome = getPositiveDouble();
				printf("\n");
				break;
			case 3:
				clearStandardInputBuffer();
				printf("Enter the country (30 chars max.): ");
				getCString(people->homeCountry, 0, 30);
				upper(people->homeCountry, 30);
				printf("\n");
				break;
			default:
				printf("ERROR: Value must be between 0 and 3 inclusive: ");
				break;
			}
			if (iSelect >= 0 && iSelect <= 3) {
				break;
			}
		}
	}
}

void updateUserLogin(struct UserLogin* login)
{
	for (;;) {
		printf("User Login: %s - Update Options\n", login->userName);
		printf("----------------------------------------\n");
		printf("1) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		for (;;) {
			int iSelect = -1;
			scanf("%d", &iSelect);
			switch (iSelect) {
			case 0:
				return;
			case 1:
				clearStandardInputBuffer();
				printf("\nEnter the password (must be 8 chars in length): ");
				getCString(login->password, 8, 8);
				printf("\n");
				break;
			default:
				printf("ERROR: Value must be between 0 and 1 inclusive:");
				break;
			}
			if (iSelect >= 0 && iSelect <= 1) {
				break;
			}
		}
	}
}

//to assgin the value between each two separators to the corresponding variable.
void assignToAccount(struct Account accounts[], int iAccIndex, char tmp[],
	int iTmpNum, int iSeparatorCount)
{
	switch (iSeparatorCount) {
	case 1:
		accounts[iAccIndex].accountNumber = atoi(tmp);
		break;
	case 2:
		if (strlen(tmp) == 1) {
			accounts[iAccIndex].accountType = tmp[0];
		}
		break;
	case 3:
		strcpy(accounts[iAccIndex].person.fullName, tmp);
		break;
	case 4:
		accounts[iAccIndex].person.yearBorn = atoi(tmp);
		break;
	case 5:
		accounts[iAccIndex].person.familyIncome = atof(tmp);
		break;
	case 6:
		strcpy(accounts[iAccIndex].person.homeCountry, tmp);
		break;
	case 7:
		strcpy(accounts[iAccIndex].login.userName, tmp);
		break;
	case 8:
		strcpy(accounts[iAccIndex].login.password, tmp);
		break;
	default:
		printf("ERROR: field overflow!");
		break;
	}
}

//get the values from accounts.txt file and assign each of these values to the corresponding variable.
int loadAccounts(struct Account accounts[], int accSIZE)
{
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "r");
	int iLineCount = 0;

	if (fp != NULL) {
		char buf[ACCOUNT_BUFF_SIZE] = { 0 };
		while (fgets(buf, ACCOUNT_BUFF_SIZE, fp) != NULL) {
			char tmp[30] = { 0 };
			int i = 0;
			int iSeparatorCount = 0;
			for (i = 0; i < ACCOUNT_BUFF_SIZE; i++) {
				if (buf[i] == '\0') {
					if (strcmp(tmp, "") != 0) {
						assignToAccount(accounts, iLineCount, tmp, 30, iSeparatorCount + 1);
					}
					break;
				}
				if (buf[i] == '~') {
					iSeparatorCount++;
					if (strcmp(tmp, "") != 0) {
						assignToAccount(accounts, iLineCount, tmp, 30, iSeparatorCount);
						int j = 0;
						for (j = 0; j < 30; j++) {
							tmp[j] = '\0';
						}
					}
					else {
						break;
					}
				}
				else {
					int k = 0;
					for (k = 0; k < 30; k++) {
						if (tmp[k] == '\0') {
							break;
						}
					}
					if (buf[i] != '\n') {
						tmp[k] = buf[i];
					}
				}
			}
			iLineCount++;
			if (iLineCount == accSIZE) {
				break;
			}
		}
		fclose(fp);
	}
	else {
		printf("ERROR: open file error!");
		return -1;
	}
	return iLineCount;
}

int saveAccounts(struct Account accounts[], int accSize)
{
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "w+");
	int accountsCount = 0;

	if (fp != NULL) {
		char writeBuff[ACCOUNT_BUFF_SIZE] = { 0 }; //Temporary storage of accounts information
		int i = 0;
		for (i = 0; i < accSize; i++) {
			if (accounts[i].accountNumber <= 0 && isspace(accounts[i].accountType) != 0 &&
				strcmp(accounts[i].person.fullName, "") == 0 && accounts[i].person.yearBorn <= 0) {
				accountsCount = i;
				break;
			}
			if (strcmp(accounts[i].login.userName, "") != 0 && strcmp(accounts[i].login.password, "") != 0) {
				sprintf(writeBuff, "%d~%c~%s~%d~%.2lf~%s~%s~%s\n", accounts[i].accountNumber, accounts[i].accountType,
					accounts[i].person.fullName, accounts[i].person.yearBorn, accounts[i].person.familyIncome, 
					accounts[i].person.homeCountry, accounts[i].login.userName, accounts[i].login.password);
			}
			else {
				sprintf(writeBuff, "%d~%c~%s~%d~%.2lf~%s\n", accounts[i].accountNumber, accounts[i].accountType,
					accounts[i].person.fullName, accounts[i].person.yearBorn, accounts[i].person.familyIncome,
					accounts[i].person.homeCountry);
			}
			fputs(writeBuff, fp);
			if (i == accSize - 1) {
				accountsCount = i + 1;
			}
		}
		fclose(fp);
	}
	return accountsCount;
}
