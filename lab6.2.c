#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    int x = 0;
    int y = 0;
    printf("Enter size of matrix: ");
    scanf("%d", &n);
    int matrix[n][n];
    printf("Elements matrix\n");
    for (int i = 0; i <n; i++) {
        for (int j =0; j<n;j++) {
            int a;
            matrix[i][j] = 0;
            printf("Enter a[%d][%d]: ", i, j);
            scanf("%d", &a);
            matrix[i][j]+=a;
        }
    }
    float b[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = 0;
        printf("Enter b: ");
        scanf("%f", &b[i]);
    
    }
    for (int i = 0; i < n; i++) {
        for  (int j = 0; j < n; j++) {
            printf("a[%d][%d] = %d\n", i, j, matrix[i][j]);
            }

        }
    printf("\n");
    
    if (n == 2) {
        float x = 0;
        float y = 0;
        float opred = 0;
        opred= matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
        if (opred=0) {
            printf("Нет единственного решения.");
        }
        else {
        x = b[0]*matrix[1][1]- b[1]*matrix[0][1];
        y = b[1]*matrix[0][0] - b[0]*matrix[1][0];
        printf("x= %.1f\n y= %.1f\n", x/opred, y/opred);
        }
    }
    if (n == 3) {
        float x = 0;
        float y = 0;
        float z = 0;
        float opred = 0;
        opred = matrix[0][0]*(matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1])
            -matrix[0][1]*(matrix[1][0]*matrix[2][2]-matrix[2][0]*matrix[1][2])
            +matrix[0][2]*(matrix[1][0]*matrix[2][1]-matrix[2][0]*matrix[1][1]);
        if (opred == 0) {
            printf("Нет единственного решения.\n");
        }
        else if (opred > 0){
        x = b[0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
                        - matrix[0][1] * (b[1] * matrix[2][2] - matrix[1][2] * b[2])
                        + matrix[0][2] * (b[1] * matrix[2][1] - matrix[1][1] * b[2]);
        y = matrix[0][0] * (b[1] * matrix[2][2] - matrix[1][2] * b[2])
                        - b[0] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
                        + matrix[0][2] * (matrix[1][0] * b[2] - b[1] * matrix[2][0]);    
        z = matrix[0][0] * (matrix[1][1] * b[2] - b[1] * matrix[2][1])
                        - matrix[0][1] * (matrix[1][0] * b[2] - b[1] * matrix[2][0])
                        + b[0] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        printf("x = %.1f\n y = %.1f\n z = %.1f\n", x/opred, y/opred, z/opred);
        }
    
    
    }


}
















