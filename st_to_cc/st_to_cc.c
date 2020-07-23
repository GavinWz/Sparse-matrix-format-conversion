#include"st_to_cc.h"

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

void st_to_cc(st_fmt st, cc_fmt* cc, int n_row){
    int index = 1;
    int tag = st.ist[0];
    (*cc).ccc = (int*)malloc(sizeof(int) * n_row + 1);
    (*cc).rcc = (int*)malloc(sizeof(int) * st.n_val);
    (*cc).vcc = (double*)malloc(sizeof(double) * st.n_val);
    (*cc).ccc[0] = 0;
    for(int i = 0; i < st.n_val; i++){
        (*cc).rcc[i] = st.jst[i];
        (*cc).vcc[i] = st.ast[i];
        if(st.ist[i] != tag){
            tag = st.ist[i];
            (*cc).ccc[index] = i;
            index++;
        }
    }
    (*cc).ccc[index] = st.n_val;
    (*cc).n_row = index;
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
    fclose(file);
    return;
}

void cc_write(char* filename,cc_fmt cc){
    FILE* file = fopen(filename, "a");
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

void st_to_cc_run(char* ifilename, char* ofilename){
    st_fmt st;
    int n_row;
    int n_col;
    int max;
    st_read(ifilename, &st, &n_row, &n_col);
    
    cc_fmt cc;

    st_to_cc(st, &cc, n_row);
    st_write (ofilename, st);
    cc_write(ofilename, cc);
}
