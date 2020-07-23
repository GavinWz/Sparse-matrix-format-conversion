#include"cc_to_st.h"

void cc_read(char* filename, cc_fmt* cc, int* row){
    FILE* file = fopen("input.txt", "r");
    int n_row, n_col, n_val;
    fscanf(file, "%d%d%d", &n_row, &n_col, &n_val);
    (*row) = n_row;
    (*cc).rcc = (int*) malloc(sizeof(int) * (n_row + 1));
    (*cc).ccc = (int*) malloc(sizeof(int) * n_val);
    (*cc).vcc = (double*) malloc(sizeof(double) * n_val);
    
    for(int i = 0; i < n_val; i++){
        if(i <= n_row){
            fscanf(file, "%d%lf%d", &(*cc).rcc[i], &(*cc).vcc[i], &(*cc).ccc[i]);
        }
        else
        {
            fscanf(file, "%d%lf", &(*cc).rcc[i], &(*cc).vcc[i]);
        }
    }
    (*cc).n_row = n_row;
}

void cc_to_st(cc_fmt cc, st_fmt* st, int n_row){
    int index = 1;
    int n_val = cc.ccc[n_row];  //rcc[n_row]记录非零元个数
    (*st).ist = (int*)malloc(sizeof(int) * n_val);
    (*st).jst = (int*)malloc(sizeof(int) * n_val);
    (*st).ast = (double*)malloc(sizeof(double) * n_val);
   
    
    for(int i = 0; i < n_val; i++){  
        
        if(i == cc.ccc[index])
            index++;
        (*st).ist[i] = index-1;
        (*st).jst[i] = cc.rcc[i];
        (*st).ast[i] = cc.vcc[i];
    }
    (*st).n_val = cc.ccc[n_row];
}

void st_write(char* filename,st_fmt st){
    FILE* file = fopen(filename, "a");
    int k;
    fprintf (file, "\nST: sparse triplet,    I, J,  A.\n" );
    fprintf (file, "  The matrix in ST format:\n" );
    fprintf (file, "     I     J       A\n" );
    fprintf (file, "  ----  ----  --------------\n" );
    fprintf (file, "\n" );
    for ( k = 0; k < st.n_val; k++ )
    {
        fprintf (file, "  %4d  %4d  %10.5lf\n", st.ist[k], st.jst[k], st.ast[k] );
    }
    fclose(file);
    return;
}

void cc_write(char* filename,cc_fmt cc){
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\ncc: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in cc format:\n" );
    fprintf (file, "   Row    Col    Value \n" );
    fprintf (file, "   ----   ----   ----  \n" );
   
    for ( k = 0; k < cc.ccc[cc.n_row]; k++ )
    {
        
        if(k <= cc.n_row)
            fprintf(file, "  %4d  %4d  %10.5lf\n", cc.rcc[k], cc.ccc[k], cc.vcc[k]);
            
        else
            fprintf(file, "  %4d        %10.5lf\n", cc.rcc[k],  cc.vcc[k]);
            
    }
    fclose(file);
    return;
}

void cc_to_st_run(char* ifilename, char* ofilename){
    cc_fmt cc;
    int n_row;
    cc_read(ifilename, &cc, &n_row);
    // for(int i = 0; i < cc.ccc[n_row]; i++){
    //     printf("%d %lf ", cc.rcc[i], cc.vcc[i]);
    //     if(i < n_row)
    //         printf("%d\n", cc.ccc[i]);
    //     else
    //     {
    //         printf("\n");
    //     }
    // }
    st_fmt st;
    
    cc_to_st(cc, &st, n_row);
    cc_write(ofilename, cc);
    st_write(ofilename, st);
}
