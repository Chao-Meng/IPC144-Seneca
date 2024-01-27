/*
	==================================================
	Workshop #6 (Part-2):
	==================================================
	Name   :Chao Meng 
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/

// ----------------------------------------------------------------------------
// defines/macros
#define NUM_GRAMS 64
#define MAX_PRODUCT 3
#define CON_factor 2.20462//part 2 

// ----------------------------------------------------------------------------
// structures
struct CatFoodInfo {
	int sku;
	double price;
	int calories;
	double weight;
};
struct ReportData {//part 2
	int sku;
	double price;
	int calories;
	double weight_lbs;
	double weight_kg;
	int weight_g;
	double total_servings;
	double cost_per_serving;
	double cost_per_calorie;
};

// ----------------------------------------------------------------------------
// function prototypes

// PART-1

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* num);//可以用num 或者直接删掉，此处不用定义变量

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* num);

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int num_product);

// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int sequence_num);//定义function

// 5. Display the formatted table header
void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data
void displayCatFoodData(const int sku, const double* price, const int calories, const double* weight);

// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg
double convertLbsKg(const double* pDlbs, double* pDkg);
// 9. convert lbs: g
int convertLbsG(const double* pDlbs, int* pIg);

// 10. convert lbs: kg / g
void convertLbs(const double* pDlbs, double* pDKg, int* pIg);

// 11. calculate: servings based on gPerServ
double calculateServings(const int* pIGramServ, const int* pITotalGram, double* pDNumServ);

// 12. calculate: cost per serving
double calculateCostPerServing(const double* pDPrice, const double* pDTotalNumServ, double* pDCostServ);

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* pDPrice, const double* pDTotalNumCal, double* pDCostCal);

// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo CatFoodProduct);////

// 15. Display the formatted table header for the analysis results
void displayReportHeader(void);//老师给的

// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData report[MAX_PRODUCT], const int cheapestoption);

// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo cheapestproduct);

// ----------------------------------------------------------------------------

// 7. Logic entry point 
void start();

