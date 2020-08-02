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

## 函数及参数含义
1. cc_read
```c
void cc_read(char* filename, cc_fmt* cc, int* n_row);
```
功能：

    从文件中读取CC格式稀疏矩阵，将结果保存在cc_fmt结构体变量中

参数说明：

char* filename: 保存CC格式稀疏矩阵的文件的文件名
cc_fmt* cc: 输入的CC格式矩阵
int* n_row: 将原矩阵行数带出函数

2. cc_to_st
```c
void cc_to_st(st_fmt st, cc_fmt* cc, int n_row)；
```
功能：

    将cc格式矩阵转换为ST格式，将结果保存在st_fmt结构体变量中

参数说明：

    cc_fmt cc: CC格式矩阵
    st_fmt* st: 保存结果的ST格式矩阵
    int n_row: 原矩阵行数

3. cc_write
```c
void cc_write(char* filename,cc_fmt cc)；
```
功能：
    
    将输入文件中的的CC矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件名
    cc_fmt cc: CC格式结构体变量

4. st_write
```c
void st_write(char* filename,st_fmt st)
```
功能：

    将转换后ST矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件的文件名
    st_fmt st: ST格式矩阵



