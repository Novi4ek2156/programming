#include <stdio.h>
#include <stdlib.h>

void print_array(int **arr, int n) {
    printf("Matrix %d x %d\n", n, n);
    int chet = 0;
    int chet_zn = 0;
    int stroka_otric = 0;
    for (int i = 0; i < n; i++) {
        chet= 0;
        for (int j = 0; j < n; j++) {        
            printf("%d ", arr[i][j]);
            if (arr[i][j]< 0) {
                ++chet;
                if (chet > chet_zn)
                {
                    chet_zn = chet;
                    stroka_otric = i;
                }
                
            }
        }
        printf("\n");
    }
    printf("***************************\nБольше всего отрицательных элементов в строке: %d\n",stroka_otric);
}
void new_matrix(int **arr, int n, int diagonal[]) {
    int term[n];
    int sum = 0;
    for (int i = 0; i <n; i++) {
        sum = 0;
        for (int j = 0;j<n;j++) {
            sum+= arr[i][j];
        }
        term[i] = sum;
    }
    for (int i = 0; i < n; i++) { // проверка элементов
        for (int j = 0; j <1; j++) {
            printf("Summa elements in stroke[%d][%d]= %d\n", i, j, term[i]);
        }
    }   
    printf("**********************\n");// увеличение элементов матрицы на элемент побочной диагонали
    int matrix_2[n][n];
    for (int i = 0; i <n;i++) {
        for (int j = 0; j <n; j++) {
            if (term[i] < 15) {
                matrix_2[i][j]=arr[i][j] + diagonal[i];
            }   
            else {
                matrix_2[i][j] = arr[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) { // проход по значениям новой матрицы
        for (int j = 0; j <n; j++) {
            printf("New_matrix[%d][%d] = %d\n", i ,j,matrix_2[i][j]);
        }
        printf("\n");
    }
    printf("**********************\n");

}
int main() {
    int n =0;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    int **arr = malloc(n * sizeof(*arr));
    if (arr == NULL) { return -1;}
    int diagonal[n];
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(**arr));
        int a= 0;
        if (arr[i] == NULL) { printf("ERROR"); }
        for (int j = 0; j < n; j++) {
            printf("Введите а[%d][%d]: ", i, j);
            scanf("%d", &a);
            arr[i][j] = a; 
            diagonal[i] = arr[i][n-i-1];
        }
    }
    printf("***************************\n");
    print_array(arr, n);
    printf("\n");
    printf("***************************\n");
    new_matrix(arr, n, diagonal);   
    for (int i = 0; i < n; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
    return 0;

}