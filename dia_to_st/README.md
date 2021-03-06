# 稀疏矩阵DIA格式转换为ST格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd dia_to_st

make

./test.exe (Linux为./test)
```
## 目标

将DIA格式存储的稀疏矩阵转换为ST格式存储

## 主要文件

* read.txt: 存储DIA格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* dia_to_st.c: 功能函数的实现
* dia_to_st_test.c: 测试

## 数据结构

```c
typedef struct dia{
    int ldiag;  //对角线长度
    int ndiag;  //对角线个数
    int* idiag; /*对角线编号数组,中心对角线编号为0，向右上递增为1,
        2，…,向左下递减为-1.-2,…. */ 
    double* val_dia;  /*DIA所有元素值组成的一维数组，按行优先保存
        生成的二维数组*/
    int n_val;  //非零元个数
} dia_fmt;

typedef struct st{
    int *ist;   //行偏移数组
    int *jst;   //列偏移数组
    double *ast; //非零元数组
    int n_val;  //非零元个数
} st_fmt;
```

## 函数及参数含义
1. dia_read
```c
clock_t dia_read(char* filename, dia_fmt* dia);
```
功能：

    从文件中读取DIA格式稀疏矩阵，将结果保存在dia_fmt结构体变量中

参数说明：

    char* filename: 保存st格式稀疏矩阵的文件的文件名
    dia_fmt* dia: dia格式结构体指针

返回值: 程序运行时间，单位：毫秒(ms)

2. dia_to_st
```c
clock_t dia_to_st(dia_fmt dia, st_fmt* st){
```
功能：

    将DIA格式矩阵转换为ST格式，将结果保存在ST格式结构体中

参数说明：

    dia_fmt dia: DIA格式结构体变量
    st_fmt* st: ST格式结构体指针

返回值: 程序运行时间，单位：毫秒(ms)

3. dia_write
```c
clock_t dia_write(char* filename, dia_fmt dia);
```
功能：

    将DIA格式稀疏矩阵输出到文件中

参数说明：

    char* filename: 输出文件名
    dia_fmt dia: DIA格式结构体变量

返回值: 程序运行时间，单位：毫秒(ms)

4. st_write
```c
clock_t st_write(char* filename,st_fmt st)
```
功能：

    将ST矩阵展示在输出文件中

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

6. dia_to_st_run
```c
void dia_to_st_run(char* ifilename, char* ofilename)
```
功能：

    执行转换程序，从输入文件中读取矩阵并将转换后的矩阵以及各个环节的时间消耗输出到输出文件

参数说明：

    char* ifilename: 输入文件名
    char* ofilename: 输出文件名