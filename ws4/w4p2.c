/*
	==================================================
	Workshop #4 (Part-2):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#define _crt_secure_no_warnings
#include<stdio.h>
#define min_items 1
#define max_items 10
int main() {
	const double min_income = 500.00;
	const double max_income = 400000.00;
	const double min_cost = 100.00;
	const int min_prior = 1;
	const int max_prior = 3;
	const int max_menu = 2;
	const int min_menu=0;
	double income, sum = 0;
	int num_items;
	double cost[max_items];
	int priority[max_items];
	char finance[max_items];
	int menu = 0;
	int keepgoing = 1;
	double sum_priority[3] = { 0 };
	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n\n");

	do {
		printf("Enter your monthly NET income: $");
		scanf("%lf", &income);
		if (income < min_income) {
			printf("ERROR: You must have a consistent monthly income of at least $500.00\n\n");
		}
		if (income > max_income) {
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n\n");
		}
	} while (income<min_income || income>max_income);
	do {
		printf("\nHow many wish list items do you want to forecast?: ");
		scanf("%d", &num_items);
		if (num_items<min_items || num_items>max_items) {
			printf("ERROR: List is restricted to between 1 and 10 items.\n");
		}
	} while (num_items<min_items || num_items>max_items);
	int i;
	for (i = 0; i < num_items; i++) {
		printf("\nItem-%d Details:\n", i + 1);

		do {
			printf("   Item cost: $");
			scanf("%lf", &cost[i]);
			
			if (cost[i] < min_cost) {
				printf("      ERROR: Cost must be at least $100.00\n");
			}

		} while (cost[i] < min_cost);
		sum += cost[i];//sum=sum+cost[i]
		do {
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &priority[i]);



			if (priority[i] < min_prior || priority[i] > max_prior) {
				printf("      ERROR: Value must be between 1 and 3\n");
			}

		} while (priority[i] < min_prior || priority[i] > max_prior);
		

			sum_priority[priority[i]-1] += cost[i];
				

		do {
			printf("   Does this item have financing options? [y/n]: ");
			scanf("%*c%c", &finance[i]);
			if (finance[i] != 'y' && finance[i] != 'n') {
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
			}
		} while (finance[i] != 'y' && finance[i] != 'n');
	}
	printf("\nItem Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	for (i = 0; i < num_items; i++) {
		printf("%3d%7d%9c%15.2lf\n", i + 1, priority[i], finance[i], cost[i]);
		
	};
	printf("---- -------- -------- -----------\n");
	printf("%23c%11.2lf\n\n", '$', sum);
			
	do {

		printf("How do you want to forecast your wish list?\n");
		printf(" 1. All items (no filter)\n");
		printf(" 2. By priority\n");
		printf(" 0. Quit/Exit\n");
		printf("Selection: ");
		scanf("%d", &menu);

		if (menu > max_menu || menu < min_menu) {
			printf("\nERROR: Invalid menu selection.\n\n");
		}
	switch (menu) {


		case 1:
			printf("\n====================================================\n");
			printf("Filter:   All items\n");
			//printf("Amount:   $54530.90\n");
			printf("Amount:   %c%.2lf\n",'$',sum);
		
			int year = (int)sum / (int)income / 12;
			double month =( sum / (income * 12)-year) * 12;

			printf("Forecast: %d years, %.0lf months\n", year, month);
			//printf("Forecast: 0 years, 9 months\n");
			printf("NOTE: Financing options are available on some items.\n");
			printf("      You can likely reduce the estimated months.\n");
			printf("====================================================\n\n");
			break;
		case 0:
			keepgoing = 0;
			break;
		case 2:
			
			printf("\nWhat priority do you want to filter by? [1-3]: ");
			scanf("%d", &priority[i]);
		
			printf("\n====================================================\n");
			printf("Filter:   by priority (%d)\n",priority[i]);
			
				
			int date_year = (int)sum_priority[priority[i] - 1] / (int)income / 12;
			double date_month = 0;
			
			if ((int) sum_priority[priority[i] - 1] % (int) income == 0) {
			 date_month = sum_priority[priority[i] - 1] / income - date_year * 12;
			}
			else 
				 date_month = (int)sum_priority[priority[i] - 1] /(int)income - date_year * 12+1;
					
			//date_month = ceil(date_month);
			printf("Amount:   $%1.2lf\n",sum_priority[priority[i]-1]);
				
			printf("Forecast: %d years, %.lf months\n",date_year, date_month);
			if (priority[i] != 2) {
				printf("NOTE: Financing options are available on some items.\n");
				printf("      You can likely reduce the estimated months.\n");
			}

			
			printf("====================================================\n\n");
			break;
			
		
		}
		
				
		}while(keepgoing!=0);
	
	
	printf("\nBest of luck in all your future endeavours!\n");


	return 0;
}

