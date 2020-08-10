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

clock_t cr_read(char* filename, cr_fmt* cr, int* n_row);

clock_t cr_to_st(cr_fmt cr, st_fmt* st, int n_row);

clock_t st_write(char* filename,st_fmt st);

clock_t cr_write(char* filename,cr_fmt cr);

void cr_to_st_run(char* ifilename, char* ofilename);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);
