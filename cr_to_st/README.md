# 稀疏矩阵CR格式转换为ST格式

## 编译运行

```
git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

cd cr_to_st

make

./cr_to_st.exe (Linux为./test)
```
## 目标

将ST格式存储的稀疏矩阵转换为CR格式存储

## 主要文件

* read.txt: 存储ST格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* cr_to_st.c: 功能函数的实现
* cr_to_st_test.c: 测试

## 函数及参数含义
1. cr_read
```c
void cr_read(char* filename, cr_fmt* cr);
```
功能：

    从文件中读取cr格式稀疏矩阵，将结果保存在cr_fmt结构体变量中

参数说明：

char* filename: 保存cr格式稀疏矩阵的文件的文件名
cr_fmt* cr: 输入的cr格式矩阵


2. cr_to_st
```c
void cr_to_st(st_fmt st, cr_fmt* cr, int n_row)；
```
功能：

    将CR格式矩阵转换为ST格式，将结果保存在st_fmt结构体变量中

参数说明：

    cr_fmt cr: CR格式矩阵
    st_fmt* st: 保存结果的ST格式矩阵
    int n_row: 原矩阵行数

3. cr_write
```c
void cr_write(char* filename,cr_fmt cr)；
```
功能：
    
    将输入文件中的的CR矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件名
    cr_fmt cr: CR格式结构体变量

4. st_write
```c
void st_write(char* filename,st_fmt st)
```
功能：

    将转换后ST矩阵展示在输出文件中

参数说明：

    char* filename: 输出文件的文件名
    st_fmt st: ST格式矩阵



