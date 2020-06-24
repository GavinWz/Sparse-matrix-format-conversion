# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>
#include "st_to_dia.h"

int main(){
// /******************************************************************************/
// /*
//   Purpose:

//     Test ST_TO_DIA using a tiny matrix.

//   Discussion:

//     This test uses a trivial matrix whose full representation is:

//           1  7  0  0            1  2  3  4 
//           0  2  8  0     ==>    7  8  9  0
//       A = 5  0  3  9            0  0  5  6
//           0  6  0  4           

//     A (1-based) ST representation, reading in order by rows is:

//       I  J   A
//      -- --  --
//       1  1   1
//       1  2   7

//       2  2   2
//       2  3   8

//       3  1   5
//       3  3   3
//       3  4   9

//       4  2   6
//       4  4   4

//     The DIA representation (which goes in order by columns) is

//     0:  1  2  3  4 
//     1:  7  8  9  0
//     -2: 0  0  5  6
      
//   Modified:

//     24 July 2020

    int m = 4;        //矩阵的行数 
    int n = 4;        //矩阵的列数
    int n_val = 9;    //非零元个数
    char* read = "./read.txt";    //输入文件，保存st类型矩阵
    char* write = "./output.txt"; //输出文件，保存程序运行结果
    st2dia(read, write, m, n, n_val);
}

// void test01 ( )

// /******************************************************************************/
// /*
//   Purpose:

//     TEST01 tests ST_TO_DIA using a tiny matrix.

//   Discussion:

//     This test uses a trivial matrix whose full representation is:

//           1  7  0  0            1  2  3  4 
//           0  2  8  0     ==>    7  8  9  0
//       A = 5  0  3  9            0  0  5  6
//           0  6  0  4           

//     A (1-based) ST representation, reading in order by rows is:

//       I  J   A
//      -- --  --
//       1  1   1
//       1  2   7

//       2  2   2
//       2  3   8

//       3  1   5
//       3  3   3
//       3  4   9

//       4  2   6
//       4  4   4

//     The DIA representation (which goes in order by columns) is

//     0:  1  2  3  4 
//     1:  7  8  9  0
//     -2: 0  0  5  6
      
//   Modified:

//     18 July 2020

 
// */
// {
// # define NST 9

//   double ast[NST] = {
//     1, 7, 
//     2, 8,
//     5, 3, 9,
//     6, 4 };
//   int ist[NST] = {
//     1, 1, 
//     2, 2, 
//     3, 3, 3, 
//     4, 4};
//   int jst[NST] = {
//     1, 2, 
//     2, 3, 
//     1, 3, 4, 
//     2, 4};
//   int m = 4;
//   int n = 4;
//   int nst = NST;

//   int lda;
//   int ndiag;
//   int* IDIAG;
//   double* VAL_DIA;

//   printf ( "\n" );
//   printf ( "TEST01\n" );
//   printf ( "  Convert a sparse matrix from ST to DIA format.\n" );
//   printf ( "  ST: sparse triplet,    I, J,  A.\n" );

//   dpre_usconv_st2dia(m, n, ast, NST, ist, jst, &lda, &ndiag, &IDIAG, &VAL_DIA);
//    st_print ( m, n, nst, ist, jst, ast, "  The matrix in ST format:" );
//    dia_print (VAL_DIA, nst, IDIAG, lda, ndiag);
//   return;
// # undef NST
// }

// void test02 ( )


// {
// # define NST 15

//   double ast[NST] = {
//     1, 7, 7,
//     2, 8, 5,
//     5, 3, 9, 3,
//     6, 4, 4,
//     5, 6};
//   int ist[NST] = {
//     1, 1, 1,
//     2, 2, 2,
//     3, 3, 3, 3, 
//     4, 4, 4,
//     5, 5};
//   int jst[NST] = {
//     1, 2, 3, 
//     2, 3, 4,
//     1, 3, 4, 5, 
//     2, 4, 5,
//     3, 5};
//   int m = 5;
//   int n = 5;
//   int nst = NST;

//   int lda;
//   int ndiag;
//   int* IDIAG;
//   double* VAL_DIA;

//   printf ( "\n" );
//   printf ( "TEST02\n" );
//   printf ( "  Convert a sparse matrix from ST to DIA format.\n" );
//   printf ( "  ST: sparse triplet,    I, J,  A.\n" );

//   dpre_usconv_st2dia(m, n, ast, NST, ist, jst, &lda, &ndiag, &IDIAG, &VAL_DIA);
//    st_print ( m, n, nst, ist, jst, ast, "  The matrix in ST format:" );
//    dia_print (VAL_DIA, nst, IDIAG, lda, ndiag);
//   return;
// # undef NST
// }

