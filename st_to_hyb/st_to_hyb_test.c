#include<stdio.h>
#include"st_to_hyb.h"
void test(){
/*
    
    1 7 0 0 	
    0 2 8 0 
    5 0 3 9 
    0 6 0 4
    
    测试上述矩阵的ST格式转换为HYB格式，结果见output.txt
*/
    st_fmt st;
    st_read("input.txt", &st);

    int n_row = 4;
    int n_col = 4;

    hyb_fmt hyb;
    hyb.max = 2;

    st_to_hyb(st, &hyb, n_row, n_row);
    st_write ("output.txt", n_row, n_col, st.n_val, st.ist, st.jst, st.ast, "  The matrix in ST format:" );
    hyb_write("output.txt", hyb, n_row);
}


int main(){
    test();
}   
