# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>
#include "st_to_dia.h"

void dpre_usconv_st2dia(int m,int n,double* ast,int n_ast,int* ist,int* jst,int* LDA,int* NDIAG, int **idiag, double **val_dia)
{
  *NDIAG=0;
  *LDA=m<n?m:n;
  int num_rows,num_cols,num_nonzeros;
  int i,ii,jj,offset,map_index,complete_ndiags,VAL_DIA_size;
  const int unmarked = -1;
  num_rows = m;
  num_cols = n;
  num_nonzeros = n_ast;
  complete_ndiags = 0;
  int* diag_map = (int*)malloc(sizeof(int)*(num_rows+num_cols));     //mark the diags
  int* diag_offset = (int*)malloc(sizeof(int)*(num_cols+num_rows));
  memset(diag_map,unmarked,sizeof(int)*(num_rows+num_cols));
  memset(diag_offset,unmarked,sizeof(int)*(num_rows+num_cols));
  for(i=0;i<num_nonzeros;i++){
    ii = ist[i];
    jj = jst[i];
    map_index = num_rows-ii+jj;            //used to find the same diag
    if(diag_map[map_index] == unmarked){        
      diag_map[map_index] = complete_ndiags;
      diag_offset[map_index] = jj - ii;             //get index of diags
      complete_ndiags++;                 //number of diags
    }
  }
  *NDIAG = complete_ndiags;
  VAL_DIA_size=(*NDIAG)*(*LDA);
  int *IDIAG=(int*)malloc(sizeof(int)*(complete_ndiags));
  double *VAL_DIA=(double*)malloc(sizeof(double)*VAL_DIA_size);
  memset(IDIAG,0,sizeof(int)*(complete_ndiags));
  memset(VAL_DIA,0,sizeof(double)*VAL_DIA_size);
  for(i=0;i<num_rows + num_cols;i++){
    if(diag_map[i] != unmarked){
      IDIAG[diag_map[i]] = diag_offset[i];     //offset of diags
    }
  }
  for(i=0;i<num_nonzeros;i++){    //get values of every diag
    ii = ist[i];
    jj = jst[i];
    map_index = num_rows-ii+jj;
    int diag = diag_map[map_index];
    if((*LDA)-(num_rows-ii)>0){
      offset=(*LDA)-(num_rows-ii);
    }else{
      offset=0;
    }
    VAL_DIA[diag*(*LDA)+offset] = ast[i];
  }
 
  free(diag_map);
  free(diag_offset);
  *val_dia=VAL_DIA;  //Take the result out of the function
  *idiag=IDIAG;
}


// void dia_print (double *val, int n_val, int *indx, int lda, int ndiag)
// {

//   int i, j;
//   printf("DIA Matrix:\n");
//   for(i = 0; i < ndiag; i++){
//     printf("%3d:\t", indx[i]);
//     for(j = i * lda+1; j <= (i+1) * lda; j++){
//         printf("%lf\t", val[j]);
//     }
//     printf("\n");
//   }
  
// }

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

void dia_write(char* filename, double *val, int *indx, int lda, int ndiag){
    FILE* file = fopen(filename, "a");
    if(file == NULL){
        printf("Can't open the file: %s.\n", filename);
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

void st2dia(char* readFile, char* writeFile, int m, int n, int n_val){
    double *ast;
    int *ist, *jst;
    st_read(readFile, &ast, &ist, &jst);
    int lda, ndiag;
    int* idiag;
    double* val_dia;
    st_write (writeFile, m, n, n_val, ist, jst, ast, "  The matrix in ST format:" );
    dpre_usconv_st2dia(m, n, ast, n_val, ist, jst, &lda, &ndiag, &idiag, &val_dia);
    dia_write(writeFile, val_dia, idiag, lda, ndiag);
}
