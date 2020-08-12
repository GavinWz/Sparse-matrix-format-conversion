# 稀疏矩阵ST格式转换为CC格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd st_to_cc

make

./st_to_cc.exe (Linux为./test)
```
## 目标

将ST格式存储的稀疏矩阵转换为CC格式存储

## 主要文件

* input.txt: 存储ST格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* st_to_cc.c: 功能函数的实现
* st_to_cc_test.c: 测试

## 数据结构

```c
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
```

## 函数及参数含义
1. st_read
```c
clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col);
```
功能：

    从文件中读取st格式稀疏矩阵，将结果保存在st_fmt结构体变量中

参数说明：

    char* filename: 保存st格式稀疏矩阵的文件的文件名
    st_fmt* st: 输入的st格式矩阵
    int* n_row: 原矩阵行数
    int* n_col: 原矩阵列数

返回值: 程序运行时间，单位：毫秒(ms)

2. st_cc_sort
```c
void st_cc_sort(st_fmt* st, int left, int right)
```
功能：

    利用快速排序算法，将ST格式矩阵按行偏移从小到大排列

参数说明：

    st_fmt* st: ST格式矩阵指针 
    int left: 快速排序左指针: 0
    int right: 快速排序右指针: st.n_val-1

3. st_to_cc
```c
clock_t st_to_cc(st_fmt st, cc_fmt* cc, int n_row)；
```
功能：

    将ST格式矩阵转换为CC格式，将结果保存在cc_fmt结构体变量中

参数说明：

    st_fmt st: ST格式矩阵
    cc_fmt* cc: 保存结果的CC格式矩阵
    int n_row: 原矩阵行数

返回值: 程序运行时间，单位：毫秒(ms)

4. st_write
```c
clock_t st_write(char* filename,st_fmt st)
```
功能：

    将输入文件中的ST数组展示在输出文件中

参数说明：

    char* filename: 输出文件的文件名
    st_fmt st: ST格式结构体变量

返回值: 程序运行时间，单位：毫秒(ms)

5. cc_write
```c
clock_t cc_write(char* filename,cc_fmt cc)；
```
功能：
    
    将转换后的CC矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件名
    cc_fmt cc: CC格式矩阵

返回值: 程序运行时间，单位：毫秒(ms)

6. time_write
```c
void time_write(
    char* filename, 
    clock_t read_t, 
    clock_t convert_t, 
    clock_t write_t1, 
    clock_t write_t2
);
```
功能：

    输出各个环节的时间花费

参数说明：

    char* filename: 输出文件名
    clock_t read_t: 数据读取的时间花费
    clock_t convert_t: 格式转换的时间花费
    clock_t write_t1: 原矩阵写入的时间花费
    clock_t write_t2: 结果矩阵写入的时间花费

7. st_to_cc_run 
```c
void st_to_cc_run(char* ifilename, char* ofilename)
```
功能：

    给出输入文件名和输出文件名，进行读取、转换和保存

参数说明：

    char* ifilename: 保存ST矩阵的文件名
    char* ofilename: 保存CC结果矩阵的文件名
