#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
    int n_col;
} cc_fmt;

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col);

clock_t st_cc_sort(st_fmt* st);

clock_t st_write(char* filename,st_fmt st);

clock_t cc_write(char* filename,cc_fmt cc);

clock_t st_to_cc(st_fmt st, cc_fmt* cc, int n_row);

void st_to_cc_run(char* ifilename, char* ofilename);
