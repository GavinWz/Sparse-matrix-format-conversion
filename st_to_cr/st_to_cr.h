#include<stdio.h>
#include<stdlib.h>

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

void st_read(char* filename, st_fmt* st, int* n_row, int* n_col);

void st_write(char* filename,st_fmt st);

void cr_write(char* filename,cr_fmt cr);

void st_to_cr(st_fmt st, cr_fmt* cr, int n_row);
