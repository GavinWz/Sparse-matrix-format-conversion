#include<stdio.h>
#include<stdlib.h>

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

// int st_read(char* filename,double **ast,int **ist, int **jst){
void st_read(char* filename, st_fmt* st){
    (*st).ast = (double*)malloc(sizeof(double) * 10);
    (*st).ist = (int*)malloc(sizeof(int) * 10);
    (*st).jst = (int*)malloc(sizeof(int) * 10);
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &((*st).ist[index]), &((*st).jst[index]), &((*st).ast[index]));
        index++;
    }
    (*st).n_val = index;
    fclose(file);
}

void hyb_write(char* filename, hyb_fmt hyb, int n_row){
    FILE *file = fopen(filename, "w+");
    if(file == NULL){
        printf("Can't open the file.\n");
        return;
    }
    fprintf(file, "The final HYB format martrix: \n");

    fprintf(file, "\nELL Column indices: \n");
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < hyb.max; j++){
            fprintf(file, "%-10d", *((int*)hyb.offset+i*hyb.max+j));
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nELL Values: \n");
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < hyb.max; j++){
            fprintf(file, "%-10.4lf", *((double*)hyb.eData+i*hyb.max+j));
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nST Martrix: \n");
    fprintf(file, "i         j         v         \n");
    fprintf(file, "------------------------------\n");
    for(int i = 0; i < hyb.n_val; i++){
        fprintf(file, "%-10d%-10d%-10.4lf\n", hyb.ist[i],hyb.jst[i],hyb.ast[i]);
    }
    fclose(file);
}

void st_to_hyb(st_fmt st, hyb_fmt* hyb, int n_row, int n_col){
    (*hyb).ist = (int*)malloc(sizeof(int) * (n_col - (*hyb).max));
    (*hyb).jst = (int*)malloc(sizeof(int) * (n_col - (*hyb).max));
    (*hyb).ast = (double*)malloc(sizeof(double) * (n_col - (*hyb).max));
    (*hyb).eData = (double**)malloc(sizeof(double) * n_row * (*hyb).max);
    (*hyb).offset = (int**)malloc(sizeof(int) * n_row * (*hyb).max);

    int cnt = 0;
    int index = -1;
    int j_index = 0;
    int e_index = 0;
    (*hyb).n_val = 0;

    for(int i = 0; i < st.n_val; i++){
        if(index == st.ist[i])
            cnt++;
        else{
            index = st.ist[i];
            cnt = 1;
            j_index = 0;
        }
        if(cnt <= (*hyb).max){
            *((int*)(*hyb).offset+st.ist[i]*(*hyb).max+j_index) = st.jst[i];
            *((double*)(*hyb).eData+st.ist[i]*(*hyb).max+j_index) = st.ast[i];
            j_index++;
        }
        else{
            (*hyb).ist[(*hyb).n_val] = st.ist[i];
            (*hyb).jst[(*hyb).n_val] = st.jst[i];
            (*hyb).ast[(*hyb).n_val] = st.ast[i];
            (*hyb).n_val++;
        }
    }

}
void test_read(){
    st_fmt st;
    st_read("test.txt", &st);
    for(int i = 0; i < st.n_val; i++){
        printf("%d\t%d\t%lf\n", st.ist[i],st.jst[i],st.ast[i]);
    }
    printf("%d", st.n_val);
}


int main(){
    st_fmt st;
    int ist[9] = {0,0,1,1,2,2,2,3,3};
    int jst[9] = {0,1,1,2,0,2,3,1,3};
    double ast[9] = {1,7,2,8,5,3,9,6,4};
    st.ist = ist;
    st.jst = jst;
    st.ast = ast;
    st.n_val = 9;

    int n_row = 4;
    int n_col = 4;

    hyb_fmt hyb;
    hyb.max = 2;

    st_to_hyb(st, &hyb, n_row, n_row);
    hyb_write("output.txt", hyb, n_row);

    // for(int i = 0; i < n_row; i++){
    //     for(int j = 0; j < hyb.max; j++){
    //         printf("%d\t", *((int*)hyb.offset+i*hyb.max+j));
    //     }
    //     printf(("\n"));
    // }
    // printf("\n");
    // for(int i = 0; i < n_row; i++){
    //     for(int j = 0; j < hyb.max; j++){
    //         printf("%lf\t", *((double*)hyb.eData+i*hyb.max+j));
    //     }
    //     printf(("\n"));
    // }
    // for(int i = 0; i < hyb.n_val; i++){
    //     printf("%d\t%d\t%lf\n", hyb.ist[i],hyb.jst[i],hyb.ast[i]);
    // }
    // test_read();
}   

