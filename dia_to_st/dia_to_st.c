#include "dia_to_st.h"

void dia_read(char* filename, dia_fmt* dia){
    int i = 0, j = 0;
    (*dia).n_val = 0;
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
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
}

void dia_to_st(dia_fmt dia, st_fmt* st){
    (*st).ist = (int*)malloc(sizeof(int) * dia.n_val);
    (*st).jst = (int*)malloc(sizeof(int) * dia.n_val);
    (*st).ast = (double*)malloc(sizeof(double) * dia.n_val);
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
                (*st).ist[index] = i >= 0 ? i : -1 * i;
                (*st).jst[index] = j;
                (*st).ast[index] = dia.val_dia[tag];
                index++;
            }
            i++, j++, tag++;
        }
        (*st).n_val = index;
    }
    
}   

void dia_write(char* filename, dia_fmt dia){
    FILE* file = fopen(filename, "w");
    if(!file){
        fprintf(file, "Can not open the output file.");
        return;
    }
    fprintf(file, "The DIA martrix is: \n");
    for(int i = 0; i < dia.ndiag; i++){
        fprintf(file, "%4d: ", dia.idiag[i]);
        for(int j = 0; j < dia.ldiag; j++){
            fprintf(file, "%lf ", dia.val_dia[i*dia.ldiag+j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
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

void dia_to_st_run(){
    dia_fmt dia;
    dia_read("input.txt", &dia);
    st_fmt st;
    dia_to_st(dia, &st);
    // printf("%d \n", st.n_val);
    dia_write("output.txt", dia);
    st_write("output.txt", st);
}