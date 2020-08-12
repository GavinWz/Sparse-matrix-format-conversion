# 稀疏矩阵CC格式转换为ST格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd cc_to_st

make

./cc_to_st.exe (Linux为./test)
```
## 目标

将ST格式存储的稀疏矩阵转换为CC格式存储

## 主要文件

* input.txt: 存储CC格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* cc_to_st.c: 功能函数的实现
* cc_to_st_test.c: 测试

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
1. cc_read
```c
clock_t cc_read(char* filename, cc_fmt* cc);
```
功能：

    从文件中读取CC格式稀疏矩阵，将结果保存在cc_fmt结构体变量中

参数说明：

    char* filename: 保存CC格式稀疏矩阵的文件的文件名
    cc_fmt* cc: 保存输入的CC格式矩阵

返回值: 程序运行时间，单位：毫秒(ms)

2. cc_to_st
```c
clock_t cc_to_st(st_fmt st, cc_fmt* cc);
```
功能：

    将cc格式矩阵转换为ST格式，将结果保存在st_fmt结构体变量中

参数说明：

    cc_fmt cc: CC格式矩阵
    st_fmt* st: 保存结果的ST格式矩阵

返回值: 程序运行时间，单位：毫秒(ms)

3. cc_write
```c
clock_t cc_write(char* filename,cc_fmt cc)；
```
功能：
    
    将输入文件中的的CC矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件名
    cc_fmt cc: CC格式结构体变量

返回值: 程序运行时间，单位：毫秒(ms)

4. st_write
```c
clock_t st_write(char* filename,st_fmt st)
```
功能：

    将转换后ST矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件的文件名
    st_fmt st: ST格式矩阵

返回值: 程序运行时间，单位：毫秒(ms)

5. time_write
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

返回值: 程序运行时间，单位：毫秒(ms)

6. cc_to_st_run
```c
void cc_to_st_run(char* ifilename, char* ofilename)
```
功能：

    执行转换程序，从输入文件中读取矩阵并将转换后的矩阵以及各个环节的时间消耗输出到输出文件

参数说明：

    char* ifilename: 输入文件名
    char* ofilename: 输出文件名
