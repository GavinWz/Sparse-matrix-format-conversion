#include"cr_to_st.h"

clock_t cr_read(char* filename, cr_fmt* cr, int* row){
    clock_t begin = clock();
    FILE* file = fopen("input.txt", "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    int n_row, n_col, n_val;
    fscanf(file, "%d%d%d", &n_row, &n_col, &n_val);
    (*row) = n_row;
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
    clock_t end = clock();
    return end - begin;
}

clock_t cr_to_st(cr_fmt cr, st_fmt* st, int n_row){
    clock_t begin = clock();
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
    clock_t end = clock();
    return end - begin;
}

clock_t st_write(char* filename,st_fmt st){
    clock_t begin = clock();
    FILE* file = fopen(filename, "a");
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

clock_t cr_write(char* filename,cr_fmt cr){
    clock_t begin = clock();
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\nCR: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in CR format:\n" );
    fprintf (file, "   Rows   Cols   Values \n" );
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

void cr_to_st_run(char* ifilename, char* ofilename){
    cr_fmt cr;
    int n_row;
    clock_t cr_read_t, cr_write_t, st_write_t, convert_t;
    st_fmt st;

    cr_read_t = cr_read(ifilename, &cr, &n_row);
    convert_t = cr_to_st(cr, &st, n_row);
    cr_write_t = cr_write(ofilename, cr);
    st_write_t = st_write(ofilename, st);

    time_write(ofilename, cr_read_t, convert_t, cr_write_t, st_write_t);
}
