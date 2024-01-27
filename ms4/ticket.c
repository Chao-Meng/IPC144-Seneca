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
#define TICKET_BUFF_SIZE 1250
#include "ticket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accountTicketingUI.h" 
#include "account.h"
#include "commonHelpers.h"

void displayTicketDetailHeader(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

//Find the index corresponding to the ticketnumber
int findTicketIndexByTicketNum(int ticketnumber, const struct Ticket ticket[], int maxnum, int number)
{
	if (number == 0) {
		printf("Enter ticket number: ");
		scanf("%d", &ticketnumber);
	}
	int i = 0;
	int iFinded = 0;
	for (i = 0; i < maxnum; i++) {
		if (ticketnumber == ticket[i].ticketNumber) {
			iFinded = 1;
			break;
		}
	}
	if (iFinded == 0) {
		i = -1;
	}
	return i;
}

//assign the value in tickets.txt file between each two separators'|' to the corresponding variable
void assignToTicket(struct Ticket tickets[], int iTicketIndex, char tmp[], int iTmpNum, int iSeparatorCount)
{
    int iMessageTypeIndex = -1;
    if (iSeparatorCount >= 6 && iSeparatorCount <= 8) {
        iMessageTypeIndex = 0;
    }
    else if (iSeparatorCount > 8) {
        iMessageTypeIndex = (iSeparatorCount - 6) / 3;
        iSeparatorCount -= 3 * iMessageTypeIndex;
    }

    switch (iSeparatorCount) {
    case 1:
        tickets[iTicketIndex].ticketNumber = atoi(tmp);
        break;
    case 2:
        tickets[iTicketIndex].accountNumber = atoi(tmp);
        break;
    case 3:
        if (strlen(tmp) == 1) {
            tickets[iTicketIndex].ticketState = atoi(tmp);
        }
        break;
    case 4:
        strcpy(tickets[iTicketIndex].subjectLine, tmp);
        break;
    case 5:
        tickets[iTicketIndex].ticketCounter = atoi(tmp);
        break;
    case 6:
        if (strlen(tmp) == 1 && iMessageTypeIndex > -1) {
            tickets[iTicketIndex].messageType[iMessageTypeIndex].author_accountType = tmp[0];
        }
        break;
    case 7:
        if (iMessageTypeIndex > -1) {
            strcpy(tickets[iTicketIndex].messageType[iMessageTypeIndex].displayName, tmp);
        }
        break;
    case 8:
        if (iMessageTypeIndex > -1) {
            strcpy(tickets[iTicketIndex].messageType[iMessageTypeIndex].message, tmp);
        }
        break;
    default:
        printf("ERROR: field overflow!");
        break;
    }
}

//read the ticket information from tickets.txt,return the number of tickets
int loadTickets(struct Ticket tickets[], int tickSize)
{
    FILE* fp = NULL;
    fp = fopen("tickets.txt", "r");
    int iLineCount = 0;
    if (fp != NULL) {
        char buf[TICKET_BUFF_SIZE] = { 0 };
        while (fgets(buf, TICKET_BUFF_SIZE, fp) != NULL) {
            char tmp[200] = { 0 };
            int i = 0;
            int iSeparatorCount = 0;
            for (i = 0; i < TICKET_BUFF_SIZE; i++) {
                if (buf[i] == '\0') {
                    if (strcmp(tmp, "") != 0) {
                        assignToTicket(tickets, iLineCount, tmp, 200, iSeparatorCount + 1);
                    }
                    break;
                }
                if (buf[i] == '|') {
                    iSeparatorCount++;
                    if (strcmp(tmp, "") != 0) {
                        assignToTicket(tickets, iLineCount, tmp, 200, iSeparatorCount);
                        int j = 0;
                        for (j = 0; j < 200; j++) {
                            tmp[j] = '\0';
                        }
                    }
                    else {
                        break;
                    }
                }
                else {
                    int k = 0;
                    for (k = 0; k < 200; k++) {
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
            if (iLineCount == tickSize) {
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

int saveTickets(struct Ticket tickets[], int tickSize)
{
    FILE* fp = NULL;
	fp = fopen("tickets.txt", "w+");
	int ticketsCount = 0;

	if (fp != NULL) {
		int i = 0;
		for (; i < tickSize; i++) {
			if (tickets[i].ticketNumber <= 0 && tickets[i].accountNumber <= 0 &&
				strcmp(tickets[i].subjectLine, "") == 0 && tickets[i].ticketCounter <= 0) {
				break;
			}
            if (tickets[i].ticketNumber <= 0) {
                continue;
            }
			char writeBuff[TICKET_BUFF_SIZE] = { 0 };//Temporary storage of tickets information
			sprintf(writeBuff, "%d|%d|%d|%s|%d|", tickets[i].ticketNumber, tickets[i].accountNumber,
				tickets[i].ticketState, tickets[i].subjectLine, tickets[i].ticketCounter);
			int j = 0;

			for (; j < 21; j++) {
				if (tickets[i].messageType[j].author_accountType == '\0' && 
					strcmp(tickets[i].messageType[j].displayName, "") == 0 &&
					strcmp(tickets[i].messageType[j].message, "") == 0) {
					break;
				}
				char singleMessType[200] = {0};
				sprintf(singleMessType, "%c|%s|%s|", tickets[i].messageType[j].author_accountType,
					tickets[i].messageType[j].displayName, tickets[i].messageType[j].message);
				strcat(writeBuff, singleMessType);//Concatenate several parts of the string
			}
			strcat(writeBuff, "\n");//Add a newline single at the end of line
			fputs(writeBuff, fp);
			ticketsCount += 1;
		}
		fclose(fp);
	}
	return ticketsCount;
}
