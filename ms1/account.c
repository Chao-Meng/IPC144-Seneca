/*
	==================================================
	Assignment:  2
	Milestone:   1
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h" 

void getAccount(struct Account* account)
{
	printf("New Account Data: (Account#:%5d)\n", account->accountNumber);
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
	pauseExecution();
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
	int i = 0;
	for (i = 0; i < 30; i++) {
		if (person->homeCountry[i] > 0) {
			person->homeCountry[i] = person->homeCountry[i] - 32;///////不是整个数组全部变，只对输入的字母变
		}
	}
	//person->homeCountry= person->homeCountry -32;
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
		printf("Enter the password (must be 8 chars in length): ");
		getCString(login->password, 8, 8);
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
			if (ispunct(login->password[j])) {
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
			printf("          symbol character: !@#$^&*\n");
			
		}
	}

	printf("\n");
}

void updateAccount(struct Account* account) {
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

void updatePerson(struct Person* people){
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
				//_strupr(people->homeCountry);
				int i = 0;
				for (i = 0; i < 30; i++) {
					if (people->homeCountry[i] > 0) {
						people->homeCountry[i] = people->homeCountry[i] - 32;
					}
				}
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

void updateUserLogin(struct UserLogin* login) {
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