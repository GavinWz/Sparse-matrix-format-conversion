#include"st_to_cc.h"
#include<omp.h>

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col){
    clock_t begin = clock();
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return -1;
    }
    int n_val;
    fscanf(file, "%d%d%d", &(*n_row), &(*n_col), &n_val);
    
    st->ast = (double*)malloc(sizeof(double) * n_val);
    st->ist = (int*)malloc(sizeof(int) * n_val);
    st->jst = (int*)malloc(sizeof(int) * n_val);
    
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &(st->ist[index]), &(st->jst[index]), &(st->ast[index]));
        index++;
    }

    
    st->n_val = n_val;
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

void st_cc_sort(st_fmt* st, int left, int right){
    if(left >= right)
        return ;
    int i = left, j = right;
    int i_key = st->ist[i];     //保存基准值的行偏移
    int j_key = st->jst[i];     //保存基准值的列偏移
    double a_key = st->ast[i];  //保存基准值的非零元
    while(i < j){
        while(i < j && j_key <= st->jst[j])
            j--;
        if(i < j){
            st->ist[i] = st->ist[j];
            st->jst[i] = st->jst[j];
            st->ast[i] = st->ast[j];
        }
        while(i < j && j_key >= st->jst[i])
            i++;
        if(i < j){
            st->ist[j] = st->ist[i];
            st->jst[j] = st->jst[i];
            st->ast[j] = st->ast[i];
        }
        
    }
    st->ist[i] = i_key;
    st->jst[i] = j_key;
    st->ast[i] = a_key;
    st_cc_sort(st, left, i - 1);
    st_cc_sort(st, i + 1, right);
}

clock_t st_to_cc(st_fmt st, cc_fmt* cc, int n_row){
    clock_t begin = clock();
    int index = 1;
    int tag = st.jst[0];    //记录当前列偏移值
    cc->ccc = (int*)malloc(sizeof(int) * n_row + 1);
    cc->rcc = (int*)malloc(sizeof(int) * st.n_val);
    cc->vcc = (double*)malloc(sizeof(double) * st.n_val);
    cc->ccc[0] = 0;
    for(int i = 0; i < st.n_val; i++){
        cc->rcc[i] = st.ist[i];  //行偏移和非零元不变，直接赋值
        cc->vcc[i] = st.ast[i];
        if(st.jst[i] != tag){   //在列偏移值发生变化时更新当前列偏移值
            tag = st.jst[i];
            cc->ccc[index] = i;
            index++;
        }
    }
    cc->ccc[index] = st.n_val;
    cc->n_col = index;
    clock_t end = clock();
    return end - begin;
}

clock_t st_write(char* filename,st_fmt st){
    clock_t begin = clock();
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\nThe matrix in ST format:\n");
    fprintf (file, "  Number of non-zero elements: %d\n", st.n_val );
    fprintf (file, "\n   Rows  Cols   Values\n" );
    fprintf (file, "   ----  ----  --------------\n" );
    for ( k = 0; k < st.n_val; k++ )
    {
        fprintf (file, "  %4d  %4d  %10.5lf\n", st.ist[k], st.jst[k], st.ast[k] );
    }
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

clock_t cc_write(char* filename,cc_fmt cc){
    clock_t begin = clock();
    FILE* file = fopen(filename, "a");
    int k;
    fprintf (file, "\nCC: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in cc format:\n" );
    fprintf (file, "   Rows   Cols   Values \n" );
    fprintf (file, "   ----   ----   ------  \n" );
    
    for ( k = 0; k < cc.ccc[cc.n_col]; k++ )
    {
        
        if(k <= cc.n_col)
            fprintf(file, "  %4d  %4d  %10.5lf\n", cc.rcc[k], cc.ccc[k], cc.vcc[k]);
            
        else
            fprintf(file, "  %4d        %10.5lf\n", cc.rcc[k],  cc.vcc[k]);
            
    }
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

void time_write(char* filename, clock_t read_t, clock_t convert_t, clock_t write_t1, clock_t write_t2){
    FILE* file = fopen(filename, "a");
    fprintf(file, "\n------------------------------------\n");
    fprintf(file, "-------------Time Sheet-------------\n");
    if(read_t == -1){
        fprintf(file, "Input file opening failed\n");
        fprintf(file, "\n------------------------------------\n");
        return;
    }
    fprintf(file, "Data Read:\t\t%ld ms\n", read_t);
    fprintf(file, "Format Conversion:\t%ld ms\n", convert_t);
    fprintf(file, "CC Write:\t\t%ld ms\n", write_t1);
    fprintf(file, "ST Write:\t\t%ld ms\n", write_t2);
    fprintf(file, "------------------------------------\n");
}

void st_to_cc_run(char* ifilename, char* ofilename){
    st_fmt st;
    cc_fmt cc;
    int n_row;
    int n_col;
    clock_t st_read_t, cc_write_t, sort_t, st_write_t, convert_t;

    st_read_t = st_read(ifilename, &st, &n_row, &n_col);

    clock_t begin = clock();
    st_cc_sort(&st, 0, st.n_val-1);
    clock_t end = clock();
    sort_t = end - begin;

    convert_t = st_to_cc(st, &cc, n_row);
    st_write_t = st_write (ofilename, st);
    cc_write_t = cc_write(ofilename, cc);
    time_write(ofilename, st_read_t, convert_t + sort_t, st_write_t, cc_write_t);
}
