#include <stdio.h>
#include <stdlib.h>


int main() {
    int n;
    printf("Enter size matrix: "); // размер матрицы
    scanf("%d", &n);
    printf("**********************\n");
    int matrix[n][n]; // заполнение элементов матрицы
    for (int i = 0; i < n; i++) {
        int a = 0;
        int chet_otric_zn = 0;
        for (int j = 0; j < n; j++) {
            printf("Enter a[%d][%d] = ", i, j);
            scanf("%d", &a);
            matrix[i][j] = a;
        }
    }
    printf("**********************\n"); //проверка элементов матрицы
    int dioganal[n];
    int chet_zn = 0;
    int stroka_otric = 0;
    for (int i = 0; i < n; i++) {
        int chet =0;
        for (int j = 0; j <n; j++) {
            printf("Matrix[%d][%d]= %d\n", i, j, matrix[i][j]);
            dioganal[i]= matrix[i][n-i-1];
            if (matrix[i][j]< 0) {
                ++chet;
                if (chet > chet_zn)
                {
                    chet_zn = chet;
                    stroka_otric= i;
                }
                
            }
        }
        
        printf("\n");
    }
    printf("**********************\n"); // заполнение матрицы с суммой элементов строк
    int term[n];
    int sum = 0;
    for (int i = 0; i <n; i++) {
        sum = 0;
        for (int j = 0;j<n;j++) {
            sum+= matrix[i][j];
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
                matrix_2[i][j]=matrix[i][j] + dioganal[i];
            }   
            else {
                matrix_2[i][j] = matrix[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) { // проход по значениям новой матрицы
        for (int j = 0; j <n; j++) {
            printf("Matrix_2[%d][%d]= %d\n", i, j, matrix_2[i][j]);
        }
        
        printf("\n");
    }
    printf("**********************\n");
    printf("Больше всего отрицательных значений в строке: %d\n", stroka_otric);
}