#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct st{
    int *ist;
    int *jst;
    double *ast;
    int n_val;
} st_fmt;

typedef struct hyb{ 
    double** eData;
    int** offset;
    int max;
    int* ist;
    int* jst;
    double* ast;
    int n_val;
} hyb_fmt;

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col, int* max);

clock_t st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col);

clock_t hyb_write(char* filename, hyb_fmt hyb, int n_row);

clock_t st_write(char* filename, st_fmt st);

void st_to_hyb_run(char* ifilename, char* ofilename);
