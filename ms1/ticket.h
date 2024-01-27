#pragma once
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
#ifndef TICKET_H_
#define TICKET_H_
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
	int tickerCounter;
	struct Message messageType[21];
};

#endif