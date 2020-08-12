#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct st{
    int *ist;   //行偏移数组
    int *jst;   //列偏移数组
    double *ast; //非零元数组
    int n_val;  //非零元个数
} st_fmt;

typedef struct cr{
    int *rcr;   //行偏移数组
    int *ccr;   //列偏移数组
    double *vcr;    //非零元数组
    int n_row;  //原矩阵行数
} cr_fmt;

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col);

clock_t st_write(char* filename,st_fmt st);

void st_cr_sort(st_fmt* st, int left, int right);

clock_t cr_write(char* filename,cr_fmt cr);

clock_t st_to_cr(st_fmt st, cr_fmt* cr, int n_row);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);

void st_to_cr_run(char* ifilename, char* ofilename);
