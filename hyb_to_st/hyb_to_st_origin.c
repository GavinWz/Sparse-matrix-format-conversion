#include<stdio.h>
#include<stdlib.h>

typedef struct st{
    int *ist;
    int *jst;
    double *ast;
    int n_val;
} st_fmt;

typedef struct hyb{ 
    double** eData;
    int** offset;
    int max;
    int* ist;
    int* jst;
    double* ast;
    int n_val;
} hyb_fmt;

void hyb_to_st(hyb_fmt hyb, st_fmt *st, int n_row){
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
}

void hyb_read(char* filename, hyb_fmt *hyb){
    int n_row, n_col;
    int i, j;

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
    fscanf(file, "%d,%d,%d", &n_row, &n_col, &(*hyb).max);

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
}

void st_write(char* filename,st_fmt st){
    FILE* file = fopen(filename, "a");
    int k;
    fprintf (file, "\nST: sparse triplet,    I, J,  A.\n" );
    fprintf (file, "  The matrix in ST format:\n" );
    fprintf (file, "     #     I     J       A\n" );
    fprintf (file, "  ----  ----  ----  --------------\n" );
    fprintf (file, "\n" );
    for ( k = 0; k < st.n_val; k++ )
    {
        fprintf (file, "  %4d  %4d  %4d  %10.8g\n", k, st.ist[k], st.jst[k], st.ast[k] );
    }
    fclose(file);
    return;
}

void hyb_write(char* filename, hyb_fmt hyb, int n_row){
    FILE *file = fopen(filename, "w+");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
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
    fprintf(file, "------------------------------\n\t");
    for(int i = 0; i < hyb.n_val; i++){
        fprintf(file, "%-10d%-10d%-10.4lf\n", hyb.ist[i],hyb.jst[i],hyb.ast[i]);
    }
    fclose(file);
}

int main(){
    hyb_fmt hyb;
    hyb_read("input.txt", &hyb);
    st_fmt st;
    hyb_to_st(hyb, &st, 4);
    hyb_write("output.txt", hyb, 4);
    st_write("output.txt", st);
/*
    ELL Column indices: 
	0         -1        
	1         2         
	0         2         
	1         3         
HYb:
	ELL Values: 
	1.0000    0.0000    
	2.0000    8.0000    
	5.0000    3.0000    
	6.0000    4.0000    
	
	ST Martrix: 
	i         j         v         
	------------------------------
	2         3         9.0000   

HYB to ST:
    0       0       1.000000
    1       1       2.000000
    1       2       8.000000
    2       0       5.000000
    2       2       3.000000
    3       1       6.000000
    3       3       4.000000
    2       3       9.000000 
*/

 

}
