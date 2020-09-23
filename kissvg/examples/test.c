#include <stdio.h>

void test(double x[3])
{
	printf("%f\t%f\t%f\n", x[0], x[1], x[2]);
}

int main()
{
	double x[3];
	x[0] = 1.0;
	x[1] = 2.0;
	x[2] = 3.0;

	puts("Hi");
	test(x);
	puts("Hello");
	return 0;
}

