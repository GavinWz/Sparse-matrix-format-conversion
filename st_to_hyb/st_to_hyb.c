#include"st_to_hyb.h"

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col, int* max){
    clock_t begin = clock();
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return -1;
    }
    int n_val;
    fscanf(file, "%d%d%d%d", &(*n_row), &(*n_col), &n_val, &(*max));
    if((*max) < 1){
        printf("The max limit per row must be greater than 0.\n");
        return -2;
    }
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

clock_t st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col){
    clock_t begin = clock();
    (*hyb).ist = (int*)malloc(sizeof(int) * (n_col - (*hyb).max));
    (*hyb).jst = (int*)malloc(sizeof(int) * (n_col - (*hyb).max));
    (*hyb).ast = (double*)malloc(sizeof(double) * (n_col - (*hyb).max));
    (*hyb).eData = (double**)malloc(sizeof(double) * n_row * (*hyb).max);
    (*hyb).offset = (int**)malloc(sizeof(int) * n_row * (*hyb).max);

    int cnt = 0;
    int index = -1;
    int j_index = 0;
    int e_index = 0;
    (*hyb).n_val = 0;

    for(int i = 0; i < st.n_val; i++){
        if(index == st.ist[i])
            cnt++;
        else{
            index = st.ist[i];
            while(j_index < (*hyb).max){
                *((int*)(*hyb).offset+st.ist[i]*(*hyb).max+j_index) = -1;
                j_index++;
            }
            cnt = 1;
            j_index = 0;
        }
        if(cnt <= (*hyb).max){
            *((int*)(*hyb).offset+st.ist[i]*(*hyb).max+j_index) = st.jst[i];
            *((double*)(*hyb).eData+st.ist[i]*(*hyb).max+j_index) = st.ast[i];
            j_index++;
        }
        else{
            (*hyb).ist[(*hyb).n_val] = st.ist[i];
            (*hyb).jst[(*hyb).n_val] = st.jst[i];
            (*hyb).ast[(*hyb).n_val] = st.ast[i];
            (*hyb).n_val++;
        }
    }
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

clock_t hyb_write(char* filename, hyb_fmt hyb, int n_row){
    clock_t begin = clock();
    FILE *file = fopen(filename, "w+");
    fprintf (file, "Convert a sparse matrix from HYB to ST format.\n" );
 
    fprintf(file, "\n------------------------------\n");
    fprintf(file, "The original HYB format martrix: \n");

    fprintf(file, "\n\tELL Column indices: \n\t");
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < hyb.max; j++){
            fprintf(file, "%-10d", *((int*)hyb.offset+i*hyb.max+j));
        }
        fprintf(file, "\n\t");
    }
    fprintf(file, "\n\tELL Values: \n\t");
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < hyb.max; j++){
            fprintf(file, "%-10.4lf", *((double*)hyb.eData+i*hyb.max+j));
        }
        fprintf(file, "\n\t");
    }
    fprintf(file, "\n\tST Martrix: \n\t");
    fprintf(file, "I         J         V         \n\t");
    fprintf(file, "------------------------------\n");
    for(int i = 0; i < hyb.n_val; i++){
        fprintf(file, "\t%-10d%-10d%-10.4lf\n", hyb.ist[i],hyb.jst[i],hyb.ast[i]);
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
    else if(read_t == -2){
        fprintf(file, "The max limit per row must be greater than 0.\n");
        fprintf(file, "\n------------------------------------\n");
        return;
    }
    fprintf(file, "Data Read:\t\t%ld ms\n", read_t);
    fprintf(file, "Format Conversion:\t%ld ms\n", convert_t);
    fprintf(file, "CC Write:\t\t%ld ms\n", write_t1);
    fprintf(file, "ST Write:\t\t%ld ms\n", write_t2);
    fprintf(file, "------------------------------------\n");
}

void st_to_hyb_run(char* ifilename, char* ofilename){
    st_fmt st;
    int n_row;
    int n_col;
    int max;
    hyb_fmt hyb;
    
    clock_t st_read_t, hyb_write_t, st_write_t, convert_t;

    st_read_t = st_read(ifilename, &st, &n_row, &n_col, &max);
    hyb.max = max;
    convert_t = st_to_hyb(st, &hyb, n_row, n_row);
    st_write_t = st_write (ofilename, st);
    hyb_write_t = hyb_write(ofilename, hyb, n_row);

    time_write(ofilename, st_read_t, convert_t, hyb_write_t, st_write_t);
}