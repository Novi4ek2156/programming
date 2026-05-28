#include <stdio.h>
#include <stdlib.h>
#define N 10
int m,c,mf,cf = 0;
void FillDec(int array[]) {
    int n = N;
    for (int i =0; i<N; i++){
        array[i] = n;
        n-=1;
    }
}
void PrintMas(int array[]){
    for (int i =0; i< N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
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
        mf+=3;
        term = array[i];
        array[i] = array[k];
        array[k] = term;
        
    }
    printf("C(фактическое)=%d; M(фактическое)=%d; T(фактическое)=%d\n", cf, mf, cf + mf);
    c = (N*N - N)/2;
    m = 3*(N-1);
    printf("Mmax=%d Mmin = 0 C=%d T=%d\n", m, c, m + c);
}
int main() {
    int array1[N];
    FillDec(array1);
    PrintMas(array1);
    SelectSort(array1);
    PrintMas(array1);
}