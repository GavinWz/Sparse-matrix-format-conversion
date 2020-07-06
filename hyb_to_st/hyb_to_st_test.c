#include<stdio.h>
#include<stdlib.h>
#include"hyb_to_st.h"

int main(){
    hyb_fmt hyb;
    hyb_read("input.txt", &hyb);
    st_fmt st;
    hyb_to_st(hyb, &st, 4);
    hyb_write("output.txt", hyb, 4);
    st_write("output.txt", st);
}