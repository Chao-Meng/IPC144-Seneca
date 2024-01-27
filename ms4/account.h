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
//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#define _CRT_SECURE_NO_WARNINGS

// Header file contents goes here...
struct Person {
	char fullName[31];
	int yearBorn;
	double familyIncome;
	char homeCountry[31];
};

struct UserLogin {
	char userName[11];
	char password[9];
};

struct Account {
    int accountNumber;
    char accountType;
	struct Person person;
	struct UserLogin login;
};

void getAccount(struct Account* account);
void getPerson(struct Person* person);
void getUserLogin(struct UserLogin* userlogin);
void updateAccount(struct Account* account);
void updatePerson(struct Person* people);
void updateUserLogin(struct UserLogin* login);

/*
Chao Meng 2021.11.27
Purpose   : Assign the value between each two separators to the corresponding variable.
Parameters: accounts--input, original data.
			iAccIndex--the maximum elements of accounts array.
			tem--array,store the value of each element of each line in the account.txt file.
			iTempNum--the maximum elements of tem array.
			iSeparatorCount--tthe index of separator '~' for locating.
Returns   : void.
*/
void assignToAccount(struct Account accounts[], int iAccIndex, char tmp[], int iTmpNum, int iSeparatorCount);

/*
Chao Meng 2021.11.27
Purpose   : get the values from accounts.txt file and assign each of these values to the corresponding variable.
Parameters: Account--input, original data.
			accSize--input, the maximum elements of accounts array.
Returns   : int. Return the number of accounts via reading the accounts.txt file.
*/
int loadAccounts(struct Account accounts[], int accSIZE);

/*
Chao Meng 2021.11.29
Purpose   : save the elements of tickets into accounts.txt file.
Parameters: accounts--input, original data.
			accSize--input, the maximum elements of accounts array.
Returns   : int. Return the number of accounts.
*/
int saveAccounts(struct Account accounts[], int accSize);

#endif// !ACCOUNT_H_