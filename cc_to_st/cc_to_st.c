#include"cc_to_st.h"

clock_t cc_read(char* filename, cc_fmt* cc){
    clock_t begin = clock();
    FILE* file = fopen("input.txt", "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return -1;
    }
    int n_row, n_col, n_val;
    fscanf(file, "%d%d%d", &n_row, &n_col, &n_val);
    (*cc).rcc = (int*) malloc(sizeof(int) * n_val);
    (*cc).ccc = (int*) malloc(sizeof(int) * (n_col + 1));
    (*cc).vcc = (double*) malloc(sizeof(double) * n_val);
    for(int i = 0; i < n_val; i++){
        if(i <= n_col){
            fscanf(file, "%d%lf%d", &(*cc).rcc[i], &(*cc).vcc[i], &(*cc).ccc[i]);

        }
        else
        {
            fscanf(file, "%d%lf", &(*cc).rcc[i], &(*cc).vcc[i]);
        }
    }
    fclose(file);
    (*cc).n_col = n_col;
    clock_t end = clock();
    return end - begin;
}

clock_t cc_to_st(cc_fmt cc, st_fmt* st){
    clock_t begin = clock();
    int index = 1;
    int n_val = cc.ccc[cc.n_col];  //ccc[n_col]记录非零元个数
    (*st).ist = (int*)malloc(sizeof(int) * n_val);
    (*st).jst = (int*)malloc(sizeof(int) * n_val);
    (*st).ast = (double*)malloc(sizeof(double) * n_val);
    
    for(int i = 0; i < n_val; i++){  
        
        if(i == cc.ccc[index])
            index++;
        (*st).jst[i] = index-1;
        (*st).ist[i] = cc.rcc[i];
        (*st).ast[i] = cc.vcc[i];
    }
    (*st).n_val = cc.ccc[cc.n_col];
    clock_t end = clock();
    return end - begin;
}

clock_t st_write(char* filename,st_fmt st){
    clock_t begin = clock();
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
    clock_t end = clock();
    return end - begin;
}

clock_t cc_write(char* filename,cc_fmt cc){
    clock_t begin = clock();
    FILE* file = fopen(filename, "w+");
    int k;
    fprintf (file, "\nCC: sparse triplet, Row, Col, Value.\n" );
    fprintf (file, "  The matrix in cc format:\n" );
    fprintf (file, "   Row    Col    Value \n" );
    fprintf (file, "   ----   ----   ----  \n" );
    
    for ( k = 0; k < cc.ccc[cc.n_col]; k++ )
    {
        
        if(k <= cc.n_col)
            fprintf(file, "  %4d  %4d  %10.5lf\n", cc.rcc[k], cc.ccc[k], cc.vcc[k]);
            
        else
            fprintf(file, "  %4d        %10.5lf\n", cc.rcc[k],  cc.vcc[k]);
            
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

void cc_to_st_run(char* ifilename, char* ofilename){
    cc_fmt cc;
    clock_t cc_read_t, cc_write_t, st_write_t, convert_t;
    cc_read_t = cc_read(ifilename, &cc);
    st_fmt st;
    cc_write_t = cc_write(ofilename, cc);
    convert_t = cc_to_st(cc, &st);
    st_write_t = st_write(ofilename, st);
    time_write(ofilename, cc_read_t, convert_t, cc_write_t, st_write_t);
}
