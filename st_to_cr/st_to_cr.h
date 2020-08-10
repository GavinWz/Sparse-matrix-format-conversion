#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct st{
    int *ist;
    int *jst;
    double *ast;
    int n_val;
} st_fmt;

typedef struct cr{
    int *rcr;
    int *ccr;
    double *vcr;
    int n_row;
} cr_fmt;

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col);

clock_t st_write(char* filename,st_fmt st);

void st_cr_sort(st_fmt* st, int left, int right);

clock_t cr_write(char* filename,cr_fmt cr);

clock_t st_to_cr(st_fmt st, cr_fmt* cr, int n_row);

void st_to_cr_run(char* ifilename, char* ofilename);
