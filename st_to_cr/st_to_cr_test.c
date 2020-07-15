#include"st_to_cr.h"

int main(){

    st_fmt st;
    int n_row;
    int n_col;
    int max;
    st_read("input.txt", &st, &n_row, &n_col);
    
    cr_fmt cr;

    st_to_cr(st, &cr, n_row);
    st_write ("output.txt", st);
    cr_write("output.txt", cr);
}