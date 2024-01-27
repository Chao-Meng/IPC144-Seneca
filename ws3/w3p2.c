/*
	==================================================
	Workshop #3 (Part-2):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define _CRT_SECURE_NO_WARNINGS
#define LOGIC_DAYS 3
#define MIN_YEAR 2010
#define MAX_YEAR 2021
#define MIN_rating 0.0
#define MAX_rating 5.0
#define LOG_DAYS 3
#define N_LOG_DAYS 10
#define MAX_LOG_DAYS 28

#include <stdio.h>

int main() {
	const int JAN = 1;
	const int DEC = 12;
	//const char* strMonth = "";//Case-by-Case
	printf("General Well-being Log\n");
	printf("======================\n");
	int year = 0;
	int month = 0;
	int day;
	int valid = 0;
	
	double morning_rating = 0.0;
	double morning_total_rating = 0.0;
	double evening_rating = 0.0;
	double evening_total_rating = 0.0;
	char* strMonth[] = { "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };

	do {
		valid = 1;
		printf("Set the year and month for the well-being log (YYYY MM): ");
		scanf("%d %d", &year, &month);
		if (year <MIN_YEAR || year >MAX_YEAR) {
			printf("   ERROR: The year must be between 2010 and 2021 inclusive\n");
			valid = 0;
		}
		if (month < JAN || month > DEC) {
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
			valid = 0;
		}
	} while (valid == 0);

	printf("\n*** Log date set! ***\n");

		/*switch (month)//Case-by-Case
	{
	case 1:
		strMonth = "JAN";
		break;
	case 2:
		strMonth = "FEB";
		break;
	case 3:
		strMonth = "MAR";
		break;
	case 4:
		strMonth = "APR";
		break;
	case 5:

		strMonth = "MAY";
		break;
	case 6:
		strMonth = "JUN";
		break;
	case 7:
		strMonth = "JUL";
		break;
	case 8:
		strMonth = "AUG";
		break;
	case 9:
		strMonth = "SEP";
		break;
	case 10:
		strMonth = "OCT";
		break;
	case 11:
		strMonth = "NOV";
		break;
	case 12:
		strMonth = "DEC";
		break;
	default:
		strMonth = "JAN";
	}*/


 	for(day=1; day <= LOG_DAYS; ++day) {
		if (day >= N_LOG_DAYS && day<=MAX_LOG_DAYS ) {
			printf("\n%d-%s-%d\n", year, strMonth[month- 1], day);
		} else {
			printf("\n%d-%s-0%d\n", year, strMonth[month- 1], day);
		
		}
		do{
			valid = 1;
			printf("   Morning rating (0.0-5.0): ");
			scanf("%lf", &morning_rating);

			if (morning_rating < MIN_rating || morning_rating > MAX_rating) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
				valid = 0;
			}

			
		} while (valid == 0);
		morning_total_rating += morning_rating;
		do {
			valid = 1;
			printf("   Evening rating (0.0-5.0): ");
			scanf("%lf", &evening_rating);

			if (evening_rating < MIN_rating || evening_rating > MAX_rating) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
				valid = 0;
			}

			
		} while (valid == 0);
		evening_total_rating += evening_rating;
	}

	printf("\nSummary\n");
	printf("=======\n");
	printf("Morning total rating: %.3lf\n", morning_total_rating);
	printf("Evening total rating: %.3lf\n", evening_total_rating);
	printf("----------------------------\n");
	double overall_total_rating = morning_total_rating + evening_total_rating;
	printf("Overall total rating: %.3lf\n\n", overall_total_rating);
	printf("Average morning rating:  %.1lf\n", (double)(morning_total_rating / LOG_DAYS));
	printf("Average evening rating:  %.1lf\n", (double)(evening_total_rating / LOG_DAYS));
	printf("----------------------------\n");
	printf("Average overall rating:  %.1lf\n\n", (double)(overall_total_rating / 2 / LOG_DAYS));
	return 0;
}