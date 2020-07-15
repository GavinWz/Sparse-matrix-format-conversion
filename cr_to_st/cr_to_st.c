#include"cr_to_st.h"

void cr_read(char* filename, cr_fmt* cr){
    FILE* file = fopen("input.txt", "r");
    int n_row, n_col, n_val;
    fscanf(file, "%d%d%d", &n_row, &n_col, &n_val);
    (*cr).rcr = (int*) malloc(sizeof(int) * (n_row + 1));
    (*cr).ccr = (int*) malloc(sizeof(int) * n_val);
    (*cr).vcr = (double*) malloc(sizeof(double) * n_val);
    
    for(int i = 0; i < n_val; i++){
        if(i <= n_row){
            fscanf(file, "%d%lf%d", &(*cr).ccr[i], &(*cr).vcr[i], &(*cr).rcr[i]);
        }
        else
        {
            fscanf(file, "%d%lf", &(*cr).ccr[i], &(*cr).vcr[i]);
        }
    }
    (*cr).n_row = n_row;
}

void cr_to_st(cr_fmt cr, st_fmt* st, int n_row){
    int index = 1;
    int n_val = cr.rcr[n_row];  //rcr[n_row]记录非零元个数
    (*st).ist = (int*)malloc(sizeof(int) * n_val);
    (*st).jst = (int*)malloc(sizeof(int) * n_val);
    (*st).ast = (double*)malloc(sizeof(double) * n_val);

    for(int i = 0; i < n_val; i++){  
        if(i == cr.rcr[index])
            index++;
        (*st).ist[i] = index-1;
        (*st).jst[i] = cr.ccr[i];
        (*st).ast[i] = cr.vcr[i];
    }
    (*st).n_val = cr.rcr[n_row];
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
        fprintf (file, "  %4d  %4d  %10.5lf\n", st.ist[k], st.jst[k], st.ast[k] );
    }
    fclose(file);
    return;
}

void cr_write(char* filename,cr_fmt cr){
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\nCR: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in CR format:\n" );
    fprintf (file, "   Row    Col    Value \n" );
    fprintf (file, "   ----   ----   ----  \n" );
    for ( k = 0; k < cr.rcr[cr.n_row]; k++ )
    {
        if(k <= cr.n_row)
            fprintf(file, "  %4d", cr.rcr[k]);
        else
            fprintf(file, "      ");
        fprintf(file, "  %4d  %10.5lf\n", cr.ccr[k], cr.vcr[k]);
    }

    
    fclose(file);
    return;
}


