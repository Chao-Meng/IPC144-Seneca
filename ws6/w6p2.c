/*
	==================================================
	Workshop #6 (Part-2):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/

#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include<stdio.h>

// User-Defined Libraries
#include"w6p2.h"//使用该文件下的函数

// ----------------------------------------------------------------------------
// PART-1

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* num) {
	int val;
	do {
		scanf("%d", &val);
		if (val <= 0) {
			printf("ERROR: Enter a positive value: ");
		}
	} while (val <= 0);
	if (num != NULL)
		*num = val;
	return val;
}

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* num) {
	double val;
	do {
		scanf("%lf", &val);
		if (val <= 0) {
			printf("ERROR: Enter a positive value: ");
		}
	} while (val <= 0);
	if (num != NULL)
		*num = val;
	return val;
}

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int num_product) {
	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n");
	printf("Enter the details for %d dry food bags of product data for analysis.\n", num_product);
	printf("NOTE: A 'serving' is %dg\n", NUM_GRAMS);
}

// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int sequence_num) {
	struct CatFoodInfo food = { 0 };
	printf("\nCat Food Product #%d\n", sequence_num);
	printf("--------------------\n");
	printf("SKU           : ");
	getIntPositive(&food.sku);
	printf("PRICE         : $");
	getDoublePositive(&food.price);
	printf("WEIGHT (LBS)  : ");
	getDoublePositive(&food.weight);
	printf("CALORIES/SERV.: ");
	getIntPositive(&food.calories);
	return food;
}

// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Display a formatted record of cat food data
void displayCatFoodData(const int sku, const double* price, const int calories, const double* weight) {
	printf("%07d %10.2lf %10.1lf %8d\n", sku, *price, *weight, calories);
}


// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg (divide by 2.20462)
double  convertLbsKg(const double* pDlbs, double* pDKg) {//part 2
	if (pDlbs == NULL) {
		return -1;
	}	
	double dKg = *pDlbs / CON_factor;
	if (pDKg != NULL) {
		*pDKg = dKg;	
	}
	return dKg;
}
//9. convert lbs: g (call convertKG, then * 1000)
int convertLbsG(const double* pDlbs, int* pIg){
	if (pDlbs == NULL) {
		return -1;
	}
	int Ig = (int)(convertLbsKg(pDlbs, NULL) * 1000);//
	if (pIg != NULL) {
		*pIg = Ig;
	}
	return Ig;
}

// 10. convert lbs: kg and g
void convertLbs(const double* pDlbs, double* pDKg, int* pIg) {//g改成大写
	if (pDlbs == NULL) {
		//return -1;
		return;
	}
	double dKg= convertLbsKg(pDlbs, NULL);
	if (pDKg != NULL) {
		*pDKg = dKg;
	}
	
	//*pDKg = convertLbsK(pDlbs, pDKg);
	//*pIg = convertLbsG(pDlbs,NULL);
	int Ig= convertLbsG(pDlbs, NULL);
	if (pIg != NULL) {
		*pIg = Ig;
	}
	
}
//11. calculate: servings based on gPerServ
double calculateServings(const int* pIGramServ, const int* pITotalGram, double* pDNumServ) {
	if (pIGramServ == NULL|| pITotalGram==NULL) {
		return -1;
	}

	double DNumServ = *pITotalGram /(double) *pIGramServ;
	if (pDNumServ != NULL) {
		*pDNumServ = DNumServ;
	}
	//*pDNumServ = *pITotalGram / *pIGramServ;
	
	return DNumServ;
}
// 12. calculate: cost per serving
double calculateCostPerServing(const double* pDPrice, const double* pDTotalNumServ, double* pDCostServ) {
	if(pDPrice == NULL || pDTotalNumServ == NULL) {
		return -1;
	}
	double DCostServ= *pDPrice / *pDTotalNumServ;
	//*pDCostServ=*pDPrice / *pDTotalNumServ;
	if (pDCostServ != NULL) {
		*pDCostServ = DCostServ;
	}
	return DCostServ;
}

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* pDPrice, const double* pDTotalNumCal, double* pDCostCal) {
	if (pDPrice == NULL || pDTotalNumCal == NULL) {
		return -1;
	}
	double DCostCal= *pDPrice / *pDTotalNumCal;
	//*pDCostCal = *pDPrice / *pDTotalNumCal;
	if (pDCostCal != NULL) {
		*pDCostCal = DCostCal;
	}
	return DCostCal;
}

// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo CatFoodProduct) {
	struct ReportData AnalysisReport;
	AnalysisReport.sku=CatFoodProduct.sku;
	AnalysisReport.price=CatFoodProduct.price;
	AnalysisReport.calories=CatFoodProduct.calories;
	AnalysisReport.weight_lbs=CatFoodProduct.weight;
	AnalysisReport.weight_kg = convertLbsKg(&CatFoodProduct.weight,NULL);
	AnalysisReport.weight_g = convertLbsG(&CatFoodProduct.weight, NULL);
	int pIGramServ=NUM_GRAMS;
	//int pITotalGram = MAX_PRODUCT * AnalysisReport.weight_g;
	int pITotalGram = AnalysisReport.weight_g;
	AnalysisReport.total_servings = calculateServings(&pIGramServ,&pITotalGram, NULL);
	AnalysisReport.cost_per_serving = calculateCostPerServing(&CatFoodProduct.price,&AnalysisReport.total_servings,NULL);
	double pDTotalNumCal = CatFoodProduct.calories * AnalysisReport.total_servings;
	AnalysisReport.cost_per_calorie = calculateCostPerCal(&CatFoodProduct.price,&pDTotalNumCal,NULL);
	return AnalysisReport;
}

// 15. Display the formatted table header for the analysis results
void displayReportHeader(void)
{
	printf("Analysis Report (Note: Serving = %dg\n", NUM_GRAMS);//???
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData report[MAX_PRODUCT], const int cheapestoption) {
	
	
	int i = 0;
	int jj = -1;
	double cost_per_calorie = 1000.00;
	for (; i < MAX_PRODUCT; i++) {
		if (report[i].cost_per_calorie < cost_per_calorie) {
			cost_per_calorie = report[i].cost_per_calorie;			
			jj = i;
		}
	}
	if (jj == -1) {
		return;
	}
	int j = 0;
	char star[4] = { '*','*','*','\0' };
	for (; j < MAX_PRODUCT; j++) {
		if (j == jj) {
			if (cheapestoption != 0) {
				printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf %s\n", report[j].sku, report[j].price, report[j].weight_lbs, report[j].weight_kg,
					report[j].weight_g, report[j].calories, report[j].total_servings, report[j].cost_per_serving, report[j].cost_per_calorie,star);
			}else {
				printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf\n", report[j].sku, report[j].price, report[j].weight_lbs, report[j].weight_kg,
					report[j].weight_g, report[j].calories, report[j].total_servings, report[j].cost_per_serving, report[j].cost_per_calorie);
			}
		} else {
			printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf\n", report[j].sku, report[j].price, report[j].weight_lbs, report[j].weight_kg,
				report[j].weight_g, report[j].calories, report[j].total_servings, report[j].cost_per_serving, report[j].cost_per_calorie);
		}
	}
}

// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo cheapestproduct) {
	printf("Final Analysis\n");
	printf("--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d Price: $%.2lf", cheapestproduct.sku, cheapestproduct.price);
	printf("\n\nHappy shopping!");
}

// ----------------------------------------------------------------------------

// 7. Logic entry point
void start(void)
{
	struct CatFoodInfo cats[MAX_PRODUCT] = { {0} };
	openingMessage(MAX_PRODUCT);
	int i;
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		cats[i] = getCatFoodInfo(i + 1);

	}
	printf("\n");
	displayCatFoodHeader();
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		displayCatFoodData(cats[i].sku, &cats[i].price, cats[i].calories, &cats[i].weight);
	}
	printf("\n");
	displayReportHeader();
	int j = 0;
	struct ReportData report1[MAX_PRODUCT];
	for (j = 0; j < MAX_PRODUCT; j++) {

		report1[j] = calculateReportData(cats[j]);

	}
	const struct ReportData report2[MAX_PRODUCT] = { report1[0],report1[1],report1[2] };
	displayReportData(report2, 1);
	printf("\n");
	int a = 0;
	int b = 0;
	double cost_per_calorie = 1000.00;
	/*int aaa = sizeof(struct ReportData);
	printf("\n%d", aaa);*/

	for (; a < MAX_PRODUCT; a++) {
		if (report2[a].cost_per_calorie < cost_per_calorie) {
			cost_per_calorie = report2[a].cost_per_calorie;
			b = a;
		}
	}
	int c = 0;
	for (; c < MAX_PRODUCT; c++) {
		if (c == b) {
			const struct CatFoodInfo catss = cats[c];
			displayFinalAnalysis(catss);
		}	
	}
}
