#include"st_to_cr.h"

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col){
    clock_t begin = clock();
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return -1;
    }
    int n_val;
    fscanf(file, "%d%d%d", &(*n_row), &(*n_col), &n_val);
    
    (*st).ast = (double*)malloc(sizeof(double) * n_val);
    (*st).ist = (int*)malloc(sizeof(int) * n_val);
    (*st).jst = (int*)malloc(sizeof(int) * n_val);
    
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &((*st).ist[index]), &((*st).jst[index]), &((*st).ast[index]));
        index++;
    }
    (*st).n_val = n_val;
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

void st_cr_sort(st_fmt* st, int left, int right){
    if(left >= right)
        return ;
    int i = left, j = right;
    int i_key = st->ist[i];
    int j_key = st->jst[i];
    double a_key = st->ast[i];
    while(i < j){
        while(i < j && i_key <= st->ist[j])
            j--;
        if(i < j){
            st->ist[i] = st->ist[j];
            st->jst[i] = st->jst[j];
            st->ast[i] = st->ast[j];
        }
        while(i < j && i_key >= st->ist[i])
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
    st_cr_sort(st, left, i - 1);
    st_cr_sort(st, i + 1, right);
}

clock_t st_to_cr(st_fmt st, cr_fmt* cr, int n_row){
    clock_t begin = clock();
    int index = 1;
    int tag = st.ist[0];
    (*cr).rcr = (int*)malloc(sizeof(int) * n_row + 1);
    (*cr).ccr = (int*)malloc(sizeof(int) * st.n_val);
    (*cr).vcr = (double*)malloc(sizeof(double) * st.n_val);
    (*cr).rcr[0] = 0;
    for(int i = 0; i < st.n_val; i++){
        (*cr).ccr[i] = st.jst[i];
        (*cr).vcr[i] = st.ast[i];
        if(st.ist[i] != tag){
            tag = st.ist[i];
            (*cr).rcr[index] = i;
            index++;
        }
    }
    (*cr).rcr[index] = st.n_val;
    (*cr).n_row = index;
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

clock_t cr_write(char* filename,cr_fmt cr){
    clock_t begin = clock();
    FILE* file = fopen(filename, "a");
    int k;
    fprintf (file, "\nCR: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in CR format:\n" );
    fprintf (file, "   Rows   Cols   Values \n" );
    fprintf (file, "   ----   ----   ----  \n" );
    for ( k = 0; k < cr.rcr[cr.n_row]; k++ )
    {
        if(k <= cr.n_row)
            fprintf(file, "  %4d", cr.rcr[k]);
        else
            fprintf(file, "      ");
        fprintf(file, "  %4d  %10.5lf\n", cr.ccr[k], cr.vcr[k]);
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

void st_to_cr_run(char* ifilename, char* ofilename){
    st_fmt st;
    cr_fmt cr;
    int n_row;
    int n_col;
    clock_t st_read_t, cr_write_t, sort_t, st_write_t, convert_t;

    st_read_t = st_read(ifilename, &st, &n_row, &n_col);

    clock_t begin = clock();
    st_cr_sort(&st, 0, st.n_val-1);
    clock_t end = clock();
    sort_t = end - begin;
    
    convert_t = st_to_cr(st, &cr, n_row);
    st_write_t = st_write (ofilename, st);
    cr_write_t = cr_write(ofilename, cr);
    
    time_write(ofilename, st_read_t, convert_t + sort_t, st_write_t, cr_write_t);
}
