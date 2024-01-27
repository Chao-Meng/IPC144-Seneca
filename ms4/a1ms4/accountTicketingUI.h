#pragma once
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
//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_TICKETINGUI_H_
#define CCOUNT_TICKETINGUI_H_
void displayAccountDetailHeader(void);
void applicationStartup(struct Account account[],int maxnum);// maxnum is the max number of elements in account[];
int menuLogin(const struct Account account[], int maxnum);//the returns represent the array index of the account...
void menuAgent(struct Account account[], int maxnum, const struct Account* acc);
int findAccountIndexByAcctNum(int accountnumber, const struct Account account[], int maxnum, int number);
void displayAllAccountDetailRecords(const struct Account account[], int maxnum);
void pauseExecution(void);
#endif
