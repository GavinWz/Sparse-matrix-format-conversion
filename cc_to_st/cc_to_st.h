#include<stdio.h>
#include<stdlib.h>

typedef struct st{
    int *ist;
    int *jst;
    double *ast;
    int n_val;
} st_fmt;

typedef struct cc{
    int *rcc;
    int *ccc;
    double *vcc;
    int n_row;
} cc_fmt;

void cc_read(char* filename, cc_fmt* cc, int* n_row);

void cc_to_st(cc_fmt cc, st_fmt* st, int n_row);

void st_write(char* filename,st_fmt st);

void cc_write(char* filename,cc_fmt cc);

void cc_to_st_run(char* ifilename, char* ofilename);