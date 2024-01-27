#pragma once
/*
	==================================================
	Assignment:  1
	Milestone:   2
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/

// structures
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
};