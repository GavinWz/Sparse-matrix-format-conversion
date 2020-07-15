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

void cr_read(char* filename, cr_fmt* cr);

void cr_to_st(cr_fmt cr, st_fmt* st, int n_row);

void st_write(char* filename,st_fmt st);

void cr_write(char* filename,cr_fmt cr);
