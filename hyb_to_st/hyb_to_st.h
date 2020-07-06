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

void hyb_read(char* filename, hyb_fmt *hyb);

void st_write(char* filename,st_fmt st);

void hyb_to_st(hyb_fmt hyb, st_fmt *st, int n_row);

void hyb_write(char* filename, hyb_fmt hyb, int n_row);