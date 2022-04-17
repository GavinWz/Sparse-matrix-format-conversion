#include<stdio.h>
#include<omp.h>
#include<time.h>

int main(){
    double b = omp_get_wtime();
    clock_t begin = clock();
    double e = omp_get_wtime();
    printf("%lf", e-b);
}