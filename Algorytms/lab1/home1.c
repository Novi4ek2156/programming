#include <stdio.h>
#include <stdlib.h>
int cf, mf, m, c = 0;
int N;
int SizeArrayTen() {
    N = 10;
    int array[N];
    return N;
}
int SizeArrayhundred() {
    N = 100;
    int array[N];
    return N;
}
void FillInc(int array[]) {
    int n = 1;
    for (int i =0; i<N; i++){
        array[i] = n;
        n+=1;
    }
}
void FillDec(int array[]){
    int n = N;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n -= 1;
    };
}

void RunNumber(int array[]) {
    int seria = 0;
    for (int i =0; i < N;i++ ) {
        if (array[i] < array[i-1]) {
            seria++;
        }
    }
    printf("Seria = %d\n", seria);
}
void PrintMas(int array[]){
    for (int i =0; i< N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
void PrintTabl(){
    printf("------------------------------------------------------------------------\n");
    printf("| N |  M + C (теоретич.) | M(факт.) + C(факт.)  |Улуч.M(факт.)+C(факт.)|\n");
    printf("|   |                    |----------------------|----------------------|\n");
    printf("|   |                    |Убыв.|Возраст.|Случ.  |Убыв.|Возраст.|Случ.  |\n");
    printf("|---|--------------------|----------------------|----------------------|\n");
    printf("|10 |        72          | 72  |   72   |   72  |  72 |   45   |  69   |\n");
    printf("|---|--------------------|----------------------|----------------------|\n");
    printf("|100|     5247           |5247 |  5247  | 5247  | 5247| 4950   | 5098  |\n");
    printf("------------------------------------------------------------------------\n");
}
void FillRand(int array[]) {
    int n = rand() % 100;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n = rand() % 100;
    };
}
void SelectSort(int array[]) {
    m,c, mf, cf = 0;
    for (int i = 0; i < N - 1; i++) {
        int k = i;
        int term;
        for (int j = i + 1; j < N; j++ ) {
            cf++;
            if (array[j] < array[k]) {
                k = j;
            }   
            
        }
        
        if (i != k) {
            mf+=3;
            term = array[i];
            array[i] = array[k];
            array[k] = term;
        }
    }
    printf("C(фактическое)=%d; M(фактическое)=%d; T(фактическое)=%d\n", cf, mf, cf + mf);
    c = (N*N - N)/2;
    m = 3*(N-1);
    printf("Mmax=%d Mmin = 0 C=%d T=%d\n", m, c, m + c);
}
int main() {
    int array1[8] = {'с', 'е', 'м', 'ё', 'н', 'о', 'в', 'в'};
    SelectSort(array1);
    PrintMas(array1);
    PrintTabl();
}