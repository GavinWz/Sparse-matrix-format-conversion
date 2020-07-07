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

void st_read(char* filename, st_fmt* st, int n_val);

void st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col);

void hyb_write(char* filename, hyb_fmt hyb, int n_row);

void st_write(char* filename,  int m, int n, int nst, int ist[], int jst[], double ast[], 
  char *title );

void test();