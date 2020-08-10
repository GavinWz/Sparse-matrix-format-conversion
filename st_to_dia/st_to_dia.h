# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include<string.h>
# include <time.h>

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

clock_t dpre_usconv_st2dia(int m, int n, st_fmt st, dia_fmt* dia);

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col);

clock_t st_write(char* filename,st_fmt st);

clock_t dia_write(char* filename, dia_fmt dia);

void st_to_dia_run(char* readFile, char* writeFile);