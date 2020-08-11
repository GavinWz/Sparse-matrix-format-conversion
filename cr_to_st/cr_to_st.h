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

clock_t cr_read(char* filename, cr_fmt* cr, int* n_row);

clock_t cr_to_st(cr_fmt cr, st_fmt* st, int n_row);

clock_t st_write(char* filename,st_fmt st);

clock_t cr_write(char* filename,cr_fmt cr);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);
 
void cr_to_st_run(char* ifilename, char* ofilename);
