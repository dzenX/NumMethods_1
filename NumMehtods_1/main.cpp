#define low_eps 1e-15 //the max precision
#define a -8.8
#define b 1.9

#include <iostream>
#include <math.h>

//struct to save additional info about calculations of func sh(x)
typedef struct Info {
	double last_mem;
	int num;
	Info() = default;
};

double sh(const double &eps, const double &x, const double &prev, Info* table = NULL, const int &num = 2) {
	double res = 0;
	if (abs(prev) > eps) {
		res = prev + sh(eps, x, (prev*x*x) / ((2 * num - 1)*(2 * num - 2)), table, num + 1);
		return res;
	}
	else 
		if (table != NULL){
			table->last_mem = prev;
			table->num = num - 1;
		}
	return res;
}

void first_table(int& n) {
	double x = (a + b) / 2; //point where sh(x) is calculated
	double eps = 1e-2; //start precision
	double sh_x = 0; //var with value of sh(x)
	Info * table = (Info*)malloc(sizeof(Info));

	printf("First table\n");
	printf("| %-16s | %3s | %-22s | %-23s |\n", "EPS", "N", "ACCURACY", "REST");

	while (eps > low_eps) {
		sh_x = sh(eps, x, x, table);
		
		//for next table
		if (eps == 1.0000000000000002e-08) //in debug such a number is where 1e-8 must be
			n = table->num;

		printf("| ");
		printf("%1.14f | ", eps);
		printf("%3.d | ", table->num);
		printf("%5.20f | ", abs(sh_x - sinh(x))); //I've tested printf("%.70f"), and still no difference in last row
		printf("%5.20f | ", table->last_mem);

		//shows default value and value calculated by my func
		//printf("%.10f | ", sinh(x));
		//printf("%.10f", sh(eps, x, x));

		printf("\n");
		eps *= 1e-2; //step of eps
	}
}

void second_table(const int& num) {
	double h = (b - a) / 10;
	double eps = 1e-8;
	double x = a;
	Info * table = (Info*)malloc(sizeof(Info));
	//table
	double sh_x = sh(eps, x, x, table);
	printf("Second table\n");
	printf("| %-10s | %-22s | %-23s |\n", "X(i)", "ACCURACY", "REST");
	printf("| %+3.7f | ", x);
	printf("%5.20f | ", abs(sh_x - sinh(x)));
	printf("%+5.20f |\n", table->last_mem);
	for (int i = 1; i < 10; i++) {
		x = x + h;
		sh_x = sh(eps, x, x, table);
		printf("| %+.7f | ", x);
		printf("%5.20f | ", abs(sh_x - sinh(x)));
		printf("%+5.20f |\n", table->last_mem);
	}
}

int main() {
	//use of func just to calc value with given precision
	/*
	double sh_x = sh(0.01, 2, 2);
	printf("%.10f\n", sh_x);
	*/

	//use of func to calc value with given accuracy and additional info located in table
	/*
	Info * table = (Info*)malloc(sizeof(Info));
	double sh_x_inf = sh(0.01, 2, 2, table);
	printf("%f, %d\n", table->last_mem, table->num);
	*/

	//first table
	int sec_table_num = 0;
	first_table(sec_table_num);
	printf("\n\n");
	second_table(sec_table_num);
	system("pause");
	return 0;
}