#include"st_to_cr.h"

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

void st_cr_sort(st_fmt* st, int left, int right){
    if(left >= right)
        return;
    int i = left, j = right;
    int i_key = st->ist[i];
    int j_key = st->jst[i];
    double a_key = st->ast[i];
    while(i < j){
        while(i < j && i_key <= st->ist[j])
            j--;
        if(i < j){
            st->ist[i] = st->ist[j];
            st->jst[i] = st->jst[j];
            st->ast[i] = st->ast[j];
        }
        while(i < j && i_key >= st->ist[i])
            i++;
        if(i < j){
            st->ist[j] = st->ist[i];
            st->jst[j] = st->jst[i];
            st->ast[j] = st->ast[i];
        }
        
    }
    st->ist[i] = i_key;
    st->jst[i] = j_key;
    st->ast[i] = a_key;
    st_cr_sort(st, left, i - 1);
    st_cr_sort(st, i + 1, right);
}

void st_to_cr(st_fmt st, cr_fmt* cr, int n_row){
    int index = 1;
    int tag = st.ist[0];
    (*cr).rcr = (int*)malloc(sizeof(int) * n_row + 1);
    (*cr).ccr = (int*)malloc(sizeof(int) * st.n_val);
    (*cr).vcr = (double*)malloc(sizeof(double) * st.n_val);
    (*cr).rcr[0] = 0;
    for(int i = 0; i < st.n_val; i++){
        (*cr).ccr[i] = st.jst[i];
        (*cr).vcr[i] = st.ast[i];
        if(st.ist[i] != tag){
            tag = st.ist[i];
            (*cr).rcr[index] = i;
            index++;
        }
    }
    (*cr).rcr[index] = st.n_val;
    (*cr).n_row = index;
}

void st_write(char* filename,st_fmt st){
    FILE* file = fopen(filename, "w+");
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

void cr_write(char* filename,cr_fmt cr){
    FILE* file = fopen(filename, "a");
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

void st_to_cr_run(char* ifilename, char* ofilename){
    st_fmt st;
    int n_row;
    int n_col;
    int max;
    st_read(ifilename, &st, &n_row, &n_col);
    // st_write (ofilename, st);
    // printf("\n\n");

    st_cr_sort(&st, 0, st.n_val-1);

    // st_cr_sort(&st);
    cr_fmt cr;

    st_to_cr(st, &cr, n_row);
    st_write (ofilename, st);
    cr_write(ofilename, cr);
}
