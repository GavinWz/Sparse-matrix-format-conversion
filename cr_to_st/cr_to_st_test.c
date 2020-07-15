#include"cr_to_st.h"

int main(){
    cr_fmt cr;
    cr_read("input.txt", &cr);

    st_fmt st;
    cr_to_st(cr, &st, 4);
    cr_write("output.txt", cr);
    st_write("output.txt", st);
}