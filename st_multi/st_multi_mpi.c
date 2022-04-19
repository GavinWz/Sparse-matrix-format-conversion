#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct st{
    int *ist;   //行偏移数组
    int *jst;   //列偏移数组
    double *ast; //非零元数组
    int n_row;
    int n_col;
    int n_val;  //非零元个数
} st_fmt;

clock_t st_read(char* filename, st_fmt* st, int* n_row, int* n_col){
    clock_t begin = clock();
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open the input file.\n");
        return -1;
    }
    int n_val;
    fscanf(file, "%d%d%d", &(*n_row), &(*n_col), &n_val);
    
    st->ast = (double*)malloc(sizeof(double) * n_val);
    st->ist = (int*)malloc(sizeof(int) * n_val);
    st->jst = (int*)malloc(sizeof(int) * n_val);
    
    int index = 0;
    while(feof(file) == 0){
        fscanf(file, "%d%d%lf", &(st->ist[index]), &(st->jst[index]), &(st->ast[index]));
        index++;
    }
    
    st->n_val = n_val;
    fclose(file);
    clock_t end = clock();
    return end - begin;
}

int exists(st_fmt st, int row, int col){
    if(!st.ist)
        return -1;
    for(int i = 0; i < st.n_val; i++){
        if(st.ist[i] == row && st.jst[i] == col)
            return i;
    }
    return -1;
}

void new_a_place(st_fmt *st){
    if(st->n_val == 0){
        st->ist = (int*)malloc(sizeof(int));
        st->jst = (int*)malloc(sizeof(int));
        st->ast = (double*)malloc(sizeof(double));    
        st->ist[0] = -1;
        st->jst[0] = -1;
        st->ast[0] = 0;
        st->n_val = 1;
    }
    else{
        st->ist = (int*)realloc(st->ist, sizeof(int) * (st->n_val + 1));
        st->jst = (int*)realloc(st->jst, sizeof(int) * (st->n_val + 1));
        st->ast = (double*)realloc(st->ast, sizeof(double) * (st->n_val + 1));
        st->ist[st->n_val] = -1;
        st->jst[st->n_val] = -1;
        st->ast[st->n_val] = 0;
        st->n_val++;
    }
}

void multi(st_fmt m1, st_fmt m2, st_fmt *result){
    clock_t start = clock();
    new_a_place(result);
    //若矩阵全0，或者m1的行数不等于m2的列数，则退出
    if(m1.n_val == 0 || m2.n_val == 0 || m1.n_row != m2.n_col){
        return;
    }

    //初始化result矩阵
    result->n_row = m1.n_row;
    result->n_col = m2.n_col;
    result->n_val = 0;
    
    //乘法运算
    //外层交给MPI（待实现）
    #pragma omp parallel for
    for(int i = 0; i < m1.n_val; i++){  //外层遍历m1
        //内层交给OpenMP
        // #pragma omp parallel for
        for(int j = 0; j < m2.n_val; j++){  //内层遍历m2
            if(m1.jst[i] == m2.ist[j]){  //当m1列号 = m2行号时，运算有效
                int index = exists(*result, m1.ist[i], m2.jst[j]);
                if(index == -1){   //每当对应的行列号第一次出现时，为结果矩阵开辟一个空间
                    #pragma omp critical  //该函数中涉及n_val的更新和空间分配，需同步访问
                        new_a_place(result);
                    result->ist[result->n_val-1] = m1.ist[i];  //新增的项的行号为m1的行号
                    result->jst[result->n_val-1] = m2.jst[j];  //列号为m2的列号
                    result->ast[result->n_val-1] += m1.ast[i] * m2.ast[j];  //初始化该行列对应元素值为第此遍历到的两值相乘
                }
                else{
                    result->ast[index] += m1.ast[i] * m2.ast[j];  //若该行列已经存在，则更新其值
                }
            }
        }
    }
    clock_t end = clock();
    printf("%d\n", end - start);
    return;
}
int main(){
    st_fmt st, result;
    int n_row, n_col;
    st_read("./data.txt", &st, &n_row, &n_col);
    st.n_row = 5;
    st.n_col = 5;
    multi(st, st, &result);
    // for(int i = 0; i < result.n_val; i++){
    //     printf("%d %d %lf \n", result.ist[i], result.jst[i], result.ast[i]);
    // }
}