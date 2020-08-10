#include"hyb_to_st.h"

clock_t hyb_read(char* filename, hyb_fmt *hyb, int* row){
    int n_row, n_col;
    int i, j;
    clock_t begin = clock();
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    fscanf(file, "%d%d%d", &n_row, &n_col, &(*hyb).max);
    if((*hyb).max < 1){
        printf("The max limit per row must be greater than 0.\n");
        return -2;
    }

    (*hyb).offset = (int**)malloc(sizeof(int)*n_col*(*hyb).max);
    (*hyb).eData = (double**)malloc(sizeof(double)*n_col*(*hyb).max);

    (*hyb).ist = (int*)malloc(sizeof(int)*n_row*(n_col-(*hyb).max));
    (*hyb).jst = (int*)malloc(sizeof(int)*n_row*(n_col-(*hyb).max));
    (*hyb).ast = (double*)malloc(sizeof(double)*n_row*(n_col-(*hyb).max));

    for(i = 0; i < n_row; i++){
        for(j = 0; j < (*hyb).max; j++){
            fscanf(file, "%d", &*((int*)(*hyb).offset+i*(*hyb).max+j));
        }
    }
    for(i = 0; i < n_row; i++){
        for(j = 0; j < (*hyb).max; j++){
            fscanf(file, "%lf", &*((double*)(*hyb).eData+i*(*hyb).max+j));
        }
    }
    for(i = 0; feof(file) == 0; i++){
        fscanf(file, "%d%d%lf", &(*hyb).ist[i], &(*hyb).jst[i], &(*hyb).ast[i]);
    }
    (*hyb).n_val = i;
    (*row) = n_row;
    clock_t end = clock();
    return end - begin;
}

clock_t hyb_to_st(hyb_fmt hyb, st_fmt *st, int n_row){
    clock_t begin = clock();
    (*st).ist = (int*)malloc(sizeof(int) * n_row * hyb.max);
    (*st).jst = (int*)malloc(sizeof(int) * n_row * hyb.max);
    (*st).ast = (double*)malloc(sizeof(double) * n_row * hyb.max);
    int index = 0;
    int i, j;
    for(i = 0; i < n_row; i++){
        for(j = 0; j < hyb.max; j++){
            if(*((int*)hyb.offset + i * hyb.max + j) == -1)
                break;
            (*st).ist[index] = i;
            (*st).jst[index] = *((int*)hyb.offset + i * hyb.max + j);
            (*st).ast[index] = *((double*)hyb.eData + i * hyb.max + j);
            index++;
        }
    }
    for(i = 0; i < hyb.n_val; i++){
        (*st).ist[index] = hyb.ist[i];
        (*st).jst[index] = hyb.jst[i];
        (*st).ast[index] = hyb.ast[i];
        index++;
    }
    (*st).n_val = index;
    clock_t end = clock();
    return end - begin;
}

clock_t st_write(char* filename,st_fmt st){
    clock_t begin = clock();
    FILE* file = fopen(filename, "a");
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

void hyb_to_st_run(char* ifilename, char* ofilename){
    hyb_fmt hyb;
    st_fmt st;
    int n_row;
    clock_t hyb_read_t, hyb_write_t, st_write_t, convert_t;

    hyb_read_t = hyb_read(ifilename, &hyb, &n_row);
    convert_t = hyb_to_st(hyb, &st, n_row);
    hyb_write_t = hyb_write(ofilename, hyb, n_row);
    st_write_t = st_write(ofilename, st);
    time_write(ofilename, hyb_read_t, convert_t, hyb_write_t, st_write_t);

}