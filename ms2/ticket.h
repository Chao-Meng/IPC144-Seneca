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
#ifndef TICKET_H_
#define TICKET_H_
#define _CRT_SECURE_NO_WARNINGS
#include "accountTicketingUI.h"
struct Message {
	char author_accountType;
	char displayName[31];
	char message[151];
};

struct Ticket {
	int ticketNumber;
	int accountNumber;
	int ticketState;//=0/1
	char subjectLine[31];
	int ticketCounter;
	struct Message messageType[21];
};

struct stTmp {
	int iEmptyIndex;
	int iMaxTicketNum;
};

void displayTicketDetailHeader(void);
//void getTicket(struct stTmp middleParam, struct AccountTicketingData* pAccTickData);//add 11.20
int findTicketIndexByTicketNum(int ticketnumber, const struct Ticket ticket[], int maxnum, int number);
#endif