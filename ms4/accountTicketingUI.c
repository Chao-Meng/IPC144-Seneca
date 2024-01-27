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
#include "accountTicketingUI.h" 
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}

void displayAccountDetailRecord(const struct Account* account)
{
	char Type[20] = { 0 };
	replaceType(account->accountType, Type);
	size_t i = 0;
	char password[10] = { 0 };
	for (i = 0; i < strlen(account->login.password); i++) {
		if (i % 2 == 1) {
			password[i] = '*';
		}
		else {
			password[i] = account->login.password[i];
		}
	}
	printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s", account->accountNumber, Type,
		account->person.fullName, account->person.yearBorn, account->person.familyIncome,
		account->person.homeCountry, account->login.userName, password);
}

void applicationStartup(struct AccountTicketingData* pAccTicData)
{
	for (;;) {
		int iMenuLoginRet = menuLogin(pAccTicData);
		if (iMenuLoginRet == -1) {
			break;
		} else if (iMenuLoginRet != -2) {
			menuAgent(pAccTicData, &pAccTicData->accounts[iMenuLoginRet]);
		}
	}
}

int menuLogin(struct AccountTicketingData* pAccTicData)
{
	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");
	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printf("----------------------------------------------\n\n");
	printf("Selection: ");
	int num = getIntFromRange(0,1);
	int accountnumber = 0;
	char password[100] = { 0 };
	char username[100] = { 0 };
	int i = -1;
	int flag = 0;
	char answer = 0;

	if (num == 0) {
		printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
		answer = getCharOption("yYnN");
		printf("\n");
		if (answer == 'y' || answer == 'Y') {
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
		}
		else {
			i = -2;
		}
	} else if (num == 1) {
		int j = 0;
		for (j = 2; j >-1; j--) {
			printf("\nEnter the account#: ");
			scanf("%d", &accountnumber);
			printf("User Login        : ");
			scanf("%s", username);
			printf("Password          : ");
			scanf("%s", password);

			for (i = 0; i < pAccTicData->ACCOUNT_MAX_SIZE; i++) {
				if (accountnumber == pAccTicData->accounts[i].accountNumber &&
					pAccTicData->accounts[i].accountType=='A' && 
					strcmp(username, pAccTicData->accounts[i].login.userName)==0 && 
					strcmp(password, pAccTicData->accounts[i].login.password)==0) {
					flag = 1;
					printf("\n");
					break;
				}
			}

			if (flag != 1) {
				i = -2;
			}
			else {
				break;
			}

			if (flag != 1 && num == 1) {
				printf("INVALID user login/password combination! [attempts remaining:%d]\n",j);
				if (j == 0) {
					printf("\nERROR:  Access Denied.\n\n");
					pauseExecution();
				}
				clearStandardInputBuffer();
			}
		}
	}

	return i;
}

