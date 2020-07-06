#include<stdio.h>
#include<stdlib.h>

/*
double* eData, ELL存值的二维数组
int* offset,  ELL存列下标的二维数组
int n_row,  ELL总行数
int n_max,      ELL各列中，非零元个数的最大值
int* ist,   
int* jst, 
double* ast
返回值：非零元个数
*/

int ell_to_st(double **eData, int **offset, int n_row, int n_max, int** ist, int** jst, double** ast){
    int* i_st = (int*)malloc(sizeof(int) * n_row * n_max);
    int* j_st = (int*)malloc(sizeof(int) * n_row * n_max);
    double* a_st = (double*)malloc(sizeof(double) * n_row * n_max);
    int index = 0;
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < n_max; j++){
            if(*((int*)offset + i * n_max + j) == -1)
                break;
            i_st[index] = i;
            j_st[index] = *((int*)offset + i * n_max + j);
            a_st[index] = *((double*)eData + i * n_max + j);
            index++;
        }
    }
    *ist = i_st;
    *jst = j_st;
    *ast = a_st;
    return index;
}

void st_to_hyb(int* ist, int* jst, double* ast, int n_val, int n_row, 
        int n_col, int max, double*** eData, int*** offset, 
        int** e_ist, int** e_jst, double**e_ast, int* e_n_val){
// void st_to_hyb(int* ist, int* jst, double* ast, int n_val, int n_row, int max){
    double** e_Data = (double**)malloc(sizeof(double)*n_row*max);
    int** e_offset = (int**)malloc(sizeof(int)*n_row*max);
    *e_ist = (int*)malloc(sizeof(int)*(n_col-max));
    *e_jst = (int*)malloc(sizeof(int)*(n_col-max));
    *e_ast = (double*)malloc(sizeof(double)*(n_col-max));
    int cnt = 0;  //统计每行非零元个数
    int index = -1;
    int j_index = 0;
    int e_index = 0;
    *e_n_val = 0;
    for(int i = 0; i < n_val; i++){
        if(index == ist[i])
            cnt++;
        else{
            index = ist[i];
            cnt = 1;
            j_index = 0;
        }
        if(cnt <= max){
            *((int*)e_offset+ist[i]*max+j_index) = jst[i];
            *((double*)e_Data+ist[i]*max+j_index) = ast[i];
            j_index++;
        }
        else{
            *e_ist[*e_n_val] = ist[i];
            *e_jst[*e_n_val] = jst[i];
            *e_ast[*e_n_val] = ast[i];
            *e_n_val++;
        }
    }

    *eData = e_Data;
    *offset = e_offset;

    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < max; j++){
            printf("%d\t", *((int*)e_offset+i*max+j));
        }
        printf(("\n"));
    }
    printf("\n");
    for(int i = 0; i < n_row; i++){
        for(int j = 0; j < max; j++){
            printf("%lf\t", *((double*)e_Data+i*max+j));
        }
        printf(("\n"));
    }
    for(int i = 0; i < *e_n_val; i++){
        printf("%d\t%d\t%lf\n", *e_ist[i],*e_jst[i],*e_ast[i]);
    }

}



int main(){
    int offset[4][3] = {0,1,-1,1,2,-1,0,2,3,1,3,-1};
    double eData[4][3] = {1,7,0,2,8,0,5,3,9,6,4,0};
    int n_row = 4;
    int n_max = 3;
    int* ist; 
    int* jst;
    double* ast;
    int n_val = ell_to_st((double**)eData, (int**)offset, n_row, n_max, &ist, &jst, &ast);
    for(int i = 0; i < n_val; i++){
        printf("%d\t%d\t%lf\n", ist[i], jst[i], ast[i]);
    }

    // int ist[9] = {0,0,1,1,2,2,2,3,3};
    // int jst[9] = {0,1,1,2,0,2,3,1,3};
    // double ast[9] = {1,7,2,8,5,3,9,6,4};
    // int n_val = 9;
    // int n_row = 4;
    // int n_col = 4;
    // int max = 2; 
    // double** eData;
    // double** offset; 
    // int* e_ist;
    // int* e_jst; 
    // double*e_ast; 
    // int e_n_val;
    // st_to_hyb(ist, jst, ast, n_val, n_row, n_col, max, eData, offset, &e_ist, &e_jst, &e_ast, &e_n_val);

}