#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOB

#ifdef BOB
float Q_rsqrt( float number )
{
	const float x2 = number * 0.5F;
	const float threehalfs = 1.5F;

	union {
		float f;
		uint32_t i;
	} conv  = { .f = number };
	conv.i  = 0x5f3759df - ( conv.i >> 1 );
	conv.f  *= threehalfs - ( x2 * conv.f * conv.f );
	// conv.f  *= threehalfs - ( x2 * conv.f * conv.f );
	return conv.f;
}
#else

//	The original Quake code and original comments.
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
#endif

int main(void)
{
	unsigned long n;
	unsigned long N = 1e6;
	float dx = 100.0F / N;
	float x = dx;
	float *y0 = malloc(sizeof(*y0) * N);
	float *y1 = malloc(sizeof(*y1) * N);
	float max, temp;

	clock_t t1, t2;
	t1 = clock();
	for (n=0; n<N; ++n)
	{
		y0[n] = Q_rsqrt(x);
		x += dx;
	}
	t2 = clock();
	printf("%f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	x = dx;
	t1 = clock();
    for (n=0; n<N; ++n)
    {
        y1[n] = 1.0F / sqrtf(x);
        x += dx;
    }
    t2 = clock();
	printf("%f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	max = 0.0F;
	for (n=0; n<N; ++n)
	{
		temp = fabsf(y0[n] - y1[n])/y1[n];
		if (max < temp)
			max = temp;
	}
	printf("%f\n", max);
	return 0;
}