void menuAgent(struct AccountTicketingData* pAccTickData, const struct Account* pAcc)
{
	for (;;) {
		char Type[20] = { 0 };
		replaceType(pAcc->accountType, Type);
		char arrTicketState[10];
		char strAc[10] = { 'A','C','T','I','V','E','\0' };
		char strCl[10] = { 'C','L','O','S','E','D','\0' };
		printf("%5s: %s (%05d)\n", Type, pAcc->person.fullName, pAcc->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("5) List new tickets\n");
		printf("6) List active tickets\n");
		printf("7) List closed tickets\n");
		printf("8) Add a new ticket\n");
		printf("9) Manage a ticket\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		int num = getIntFromRange(0, 9);
		int i = 0;
		int accountnumber = 0;
		int iEmptyIndex = -1;
		int iMaxAccNum = 0;
		
		switch (num) {
		case 0:
			printf("\nSaving session modifications...\n");
			int accNum = saveAccounts(pAccTickData->accounts, pAccTickData->ACCOUNT_MAX_SIZE);
			int tickNum = saveTickets(pAccTickData->tickets, pAccTickData->TICKET_MAX_SIZE);
			printf("   %d account(s) saved.\n", accNum);
			printf("   %d ticket(s) saved.\n", tickNum);
			printf("### LOGGED OUT ###\n\n");
			return;
		case 1:
			for (i = 0; i < pAccTickData->ACCOUNT_MAX_SIZE; i++) {
				if (iEmptyIndex == -1) {
					if (pAccTickData->accounts[i].accountNumber <= 0) {
						iEmptyIndex = i;
					}
				}
				if (iMaxAccNum < pAccTickData->accounts[i].accountNumber) {
					iMaxAccNum = pAccTickData->accounts[i].accountNumber;
				}
			}

			if (iEmptyIndex == -1) {
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
			}
			else {
				printf("\n");
				pAccTickData->accounts[iEmptyIndex].accountNumber = iMaxAccNum + 1;
				getAccount(&pAccTickData->accounts[iEmptyIndex]);
			}
			pauseExecution();
			break;
		case 2:
			printf("\nEnter the account#: ");
			scanf("%d", &accountnumber);
			printf("\n");
			int iFinded = findAccountIndexByAcctNum(accountnumber, pAccTickData->accounts,
				pAccTickData->ACCOUNT_MAX_SIZE, 0);

			if (iFinded != -1) {
				updateAccount(&pAccTickData->accounts[iFinded]);
			}
			else {
				printf("ERROR\n");
			}
			break;
		case 3:
			printf("\nEnter the account#: ");
			scanf("%d", &accountnumber);
			if (accountnumber == pAcc->accountNumber) {
				printf("\nERROR: You can't remove your own account!\n\n");
				clearStandardInputBuffer();
				pauseExecution();
				break;
			}
			else {
				int iFinded = findAccountIndexByAcctNum(accountnumber, pAccTickData->accounts,
					pAccTickData->ACCOUNT_MAX_SIZE, 0);
				if (iFinded != -1) {
					printf("\n");
					displayAccountDetailHeader();
					displayAccountDetailRecord(&pAccTickData->accounts[iFinded]);
					printf("\n");
					clearStandardInputBuffer();
					printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
					char option = getCharOption("yYnN");
					if (option == 'Y' || option == 'y') {						
						pAccTickData->accounts[iFinded].accountNumber = 0;
						pAccTickData->accounts[iFinded].accountType = 0;//remove all information about account
						strcpy(pAccTickData->accounts[iFinded].login.password, "");
						strcpy(pAccTickData->accounts[iFinded].login.userName, "");
						pAccTickData->accounts[iFinded].person.familyIncome = 0;
						strcpy(pAccTickData->accounts[iFinded].person.fullName, "");
						strcpy(pAccTickData->accounts[iFinded].person.homeCountry, "");
						pAccTickData->accounts[iFinded].person.yearBorn = 0;
						
						int iCount = 0;
						int k = 0;
						// remove ticket information associated with the account and count the number of ticket
						for (; k < pAccTickData->TICKET_MAX_SIZE; k++) {
							if (pAccTickData->tickets[k].accountNumber == accountnumber) {
								pAccTickData->tickets[k].ticketNumber = 0;
								pAccTickData->tickets[k].ticketState=0;
								iCount++;
							}
						}
						//display the number of tickets deleted
						printf("\n*** Account Removed! (%d ticket(s) removed) ***\n\n", iCount);
						pauseExecution();
					}
				}
				else {
					printf("ERROR: no proper index!");
				}
			}
			break;
		case 4:
			printf("\n");
			displayAllAccountDetailRecords(pAccTickData->accounts, pAccTickData->ACCOUNT_MAX_SIZE);
			break;
		case 5:
			printf("\n");
			displayTicketDetailHeader();
			int m = 0;

			for (m = 0; m < pAccTickData->TICKET_MAX_SIZE; m++)
			{
				if (pAccTickData->tickets[m].ticketState == 1) {
					strcpy(arrTicketState, strAc);
				}
				else {
					strcpy(arrTicketState, strCl);
				}
				if (pAccTickData->tickets[m].ticketState == 1 && pAccTickData->tickets[m].ticketCounter == 1) {
					printf("%06d %05d %-15s %5s %-25s %10d\n", pAccTickData->tickets[m].ticketNumber,
						pAccTickData->tickets[m].accountNumber, pAccTickData->tickets[m].messageType->displayName,
						arrTicketState, pAccTickData->tickets[m].subjectLine,
						pAccTickData->tickets[m].ticketCounter);
				}
			}

			printf("------ ----- --------------- ------ ------------------------------ --------\n");
			printf("\n");
			int choice = 0;
			int n = 0;
			printf("Enter the ticket number to view the messages or\n");
			printf("0 to return to previous menu: ");
			scanf("%d", &choice);

			for (n = 0; n < pAccTickData->TICKET_MAX_SIZE; n++) {
				if (choice == pAccTickData->tickets[n].ticketNumber) {
					printf("%d", pAccTickData->tickets[n].ticketCounter);
				}
				else {
					if (choice == 0);
					break;
				}
			}
			printf("\n");
			break;
		case 6:
			for (;;) {
				printf("\n");
				displayTicketDetailHeader();
				for (m = 0; m < pAccTickData->TICKET_MAX_SIZE; m++) {
					if (pAccTickData->tickets[m].ticketState == 1) {
						strcpy(arrTicketState, strAc);
					}
					else {
						strcpy(arrTicketState, strCl);
					}
					if (pAccTickData->tickets[m].ticketState == 1) {
						printf("%06d %05d %-15s %5s %-30s %5d\n", pAccTickData->tickets[m].ticketNumber,
							pAccTickData->tickets[m].accountNumber, pAccTickData->tickets[m].messageType[0].displayName,
							arrTicketState, pAccTickData->tickets[m].subjectLine, pAccTickData->tickets[m].ticketCounter);
					}
				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\n");
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &choice);

				if (choice > 0) {
					for (n = 0; n < pAccTickData->TICKET_MAX_SIZE; n++) {
						if (choice == pAccTickData->tickets[n].ticketNumber) {
							if (pAccTickData->tickets[n].ticketState == 1) {
								printf("\n================================================================================\n");
								printf("%06d (%6s) Re: %-25s", pAccTickData->tickets[n].ticketNumber, strAc, pAccTickData->tickets[n].subjectLine);
								printf("\n================================================================================\n");
								int ii = 0;
								for (ii = 0; ii < 20; ii++) {
									if (pAccTickData->tickets[n].messageType[ii].author_accountType == '\0') {
										break;
									}
									if (pAccTickData->tickets[n].messageType[ii].author_accountType == 'A') {
										printf("AGENT (%s):\n", pAccTickData->tickets[n].messageType[ii].displayName);
										printf("   %s\n\n", pAccTickData->tickets[n].messageType[ii].message);
									}
									else if (pAccTickData->tickets[n].messageType[ii].author_accountType == 'C') {
										printf("CUSTOMER (%s):\n", pAccTickData->tickets[n].messageType[ii].displayName);
										printf("   %s\n\n", pAccTickData->tickets[n].messageType[ii].message);
									}
								}
							}
							else {
								printf("\nERROR: Invalid ticket number.\n\n");
								clearStandardInputBuffer();
								pauseExecution();
							}
							break;
						}
					}
					clearStandardInputBuffer();
					pauseExecution();
				}
				else if (choice == 0) {
					printf("\n");
					break;
				}
			}			
			break;
		case 7:
			printf("\n");
			for (;;) {
				displayTicketDetailHeader();

				for (m = 0; m < pAccTickData->TICKET_MAX_SIZE; m++) {
					if (pAccTickData->tickets[m].ticketState == 1) {
						strcpy(arrTicketState, strAc);
					}
					else {
						strcpy(arrTicketState, strCl);
					}
					if (pAccTickData->tickets[m].ticketState == 0 && pAccTickData->tickets[m].ticketNumber != 0) {
						printf("%06d %05d %-15s %5s %-25s %10d\n", pAccTickData->tickets[m].ticketNumber,
							pAccTickData->tickets[m].accountNumber, pAccTickData->tickets[m].messageType->displayName,
							arrTicketState, pAccTickData->tickets[m].subjectLine,
							pAccTickData->tickets[m].ticketCounter);
					}
				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\n");
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &choice);

				if (choice > 0) {
					for (n = 0; n < pAccTickData->TICKET_MAX_SIZE; n++) {
						if (choice == pAccTickData->tickets[n].ticketNumber) {
							if (pAccTickData->tickets[n].ticketState == 0) {
								printf("\n================================================================================\n");
								printf("%06d (%6s) Re: %-s", pAccTickData->tickets[n].ticketNumber, arrTicketState, pAccTickData->tickets[n].subjectLine);
								printf("\n================================================================================\n");
								int ii = 0;
								for (ii = 0; ii < 20; ii++) {
									if (pAccTickData->tickets[n].messageType[ii].author_accountType == '\0') {
										break;
									}
									if (pAccTickData->tickets[n].messageType[ii].author_accountType == 'A') {
										printf("AGENT (%s):\n", pAccTickData->tickets[n].messageType[ii].displayName);
										printf("   %s\n\n", pAccTickData->tickets[n].messageType[ii].message);
									}
									else if (pAccTickData->tickets[n].messageType[ii].author_accountType == 'C') {
										printf("CUSTOMER (%s):\n", pAccTickData->tickets[n].messageType[ii].displayName);
										printf("   %s\n\n", pAccTickData->tickets[n].messageType[ii].message);
									}
								}
							}
							else {
								printf("\nERROR: Invalid ticket number.\n\n");
							}
							break;
						}
					}
					clearStandardInputBuffer();
					pauseExecution();
				}
				else {
					printf("\n");
					break;
				}
				
			}
			break;
		case 8:
			iEmptyIndex = -1;
			int iMaxTicketNum = 0;

			for (i = 0; i < pAccTickData->TICKET_MAX_SIZE; i++) {
				if (iEmptyIndex == -1) {
					if (pAccTickData->tickets[i].ticketNumber <= 0) {
						iEmptyIndex = i;
					}
				}
				if (iMaxTicketNum < pAccTickData->tickets[i].ticketNumber) {
					iMaxTicketNum = pAccTickData->tickets[i].ticketNumber;
				}
			}

			if (iEmptyIndex == -1) {
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
			}
			else {
				printf("\n");
				pAccTickData->tickets[iEmptyIndex].ticketState = 1;
				struct stTmp middleParam;
				middleParam.iEmptyIndex = iEmptyIndex;
				middleParam.iMaxTicketNum = iMaxTicketNum;
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
					}
					else {
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
							printf("\nNew Ticket (Ticket#:%06d)", pAccTickData->tickets[middleParam.iEmptyIndex].ticketNumber);
							printf("\n----------------------------------------\n");
							printf("Enter the ticket SUBJECT (30 chars. maximum): ");
							scanf("%[^\n]", pAccTickData->tickets[middleParam.iEmptyIndex].subjectLine);//input string with space
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
						}
					}
					break;
				}
			}
			printf("\n");
			clearStandardInputBuffer();
			pauseExecution();
			break;
		case 9:
			printf("\n");
			int iticketNum = 0;
			int iIndex = findTicketIndexByTicketNum(iticketNum, pAccTickData->tickets, pAccTickData->TICKET_MAX_SIZE, 0);

			if (iIndex != -1) {
				int iBreakFor = 0;
				int jj = 0;

				for (;;) {
					printf("\n----------------------------------------");
					printf("\nTicket %06d - Update Options", pAccTickData->tickets[iIndex].ticketNumber);
					printf("\n----------------------------------------");
					printf("\nStatus  : %s", pAccTickData->tickets[iIndex].ticketState == 1 ? "ACTIVE" : "CLOSED");
					printf("\nSubject : %s", pAccTickData->tickets[iIndex].subjectLine);
					printf("\nAcct#   : %d", pAccTickData->tickets[iIndex].accountNumber);
					printf("\nCustomer: %s",pAccTickData->tickets[iIndex].messageType[0].displayName);
					printf("\n----------------------------------------");
					printf("\n1) Add CUSTOMER message");
					printf("\n2) Add AGENT message");
					printf("\n3) Close ticket");
					printf("\n4) Re-activate ticket");
					printf("\n0) Done");
					printf("\nSelection: ");
					int numOption = getIntFromRange(0, 4);

					switch (numOption) {
					case 0:
						iBreakFor = 1;
						printf("\n");
						break;
					case 1:// add customer message
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						
						for (jj = 0; jj < 20; jj++) {
							if (pAccTickData->tickets[iIndex].messageType[jj].author_accountType == '\0') {
								break;
							}
						}
						pAccTickData->tickets[iIndex].messageType[jj].author_accountType = 'C';
						strcpy(pAccTickData->tickets[iIndex].messageType[jj].displayName, pAccTickData->tickets[iIndex].messageType[0].displayName);
						scanf("%[^\n]", pAccTickData->tickets[iIndex].messageType[jj].message);
						pAccTickData->tickets[iIndex].ticketCounter += 1;
						clearStandardInputBuffer();
						break;
					case 2://add agent message
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						for (jj = 0; jj < 20; jj++) {
							if (pAccTickData->tickets[iIndex].messageType[jj].author_accountType == '\0') {
								break;
							}
						}
						pAccTickData->tickets[iIndex].messageType[jj].author_accountType = 'A';
						strcpy(pAccTickData->tickets[iIndex].messageType[jj].displayName, pAcc->person.fullName);
						scanf("%[^\n]", pAccTickData->tickets[iIndex].messageType[jj].message);
						pAccTickData->tickets[iIndex].ticketCounter += 1;
						clearStandardInputBuffer();
						break;
					case 3:
						if (pAccTickData->tickets[iIndex].ticketState ==0) {
							printf("\nERROR: Ticket is already closed!\n");
						}
						else {
							printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
							char option = getCharOption("yYnN");
							if (option == 'Y' || option == 'y') {
								pAccTickData->tickets[iIndex].ticketState = 0;
								printf("\n*** Ticket closed! ***\n");
							}
						}
						break;
					case 4:
						if (pAccTickData->tickets[iIndex].ticketState == 1) {
							printf("\nERROR: Ticket is already active!\n");
						}
						else {
							printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
							char option = getCharOption("yYnN");
							if (option == 'Y' || option == 'y') {
								pAccTickData->tickets[iIndex].ticketState = 1;
								printf("\n*** Ticket re-activated! ***\n");
							}
						}
						break;
					default:
						break;
					}
					
					if (iBreakFor == 1) {
						break;
					}
				}
			}
			else {
				printf("ERROR: no proper index! ");
				break;
			}
		default:
			break;
		}
	}
}

int findAccountIndexByAcctNum(int accountnumber, const struct Account* account, int maxnum, int number)
{
	if (number != 0) {
		printf("Enter the account#:");
		scanf("%d", &accountnumber);
	}
	int i = 0;
	int iFinded = 0;
	for (i = 0; i < maxnum; i++) {
		if (accountnumber == account[i].accountNumber) {
			iFinded = 1;
			break;
		}
	}
	if (iFinded == 0) {
		i = -1;
	}
	return i;
}

void  displayAllAccountDetailRecords(const struct Account* account, int maxnum)
{
	int i = -1;
	displayAccountDetailHeader();
	for (i = 0; i < maxnum; i++) {
		if (account[i].accountNumber > 0) {
			displayAccountDetailRecord(&account[i]);
			printf("\n");
		}
	}
	printf("\n");
	pauseExecution();
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}