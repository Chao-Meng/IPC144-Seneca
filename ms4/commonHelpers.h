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
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
#define _CRT_SECURE_NO_WARNINGS

int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
double getDouble(void);
double getPositiveDouble(void);
int getIntFromRange(int min_bound, int max_bound);
char getCharOption(const char singlechar[]);
void getCString(char* cstring, int min_bound, int max_bound);
void replaceType(char accountType, char* Type);
/*
Chao Meng 2021.11.23
Purpose   : convert lowercase letters to uppercase via ASCII code.
Parameters: letter--Input, lowercase letters. Output uppercase letters.
			iMaxNum--the maximum elements of lower array.
Returns   : void.
*/
void upper(char letter[], int iMaxNum);

#endif