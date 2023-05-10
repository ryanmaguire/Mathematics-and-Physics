#include <stdio.h>
#include <math.h>

typedef double (*function)(double);

static double Newton(double x, function f, function f_prime, double EPS)
{
	double dx;
	int i = 0;
	dx = (*f)(x)/(*f_prime)(x);
	x -= dx;
	while(fabs(dx) > EPS){
	        dx = (*f)(x)/(*f_prime)(x);
        	x -= dx;
		++i;
	}
	return x;
}

static double x_square(double x){return x*x - 2.0;}
static double d_x_square(double x){return 2.0*x;}
static double log_minus_1(double x){return log(x) - 1.0;}
static double d_log_minus_1(double x){return 1.0/x;}
static double golden_ratio(double x){return x*x - x - 1.0;}
static double d_golden_ratio(double x){return 2.0*x - 1.0;}
static double x_12_minus_2(double x){return pow(x, 12.0) - 2.0;}
static double d_x_12_minus_2(double x){return 12.0*pow(x, 11.0);}

int main()
{
	double x, root;
	const double EPS = 1.0E-15;

	x = 2.0;
	root = Newton(x, x_square, d_x_square, EPS);
	printf("The Square Root of Two: %0.16f\n", root);
	printf("Exact:                  1.414213562373095048801688724\n\n");

	x = 3.0;
	root = Newton(x, sin, cos, EPS);
	printf("The Value of Pi: %0.16f\n", root);
	printf("Exact:           3.14159265358979323846\n\n");

	x = 3.0;
	root = Newton(x, &log_minus_1, &d_log_minus_1, EPS);
	printf("Euler's Number (e): %0.16f\n", root);
	printf("Exact:              2.71828182845904523536028\n\n");

	x = 2.0;
	root = Newton(x, &golden_ratio, &d_golden_ratio, EPS);
	printf("The Golden Ratio: %0.16f\n", root);
	printf("Exact:            1.618033988749894848204\n\n");

	x = 1.0;
	root = Newton(x, &x_12_minus_2, &d_x_12_minus_2, EPS);
	printf("The Music Number is: %0.16g\n", root);
	printf("Exact:               1.059463094359295264561825\n\n");
}
