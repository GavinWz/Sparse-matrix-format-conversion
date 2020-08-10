#include "st_to_dia.h"

clock_t dpre_usconv_st2dia(int m, int n, st_fmt st, dia_fmt* dia){
  clock_t begin = clock();
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
  clock_t end = clock();
  return end - begin;
}

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

clock_t dia_write(char* filename, dia_fmt dia){
    clock_t begin = clock();
    FILE* file = fopen(filename, "a");
    
    fprintf(file, "\nThe DIA martrix: \n");
    fprintf(file, "  Number of diagonals: %d\n", dia.ndiag);
    fprintf(file, "  Length of diagonals: %d\n\n", dia.ldiag);
    fprintf(file, "  Values:\n");
    for(int i = 0; i < dia.ndiag; i++){
        fprintf(file, "%4d: ", dia.idiag[i]);
        for(int j = 0; j < dia.ldiag; j++){
            fprintf(file, "%lf ", dia.val_dia[i*dia.ldiag+j]);
        }
        fprintf(file, "\n");
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

void st_to_dia_run(char* ifilename, char* ofilename){
    double *ast;
    int *ist, *jst;
    int n_row, n_col, n_val;
    st_fmt st;
    dia_fmt dia;
    clock_t st_read_t, dia_write_t, st_write_t, convert_t;

    st_read_t = st_read(ifilename, &st, &n_row, &n_col);
    convert_t = dpre_usconv_st2dia(n_row, n_col, st, &dia);
    st_write_t = st_write(ofilename,st);
    dia_write_t = dia_write(ofilename, dia);
    time_write(ofilename, st_read_t, convert_t, dia_write_t, st_write_t);
}
