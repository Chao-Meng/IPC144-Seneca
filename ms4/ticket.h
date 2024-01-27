//#pragma once
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
	int ticketState;
	char subjectLine[31];
	int ticketCounter;
	struct Message messageType[21];
};

struct stTmp {
	int iEmptyIndex;
	int iMaxTicketNum;
};

void displayTicketDetailHeader(void);
int findTicketIndexByTicketNum(int ticketnumber, const struct Ticket ticket[], int maxnum, int number);

/*
Chao Meng 2021.11.27
Purpose   : Assign the value between each two separators to the corresponding variable.
Parameters: tickets--input.
            iTicketIndex--input, the maximum elements of ticket array.
			tmp--input, temporary storage the value of each field of each line in the ticket.txt file.
			iTmpNum--input,the maximum elements of tem array.
			iSeparatorCount--input,the index of separator'|' for locating.
Returns   : void.
*/
void assignToTicket(struct Ticket tickets[], int iTicketIndex, char tmp[], int iTmpNum, int iSeparatorCount);
/*
Chao Meng 2021.11.27
Purpose   : get the values from tickets.txt file and assign each of these values to the corresponding variable.
Parameters: tickets--input, original data.
			ticketSize--input, the maximum elements of tickets array.
Returns   : int. Return the number of tickets via reading the tickets.txt file.
*/
int loadTickets(struct Ticket tickets[], int tickSize);

/*
Chao Meng 2021.11.29
Purpose   : save the elements of tickets into tickets.txt file.
Parameters: tickets--input, original data
		    tickSize--input int, the maximum elements of tickets array.
Returns   : int. Return the number of tickets. 
*/
int saveTickets(struct Ticket tickets[], int tickSize);

#endif