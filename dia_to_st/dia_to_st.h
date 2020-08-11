#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct dia{
    int ldiag;  //对角线长度
    int ndiag;  //对角线个数
    int* idiag; //对角线编号数组
    double* val_dia; //DIA所有元素值组成的一维数组
    int n_val;  //非零元个数
} dia_fmt;

typedef struct st{
    int *ist;   //行偏移数组
    int *jst;   //列偏移数组
    double *ast; //非零元数组
    int n_val;  //非零元个数
} st_fmt;

clock_t dia_read(char* filename, dia_fmt* dia);

clock_t dia_to_st(dia_fmt dia, st_fmt* st);

clock_t dia_write(char* filename, dia_fmt dia);

clock_t st_write(char* filename,st_fmt st);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);

void dia_to_st_run(char* ifilename, char* ofilename);