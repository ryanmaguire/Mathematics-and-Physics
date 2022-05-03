#include <stdlib.h>
#include <stdio.h>

long **WhereGreater(double *data, long dim, double threshold)
{
    long i;
    long arr_size = 0;
    long *dummy = (long *)malloc(sizeof(long) * dim);
    for (i=0; i<dim; ++i) {
        if (data[i] > threshold){
            dummy[arr_size] = i;
            arr_size += 1;
        }
    }
    long *arr = (long *)malloc(sizeof(long) * arr_size);
    for (i=0; i<arr_size; ++i){
        arr[i] = dummy[i];
    }
    free(dummy);
	long **where = (long **)malloc(sizeof(long) * 2);
	where[0] = arr;
	where[1] = &arr_size;
    return where;
}

int main(){
	long i;
	long n = 24;
	double threshold = 18.0;

	double *ptr = (double *)malloc(sizeof(double) * n);

	for (i=0; i<n; ++i){
		ptr[i] = (double)i;
	}

	long **where = WhereGreater(ptr, n, threshold);
	long *where_arr =  where[0];
	long where_dim  = *where[1];
	for (i=0; i<where_dim; ++i){
		printf("%ld\t%ld\t%ld\n", i, where_dim, where_arr[i]);
	}
	free(where_arr);
	free(where);
	free(ptr);
	return 0;
}
