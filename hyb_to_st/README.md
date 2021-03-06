# 稀疏矩阵HYB格式转换为ST格式

## 编译运行

```shell
$ git clone https://github.com/GavinWz/Sparse-matrix-format-conversion.git

$ cd hyb_to_st

$ make

$ ./hyb_to_st.exe (Linux为./hyb_to_st)
```
## 目标

将HYB格式存储的稀疏矩阵转换为ST格式存储

例： 

    1 0 0 0 	
    0 2 8 0 
    5 0 3 9 
    0 6 0 4
    
测试上述矩阵的HYB格式转换为ST格式，结果见[output.txt](https://github.com/GavinWz/Sparse-matrix-format-conversion/blob/master/hyb_to_st/output.txt)

注：

    ELL列偏移数组中，值-1表示此行此列的元素值为0

## 主要文件

* input.txt: 存储HYB格式稀疏矩阵的文件, 用于程序读取
* output.txt: 存储程序运行结果
* hyb_to_st.c: 功能函数的实现
* hyb_to_st_test.c: 测试

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
1. hyb_read
```c
clock_t hyb_read(char* filename, hyb_fmt *hyb)
```
功能：

    从文件中读取HYB格式稀疏矩阵，将结果保存在hyb_fmt结构体变量中

参数说明：

    char* filename: 保存HYB格式稀疏矩阵的文件的文件名
    hyb_fmt *hyb: 保存读取结果的hyb格式结构体变量指针

返回值: 程序运行时间，单位：毫秒(ms)

2. hyb_to_st
```c
clock_t hyb_to_st(hyb_fmt hyb, st_fmt *st, int n_row)
```
功能：

    将HYB格式矩阵转换为ST格式，将结果保存在st_fmt结构体变量中

参数说明：

    hyb_fmt hyb:      将要转换的HYB类型矩阵
    st_fmt *st:   保存结果的ST类型矩阵
    int n_row:      原二维矩阵的行数    

返回值: 程序运行时间，单位：毫秒(ms)

3. st_write
```c
clock_t st_write(char* filename,st_fmt st)
```
功能：

    将转换后的ST矩阵展示在输出文件中

参数说明：

    char* filename: 保存st格式稀疏矩阵的文件的文件名
    st_fmt st: st格式结构体变量

返回值: 程序运行时间，单位：毫秒(ms)

4. hyb_write
```c
clock_t hyb_write(char* filename, hyb_fmt hyb, int n_row)
```
功能：

    将原HYB格式矩阵保存到输出文件

参数说明：

    char* filename: 保存输出结果的文件的文件名
    hyb_fmt hyb:   保存结果的HYB类型矩阵
    int n_row:      原二维矩阵的行数

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

6. hyb_to_st_run 
```c
void hyb_to_st_run(char* ifilename, char* ofilename)
```
功能：

    给出输入文件名和输出文件名，进行读取、转换和保存

参数说明：

    char* ifilename: 保存HYB矩阵的文件名
    char* ofilename: 保存ST结果矩阵的文件名