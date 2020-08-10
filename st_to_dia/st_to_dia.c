# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>
#include "st_to_dia.h"

void dpre_usconv_st2dia(int m, int n, st_fmt st, dia_fmt* dia)
{
  dia->ndiag=0;
  dia->ldiag=m<n?m:n;
  int num_rows,num_cols,num_nonzeros;
  int i,ii,jj,offset,map_index,complete_ndiags,VAL_DIA_size;
  const int unmarked = -1;
  num_rows = m;
  num_cols = n;
  num_nonzeros = st.n_val;
  complete_ndiags = 0;
  int* diag_map = (int*)malloc(sizeof(int)*(num_rows+num_cols));     //mark the diags
  int* diag_offset = (int*)malloc(sizeof(int)*(num_cols+num_rows));
  memset(diag_map,unmarked,sizeof(int)*(num_rows+num_cols));
  memset(diag_offset,unmarked,sizeof(int)*(num_rows+num_cols));
  for(i=0;i<num_nonzeros;i++){
    ii = st.ist[i];
    jj = st.jst[i];
    map_index = num_rows-ii+jj;            //used to find the same diag
    if(diag_map[map_index] == unmarked){        
      diag_map[map_index] = complete_ndiags;
      diag_offset[map_index] = jj - ii;             //get index of diags
      complete_ndiags++;                 //number of diags
    }
  }
  dia->ndiag = complete_ndiags;
  VAL_DIA_size=dia->ndiag*dia->ldiag;
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
    ii = st.ist[i];
    jj = st.jst[i];
    map_index = num_rows-ii+jj;
    int diag = diag_map[map_index];
    if(dia->ldiag-(num_rows-ii)>0){
      offset=dia->ldiag-(num_rows-ii);
    }else{
      offset=0;
    }
    VAL_DIA[diag*dia->ldiag+offset] = st.ast[i];
  }
 
  free(diag_map);
  free(diag_offset);
  dia->val_dia=VAL_DIA;  //Take the result out of the function
  dia->idiag=IDIAG;
}

void st_read(char* filename, st_fmt* st, int* n_row, int* n_col){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return;
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
}

void st_write(char* filename,st_fmt st){
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\nST: sparse triplet,    I, J,  A.\n" );
    fprintf (file, "  The matrix in ST format:\n" );
    fprintf (file, "     #     I     J       A\n" );
    fprintf (file, "  ----  ----  ----  --------------\n" );
    fprintf (file, "\n" );
    for ( k = 0; k < st.n_val; k++ )
    {
        fprintf (file, "  %4d  %4d  %10.5lf\n", st.ist[k], st.jst[k], st.ast[k] );
    }
    fprintf (file, "\n" );
    fclose(file);
    return;
}

void dia_write(char* filename, dia_fmt dia){
    FILE* file = fopen(filename, "a");
    if(!file){
        fprintf(file, "Can not open the output file.");
        return;
    }
    fprintf(file, "\nThe DIA martrix is: \n");
    for(int i = 0; i < dia.ndiag; i++){
        fprintf(file, "%4d: ", dia.idiag[i]);
        for(int j = 0; j < dia.ldiag; j++){
            fprintf(file, "%lf ", dia.val_dia[i*dia.ldiag+j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void st_to_dia_run(char* readFile, char* writeFile){
    double *ast;
    int *ist, *jst;
    int n_row, n_col, n_val;

    st_fmt st;
    dia_fmt dia;
    st_read(readFile, &st, &n_row, &n_col);
    dpre_usconv_st2dia(n_row, n_col, st, &dia);
    st_write(writeFile,st);
    dia_write(writeFile, dia);
}
