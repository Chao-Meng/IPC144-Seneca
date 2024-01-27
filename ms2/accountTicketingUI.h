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
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
#define _CRT_SECURE_NO_WARNINGS
#include "account.h"
#include "ticket.h"
struct AccountTicketingData {
	struct Account* accounts;//array of accounts
	const int ACCOUNT_MAX_SIZE;//maximum elements for account array
	struct Ticket* tickets;//array of tickets
	const int TICKET_MAX_SIZE;//maximum elements for ticket array
};

void displayAccountDetailHeader(void);
void applicationStartup(struct AccountTicketingData* pAccTicData);// maxnum is the max number of elements in account[];
int menuLogin(struct AccountTicketingData* pAccTicData);//the returns represent the array index of the account...
void menuAgent(struct AccountTicketingData* pAccTickData, const struct Account* pAcc);
//int findAccountIndexByAcctNum(int accountnumber, const struct Account account[], int maxnum, int number);
int findAccountIndexByAcctNum(int accountnumber, const struct Account* account, int maxnum, int number);
void displayAllAccountDetailRecords(const struct Account* account, int maxnum);
void pauseExecution(void);

#endif
