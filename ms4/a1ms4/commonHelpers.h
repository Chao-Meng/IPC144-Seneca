#pragma once
/*
	==================================================
	Assignment:  1
	Milestone:   3
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
double getDouble(void);
double getPositiveDouble(void);
int getIntFromRange(int min_bound, int max_bound);
char getCharOption(const char singlechar[]);
void getCString(char* cstring, int min_bound, int max_bound);

#endif