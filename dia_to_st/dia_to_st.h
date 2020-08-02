#include<stdio.h>
#include<stdlib.h>

typedef struct dia{
    int ldiag;  //对角线长度
    int ndiag;  //对角线个数
    int* idiag; //对角线编号数组
    double* val_dia; //DIA所有元素值组成的一维数组
    int n_val;  //非零元个数
} dia_fmt;

typedef struct st{
    int *ist;
    int *jst;
    double *ast;
    int n_val;
} st_fmt;

void dia_read(char* filename, dia_fmt* dia);

void dia_to_st(dia_fmt dia, st_fmt* st);

void dia_write(char* filename, dia_fmt dia);

void st_write(char* filename,st_fmt st);

void dia_to_st_run();