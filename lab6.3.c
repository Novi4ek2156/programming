#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int opredelitel(int matrix[3][3], int n) {
    int opred_3x3;
    opred_3x3 = matrix[0][0]*(matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1])
            -matrix[0][1]*(matrix[1][0]*matrix[2][2]-matrix[2][0]*matrix[1][2])
            +matrix[0][2]*(matrix[1][0]*matrix[2][1]-matrix[2][0]*matrix[1][1]);
    return opred_3x3;
}

int main() {
    int n;
    printf("Enter size matrix: ");
    scanf("%d", &n);
    int matrix[n][n];
    //внесение значений в матрицу
    for (int i =0;i< n;i++) {
        
        for (int j = 0; j <n;j++) {
            matrix[i][j] =0;
            int a;
            printf("Enter a[%d][%d] = ", i, j);
            scanf("%d", &a);
            matrix[i][j] = a;
        }
    }
    float b[n];     //значения ур-я
    for (int i = 0; i < n; i++)
    {
        b[i] = 0;
        printf("Enter b: ");
        scanf("%f", &b[i]);
    }
    //проверка значений
    for (int i =0; i<n; i++) {
        for (int j =0; j<n;j++) {
            printf("a[%d][%d] = %d\n", i,j, matrix[i][j]);
        }
    
    }
    if (n == 4) {
        float x = 0;
        float y = 0;
        float opred = 0;
        
        printf("Opred = %f\nx=%f", opred, x);

    }
}