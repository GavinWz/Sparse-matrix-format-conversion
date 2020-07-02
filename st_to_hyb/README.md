# 稀疏矩阵ST格式转换为HYB格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd st_to_hyb

make

./st_to_hyb.exe (Linux为./st_to_hyb)
```
## 目标

将ST格式存储的稀疏矩阵转换为HYB格式存储

例： 

    1 0 0 0 	
    0 2 8 0 
    5 0 3 9 
    0 6 0 4
    
测试上述矩阵的ST格式转换为HYB格式，结果见output.txt

注：

    ELL列偏移数组中，值-1表示此行此列的元素值为0

## 主要文件

* read.txt: 存储ST格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* st_to_hyb.c: 功能函数的实现
* st_to_hyb_test.c: 测试

## 数据结构

```c
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
```

## 函数及参数含义
1. st_read
```c
int st_read(char* filename,double **ast,int **ist, int **jst)
```
功能：

    从文件中读取st格式稀疏矩阵，将结果保存在三个数组中

参数说明：

char* filename: 保存st格式稀疏矩阵的文件的文件名
double* ast: 非零元数组  
int* ist: 行偏移数组  
int* jst: 列偏移数组  


2. st_to_hyb
```c
void st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col)
```
功能：

    将ST格式矩阵转换为HYB格式，将结果保存在HYB结构体中

参数说明：
    st_fmt st:      将要转换的ST类型矩阵
    hyb_fmt* hyb:   保存结果的HYB类型矩阵
    int n_row:      原二维矩阵的行数    
    int n_col:      原二维矩阵的列数

3. st_write
```c
void st_write(
    char* filename, 
    int m, 
    int n, 
    int nst, 
    int ist[],
    int jst[], 
    double ast[], 
    char *title );
```
功能：

    将原ST数组展示在输出文件中

参数说明：

    char* filename: 保存st格式稀疏矩阵的文件的文件名
    int m:      原二维矩阵的行数  
    int n:      原二维矩阵的列数
    int nst[]:    非零元个数
    int ist[]:   行偏移数组  
    int jst[]:   列偏移数组  
    double ast[]: 非零元数组
    char *title: 补充说明

4. hyb_write
```c
void hyb_write(char* filename, hyb_fmt hyb, int n_row)
```
功能：

    将在转换后生成的HYB格式矩阵保存到输出文件

参数说明：

    char* filename: 保存输出结果的文件的文件名
    hyb_fmt hyb:   保存结果的HYB类型矩阵
    int n_row:      原二维矩阵的行数
