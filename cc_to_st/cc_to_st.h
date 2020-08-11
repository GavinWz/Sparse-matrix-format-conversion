#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct st{
    int *ist;   //行偏移数组
    int *jst;   //列偏移数组
    double *ast; //非零元数组
    int n_val;  //非零元个数
} st_fmt;

typedef struct cc{
    int *rcc;   //行偏移数组
    int *ccc;   //列偏移数组
    double *vcc; //非零元数组
    int n_col;  //原矩阵列数
} cc_fmt;

clock_t cc_read(char* ifilename, cc_fmt* cc);

clock_t cc_to_st(cc_fmt cc, st_fmt* st);

clock_t st_write(char* filename,st_fmt st);

clock_t cc_write(char* filename,cc_fmt cc);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);

void cc_to_st_run(char* ifilename, char* ofilename);