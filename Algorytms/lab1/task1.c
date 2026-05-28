#include <stdio.h>
#include <stdlib.h>
//#include <random.h>
#define N 10
void FillInc(int array[]) {
    int n = 1;
    for (int i =0; i<N; i++){
        array[i] = n;
        n+=1;
    }
}
void FillDec(int array[]){
    int n = 10;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n -= 1;
    };
}
void FillRand(int array[]) {
    int n = rand() % 1000;
    for (int i = 0; i < N; i++) {
        array[i]= n;
        n = rand() % 1000;
    };
}







void CheckSum(int array[]){
    int sum = 0;
    for (int i=0; i < N; i++) {
        sum += array[i];
    }  
    printf("Summa = %d\n", sum);
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
}
void end_task(int array[]) {
    int seria = 0;
    int kol_vo = 1000;
    int chet = 0;
    while (kol_vo > 0){ 
        int n = rand() %100;
        for (int i = 0; i < N; i++) {
            array[i]= n;
            n = rand() % 100;
        };
        for (int i =0; i < N;i++ ) {
            if (array[i] < array[i-1]) {
                seria++;
            }
        }
        printf("Seria[%d]= %d\n", kol_vo, seria);
        chet+=seria;
        kol_vo -= 1;
    }
    int resultat = chet % 1000;
    printf("Средняя длина серии:%d", resultat);
}


int main() {
    int array[N] = {};
    FillInc(array);
    PrintMas(array);
    CheckSum(array);
    RunNumber(array);
    printf("-----------------------------------\n");
    FillDec(array);
    PrintMas(array);
    CheckSum(array);
    RunNumber(array);
    printf("-----------------------------------\n");
    FillRand(array);
    PrintMas(array);
    CheckSum(array);
    RunNumber(array);
    printf("-----------------------------------\n");
    end_task(array);

}