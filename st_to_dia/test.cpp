#include<stdio.h>
#include<stdlib.h>
#include"st_to_dia.h"
int st_read(char* filename,double **ast,int **ist, int **jst){
    *ast = (double*)malloc(sizeof(double) * 10);
    *ist = (int*)malloc(sizeof(int) * 10);
    *jst = (int*)malloc(sizeof(int) * 10);
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &(*ist)[index], &(*jst)[index], &(*ast)[index]);
        index++;
    }
    fclose(file);
    return index;
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

void dia_write(char* filename, double *val, int n_val, int *indx, int lda, int ndiag){
    FILE* file = fopen(filename, "a");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
    int i, j;
    fprintf(file, "\nDIA Matrix:\n");
    for(i = 0; i < ndiag; i++){
        fprintf(file, "%3d:\t", indx[i]);
        for(j = i * lda+1; j <= (i+1) * lda; j++){
            fprintf(file, "%lf\t", val[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int max(int* arr, int length){
    int max = arr[0];
    for(int i = 1; i < length; i++){
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

void st2dia(char* readFile, char* writeFile, int m, int n, int n_val){
    double *ast;
    int *ist, *jst;
    st_read(readFile, &ast, &ist, &jst);
    int lda, ndiag;
    int* idiag;
    double* val_dia;
    st_write (writeFile, m, n, n_val, ist, jst, ast, "  The matrix in ST format:" );
    dpre_usconv_st2dia(m, n, ast, n_val, ist, jst, &lda, &ndiag, &idiag, &val_dia);
    dia_write(writeFile, val_dia, n_val, idiag, lda, ndiag);
}



int main(){
    int m = 4;
    int n = 4;
    int n_val = 9;
    char* read = "./test.txt";
    char* write = "./output.txt";
    st2dia(read, write, m, n, n_val);
}

