# 稀疏矩阵ST格式转换为CR格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd st_to_cr

make

./st_to_cr.exe (Linux为./test)
```
## 目标

将ST格式存储的稀疏矩阵转换为CR格式存储

## 主要文件

* read.txt: 存储ST格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* st_to_cr.c: 功能函数的实现
* st_to_cr_test.c: 测试

## 函数及参数含义
1. st_read
```c
void st_read(char* filename, st_fmt* st, int* n_row, int* n_col);
```
功能：

    从文件中读取st格式稀疏矩阵，将结果保存在st_fmt结构体变量中

参数说明：

char* filename: 保存st格式稀疏矩阵的文件的文件名
st_fmt* st: 输入的st格式矩阵
int* n_row: 原矩阵行数
int* n_col: 原矩阵列数


2. st_to_cr
```c
void st_to_cr(st_fmt st, cr_fmt* cr, int n_row)；
```
功能：

    将ST格式矩阵转换为CR格式，将结果保存在cr_fmt结构体变量中

参数说明：

    st_fmt st: ST格式矩阵
    cr_fmt* cr: 保存结果的CR格式矩阵
    int n_row: 原矩阵行数

3. st_write
```c
void st_write(char* filename,st_fmt st)
```
功能：

    将输入文件中的ST数组展示在输出文件中

参数说明：

    char* filename: 输出文件的文件名
    st_fmt st: ST格式结构体变量

4. cr_write
```c
void cr_write(char* filename,cr_fmt cr)；
```
功能：
    
    将转换后的CR矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件名
    cr_fmt cr: CR格式矩阵

