#include "dia_to_st.h"

clock_t dia_read(char* filename, dia_fmt* dia){
    clock_t begin = clock();
    int i = 0, j = 0;
    (*dia).n_val = 0;
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    fscanf(file, "%d%d", &(*dia).ndiag, &(*dia).ldiag);
    (*dia).idiag = (int*)malloc(sizeof(int) * (*dia).ndiag);
    (*dia).val_dia = (double*)malloc(sizeof(double) * (*dia).ldiag * (*dia).ndiag);
   
    while(feof(file) == 0){
        fscanf(file, "%d", &(*dia).idiag[i]);
        i++;
        for(int n = 0; n < (*dia).ldiag; n++){
            fscanf(file, "%lf", &(*dia).val_dia[j]);
            
            if((*dia).val_dia[j] != 0)
                (*dia).n_val++;
            j++;
        }
    }
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

clock_t dia_to_st(dia_fmt dia, st_fmt* st){
    clock_t begin = clock();
    st->ist = (int*)malloc(sizeof(int) * dia.n_val);
    st->jst = (int*)malloc(sizeof(int) * dia.n_val);
    st->ast = (double*)malloc(sizeof(double) * dia.n_val);
    int index = 0; //st矩阵下标
    int tag = 0;
    for(int order = 0; order < dia.ndiag; order++){
        int i = 0, j = 0;
        if(dia.idiag[order] >= 0)
            j += dia.idiag[order];
        else
            i -= dia.idiag[order];
        
        //若当前对角线为正偏移则无需跳过
        //若为负偏移，则跳过idiag[order]个0元素
        int skip = dia.idiag[order] >= 0 ? 0 : -1 * dia.idiag[order];
        tag += skip;
        for(int k = 0; k < dia.ldiag - skip; k++){
            if(dia.val_dia[tag] != 0){
                st->ist[index] = i >= 0 ? i : -1 * i;
                st->jst[index] = j;
                st->ast[index] = dia.val_dia[tag];
                index++;
            }
            i++, j++, tag++;
        }
        st->n_val = index;
    }
    clock_t end = clock();
    return end - begin;
}   

clock_t dia_write(char* filename, dia_fmt dia){
    clock_t begin = clock();
    FILE* file = fopen(filename, "w+");
    
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

void dia_to_st_run(char* ifilename, char* ofilename){
    dia_fmt dia;
    st_fmt st;
    clock_t dia_read_t, dia_write_t, st_write_t, convert_t;

    dia_read_t = dia_read("input.txt", &dia);
    convert_t = dia_to_st(dia, &st);
    dia_write_t = dia_write("output.txt", dia);
    st_write_t = st_write("output.txt", st);
    time_write(ofilename, dia_read_t, convert_t, dia_write_t, st_write_t);
    
}