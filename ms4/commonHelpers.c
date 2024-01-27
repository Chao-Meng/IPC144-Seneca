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
//#define _CRT_SECURE_NO_DEPRECATE  
//#define _CRT_NONSTDC_NO_DEPRECATE

#include "commonHelpers.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int getInteger(void)
{
	int value = 0;
	char newLine = 'x';
	for (;;) {
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n') {
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else {
			break;
		}
	}
	return value;
}

int getPositiveInteger(void)
{
	int value = 0;
	do {
		value = getInteger();
		if (value <= 0)
			printf("ERROR: Value must be a positive integer greater than zero: ");
	} while (value <= 0);
	return value;
}

double getDouble(void)
{
	double value = 0.00;
	char newLine = 'x';
	for (;;) {
		scanf("%lf%c", &value, &newLine);
		if (newLine == '\n') {
			return value;
		}
		else {
			scanf("%lf%c", &value, &newLine);
			if (newLine == '\n') {
				return value;
			}
			else {
				clearStandardInputBuffer();
				printf("ERROR: Value must be a double floating-point number: ");
			}
		}
	}
}

double getPositiveDouble(void)
{
	double value;
	do {
		value = getDouble();
		if (value <= 0)
			printf("ERROR: Value must be a positive double floating-point number: ");
	} while (value <= 0);
	return value;
}

int getIntFromRange(int min_bound, int max_bound)
{
	int value = 0;
	for (;;) {
		value = getInteger();
		if (value < min_bound || value > max_bound) {
			printf("ERROR: Value must be between %d and %d inclusive: ", min_bound, max_bound);
		}
		else {
			break;
		}
	}
	return value;
}

char getCharOption(const char singlechar[])
{
	char inputValue = 0;
	char charEol = 0;
	for (;;) {
		scanf("%c%c", &inputValue, &charEol);
		if (charEol == '\n') {
			size_t len = strlen(singlechar);
			int flag = 0;
			size_t i = 0;
			for (i = 0; i < len; i++) {
				if (inputValue == singlechar[i]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				return inputValue;
			}
			else {
				printf("ERROR: Character must be one of [%s]: ", singlechar);
			}
		}
		else {
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", singlechar);
		}
	}
}

void getCString(char* cstring, int min_bound, int max_bound)
{
	char str[50] = { 0 };
	for (;;) {
		scanf("%[^\n]", str);
		size_t len = strlen(str);
		if (min_bound == max_bound) {
			if (len != min_bound) {
				printf("ERROR: String length must be exactly %d chars: ", max_bound);
			}
			else {
				strcpy(cstring, str);
				break;
			}
			clearStandardInputBuffer();
		}
		else {
			if (len > (size_t)max_bound) {
				printf("ERROR: String length must be no more than %d chars: ", max_bound);
			}
			else if (len < (size_t)min_bound) {
				printf("ERROR: String length must be between %d and %d chars: ", min_bound, max_bound);
			}
			else {
				strcpy(cstring, str);
				break;
			}
			clearStandardInputBuffer();
		}
	}
	clearStandardInputBuffer();
}

//replace a single character with the entire word.
void replaceType(char accountType, char* Type)
{
	char strC[20] = { 'C','U','S','T','O','M','E','R', '\0' };
	char strA[20] = { 'A','G','E','N','T','\0' };
	if (accountType == 'A') {
		strcpy(Type, strA);
	}
	if (accountType == 'C') {
		strcpy(Type, strC);
	}
}

//convert lowercase letters to uppercase via ASCII code.
void upper(char letter[], int iMaxNum)
{
	int i = 0;
	for (i = 0; i < iMaxNum; i++) {
		if (letter[i] == '\0') {
			break;
		}
		if (letter[i] >= 'a' && letter[i] <= 'z') {
			letter[i] -= 32;
		}
	}
}
