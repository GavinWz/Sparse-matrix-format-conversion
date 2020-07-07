#include<stdio.h>
#include<stdlib.h>
#include"st_to_hyb.h"

void st_read(char* filename, st_fmt* st, int n_val){
    (*st).ast = (double*)malloc(sizeof(double) * n_val);
    (*st).ist = (int*)malloc(sizeof(int) * n_val);
    (*st).jst = (int*)malloc(sizeof(int) * n_val);
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return;
    }
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &((*st).ist[index]), &((*st).jst[index]), &((*st).ast[index]));
        index++;
    }
    (*st).n_val = n_val;
    printf("%d", index);
    fclose(file);
}

void st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col){
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
                // printf("%d\t%d\n",st.ist[i], j_index);
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
}

void st_write(char* filename,  int m, int n, int nst, int ist[], int jst[], double ast[], 
  char *title ){
    FILE* file = fopen(filename, "w+");
    fprintf (file, " Convert a sparse matrix from ST to DIA format.\n" );
    fprintf (file, " ST: sparse triplet,    I, J,  A.\n" );
    int k;
    fprintf (file, "\n" );
    fprintf (file, "%s\n", title );
    fprintf (file, "     #     I     J       A\n" );
    fprintf (file, "  ----  ----  ----  --------------\n" );
    fprintf (file, "\n" );
    for ( k = 0; k < nst; k++ )
    {
        fprintf (file, "  %4d  %4d  %4d  %10.8g\n", k, ist[k], jst[k], ast[k] );
    }
    fclose(file);
    return;
}

void hyb_write(char* filename, hyb_fmt hyb, int n_row){
    FILE *file = fopen(filename, "a");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
    fprintf(file, "\n------------------------------\n");
    fprintf(file, "The final HYB format martrix: \n");

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
    fprintf(file, "I         J         A         \n\t");
    fprintf(file, "------------------------------\n\t");
    for(int i = 0; i < hyb.n_val; i++){
        fprintf(file, "%-10d%-10d%-10.4lf\n", hyb.ist[i],hyb.jst[i],hyb.ast[i]);
    }
    fclose(file);
}

// st_to_hyb_run(char* ifilename, char* ofilename){

//     st_fmt st;
//     st_read(ifilename, &st, 8);

//     int n_row = 4;
//     int n_col = 4;

//     hyb_fmt hyb;
//     hyb.max = 2;

//     st_to_hyb(st, &hyb, n_row, n_row);
//     st_write ("output.txt", n_row, n_col, st.n_val, st.ist, st.jst, st.ast, "  The matrix in ST format:" );
//     hyb_write("output.txt", hyb, n_row);
// }