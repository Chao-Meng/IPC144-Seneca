//#pragma once
/*
	==================================================
	Assignment:  2
	Milestone:   2
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
#endif// !ACCOUNT_H_