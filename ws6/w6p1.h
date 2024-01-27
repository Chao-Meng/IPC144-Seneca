/*
	==================================================
	Workshop #6 (Part-1):
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZAA
*/
#define NUM_GRAMS 64
#define MAX_PRODUCT 3
// ----------------------------------------------------------------------------
// structures
struct CatFoodInfo {
	int sku;
	double price;
	int calories;
	double weight;
};



// ----------------------------------------------------------------------------
// function prototypes

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
void displayCatFoodHeader();
// 6. Display a formatted record of cat food data

void displayCatFoodData(const int sku, const double* price, const int calories, const double* weight);
// 7. Logic entry point
void start();
