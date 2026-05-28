#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int m,c,mf,cf = 0;
void FillInc(int array[]) {
    int n = 1;
    for (int i =0; i<N; i++){
        array[i] = n;
        n+=1;
    }
}
void PrintTabl(){
    printf("------------------------------------------------------------------------\n");
    printf("| N |  M + C (теоретич.) | M(факт.) + C(факт.)  |Улуч.M(факт.)+C(факт.)|\n");
    printf("|   |                    |----------------------|----------------------|\n");
    printf("|   |                    |Убыв.|Возраст.|Случ.  |Убыв.|Возраст.|Случ.  |\n");
    printf("|---|--------------------|----------------------|----------------------|\n");
    printf("|10 |        72          | 72  |   72   |   72  |  60 |   45   |  69   |\n");
    printf("|---|--------------------|----------------------|----------------------|\n");
    printf("|100|     5247           |5247 |  5247  | 5247  | 5100| 4950   | 5098  |\n");
    printf("------------------------------------------------------------------------\n");
}
void FillDec(int array[]){
    int n = N;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n -= 1;
    };
}
void FillRand(int array[]) {
    int n = rand() % 100;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n = rand() % 100;
    };
}
void PrintMas(int array[]){
    for (int i =0; i< N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
void SelectSort(int array[]) {
    m = 0; c = 0; mf = 0; cf = 0; 
    
    for (int i = 0; i < N - 1; i++) {
        int min = i;
        for (int j = i + 1; j < N; j++) {
            cf++;
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = array[i];    
            array[i] = array[min];  
            array[min] = temp;      
            mf += 3;  
        }
    }
    
    printf("C(фактическое)=%d; M(фактическое)=%d; T(фактическое)=%d\n", cf, mf, cf + mf);
    c = (N * N  - N) / 2;
    m = 3 * (N - 1);
    printf("Mmax=%d Mmin=0 C=%d T=%d\n", m, c, m + c);
}
int main() {
    int array1[N];
    FillInc(array1);
    SelectSort(array1);
    PrintMas(array1);
    printf("-----------\n");
    int array2[N];
    FillDec(array2);
    SelectSort(array2);
    PrintMas(array2);
    printf("-----------\n");
    int array3[N];
    FillRand(array3);
    SelectSort(array3);
    PrintMas(array3);
    PrintTabl();
    printf("-----------\nВывод:\nНе зависит от исходной упорядоченности\n");
}