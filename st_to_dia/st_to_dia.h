void dpre_usconv_st2dia  (int m,int n,double* VAL,int n_VAL,int* INDX,int* JNDX,
    int* LDA,int* NDIAG, int **idiag, double **val_dia);
void st_print ( int m, int n, int nst, int ist[], int jst[], double ast[], 
    char *title );
void dia_print (double *val, int n_val, int *indx, int lda, int ndiag);
void st2dia(char* readFile, char* writeFile, int m, int n, int n_val);
void dia_write(char* filename, double *val, int *indx, int lda, int ndiag);
void st_write(char* filename,  int m, int n, int nst, int ist[], int jst[], double ast[], char *title);
void test01 ( );
void test02 ( );