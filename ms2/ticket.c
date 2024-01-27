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

#define _CRT_SECURE_NO_WARNINGS
#include "ticket.h"
#include <stdio.h>
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

/*
void getTicket(struct stTmp middleParam, struct AccountTicketingData* pAccTickData)
{
	//scanf("%d", &ticket->accountNumber);
	for (;;) {
		printf("Enter the account#: ");
		int iAccNum = 0;
		scanf("%d", &iAccNum);
		int iIndex = findAccountIndexByAcctNum(iAccNum, pAccTickData->accounts, pAccTickData->ACCOUNT_MAX_SIZE, 0);
		if (iIndex == -1) {
			printf("\nERROR: can't find the account, please input it again!\n");
			continue;
		}
		if (pAccTickData->accounts[iIndex].accountType == 'A') {
			printf("\nERROR: Agent accounts can't have tickets!\n");
			//pauseExecution();
		}
		else {
			//char strC[20] = { 'C','U','S','T','O','M','E','R', '\0' };
			//char strA[20] = { 'A','G','E','N','T','\0' };
			//char Type[20] = { 0 };
			//if (pAccTickData->accounts->accountType == 'A') {
			//	strcpy(Type, strA);
			//}
			//if (pAccTickData->accounts->accountType == 'C') {
			//	strcpy(Type, strC);
			//}

			char Type[20] = { 0 };
			replaceType(pAccTickData->accounts[iIndex].accountType, Type);
			printf("\n");
			displayAccountDetailHeader();
			printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s", pAccTickData->accounts[iIndex].accountNumber, Type,
				pAccTickData->accounts[iIndex].person.fullName, pAccTickData->accounts[iIndex].person.yearBorn, pAccTickData->accounts[iIndex].person.familyIncome,
				pAccTickData->accounts[iIndex].person.homeCountry, pAccTickData->accounts[iIndex].login.userName, pAccTickData->accounts[iIndex].login.password);
			printf("\n\nAdd a new ticket for this customer? ([Y]es|[N]o): ");

			clearStandardInputBuffer();
			char option = getCharOption("yYnN");

			if (option == 'Y' || option == 'y') {
				pAccTickData->tickets[middleParam.iEmptyIndex].ticketNumber = middleParam.iMaxTicketNum + 1;
				pAccTickData->tickets[middleParam.iEmptyIndex].accountNumber = iAccNum;
				printf("\nNew Ticket(Ticket#:%06d)", pAccTickData->tickets[middleParam.iEmptyIndex].ticketNumber);
				printf("\n----------------------------------------\n");
				printf("Enter the ticket SUBJECT (30 chars. maximum): ");
				scanf("%[^\n]", pAccTickData->tickets[middleParam.iEmptyIndex].subjectLine);////input string with space
				clearStandardInputBuffer();
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");

				int i = 0;
				int iEmptyIndex = -1;
				for (i = 0; i < 20; i++) {
					if (iEmptyIndex == -1) {
						if (pAccTickData->tickets[middleParam.iEmptyIndex].messageType[i].author_accountType != '\0') {
							iEmptyIndex = i;
							break;
						}
					}
				}

				if (iEmptyIndex > -1) {
					pAccTickData->tickets[middleParam.iEmptyIndex].messageType[iEmptyIndex].author_accountType = 'C';
					strcpy(pAccTickData->tickets[middleParam.iEmptyIndex].messageType[iEmptyIndex].displayName,
						pAccTickData->accounts[iIndex].person.fullName);
					scanf("%[^\n]", pAccTickData->tickets[middleParam.iEmptyIndex].messageType[iEmptyIndex].message);
				}

				printf("\n*** New ticket created! ***\n");
				//pauseExecution();
			}
		}
		break;
	}
}
*/
int findTicketIndexByTicketNum(int ticketnumber, const struct Ticket ticket[], int maxnum, int number) {
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
