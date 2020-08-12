#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*ST格式矩阵类型*/
typedef struct st{
    int *ist;       //行偏移数组
    int *jst;       //列偏移数组
    double *ast;    //非零元数组
    int n_val;      //非零元个数
} st_fmt;

/*HYB格式矩阵类型*/
typedef struct hyb{ 
    double** eData;   //HYB中ELL数据矩阵
    int** offset;     //HYB中ELL列偏移矩阵
    int max;          //用户定义ELL格式行中非零元个数最大值
    int* ist;         //HYB中st格式的行偏移数组
    int* jst;         //HYB中st格式的列偏移数组
    double* ast;      //HYB中st格式的非零元素数组
    int n_val;        //HYB中st格式的非零元素个数
} hyb_fmt;

clock_t hyb_read(char* filename, hyb_fmt *hyb, int* row);

clock_t hyb_to_st(hyb_fmt hyb, st_fmt *st, int n_row);

clock_t st_write(char* filename,st_fmt st);

clock_t hyb_write(char* filename, hyb_fmt hyb, int n_row);

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2);

void hyb_to_st_run(char* ifilename, char* ofilename);