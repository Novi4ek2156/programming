#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cf, mf;
void FillInc(int array[], int size) {
    int n = 1;
    for (int i =0; i < size; i++){
        array[i] = n;
        n++;
    }
}
void FillDec(int array[], int size) {
    int n = size;
    for (int i =0; i <size; i++) {
        array[i] = n;
        n--;
    }
}
void FillRand(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int random = rand()%999;
        array[i] = random;
    }
}
int ShellSort(int array[], int size) {
    int k, i, j, temp;
    cf = 0, mf = 0;
    int hm =1;
    while (hm < size) {
        hm = 2*hm + 1;
    }
    hm = (hm-1)/2;
    for (int k=hm;k>=1; k = (k-1)/2) {
        for (int i= k; i < size; i++) {
            int temp = array[i];
            int j = i-k;
            while ((j >= 0) && (temp < array[j])) {
                cf+=2;
                mf++;
                array[j+k] = array[j];
                j = j-k;
            }
            mf++;
            array[j+k] = temp;
        }
    }    
    return cf, mf;
}
int ShellSort_Classic(int array[], int size) {
    int k, i, j, temp;
    cf = 0, mf = 0;
    int hm =size /2;
    for (int k=hm;k>=1; k = k/2) {
        for (int i= k; i < size; i++) {
            int temp = array[i];
            int j = i-k;
            while ((j >= 0) && (temp < array[j])) {
                cf+=2;
                mf++;
                array[j+k] = array[j];
                j = j-k;
            }
            mf++;
            array[j+k] = temp;
        }
    }    
    return cf, mf;
}
void PrintMas(int arr[], int size){
    for (int i= 0; i< size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main() {
    srand(time(NULL));
    int array[100];
    int arr[100];
    FillRand(array, 100);
    for (int i = 0; i < 100; i++) {
        arr[i] = array[i];
    }
    ShellSort(array, 100);
    int tf1 = cf+mf;
    printf("--------------------------------------------------\n");
    printf("|n  | h1 … hm по ф-е Д.Кнута| Insert Tf| Shell Tf|\n");
    printf("--------------------------------------------------\n");
    printf("|100|     1,3,7,15,31       |   5351   |   %d  |\n", tf1);
    int array2[200];
    int arr2[200];
    FillRand(array2, 200);
    for (int i = 0; i < 200; i++) {
        arr2[i] = array2[i];
    }
    ShellSort(array2, 200);
    int tf2 = cf+mf;
    printf("|200|   1,3,7,15,31,63      |   20770  |   %d  |\n", tf2);
    int array3[300];
    int arr3[300];
    FillRand(array3, 300);
    for (int i = 0; i < 300; i++) {
        arr3[i] = array3[i];
    }
    ShellSort(array3, 300);
    int tf3 = cf+mf;
    printf("|300|1,3,7,15,31,63,127     |   45992  |   %d  |\n", tf3);
    int array4[400];
    int arr4[400];
    FillRand(array4, 400);
    for (int i = 0; i < 400; i++) {
        arr4[i] = array4[i];
    }
    ShellSort(array4, 400);
    int tf4 = cf +mf;
    printf("|400|1,3,7,15,31,63,127     |   81850  |  %d   |\n", tf4);
    int array5[500];
    int arr5[500];
    FillRand(array5, 500);
    for (int i = 0; i < 500; i++) {
        arr5[i] = array5[i];
    }
    ShellSort(array5, 500);
    int tf5 = cf + mf;
    printf("|500|1,3,7,15,31,63,127     |  126334  |  %d  |\n", tf5);
    printf("--------------------------------------------------\n");
    ShellSort_Classic(arr, 100);
    int t1 = cf + mf;
    ShellSort_Classic(arr2, 200);
    int t2 = cf + mf;
    ShellSort_Classic(arr3, 300);
    int t3 = cf + mf;
    ShellSort_Classic(arr4, 400);
    int t4 = cf + mf;
    ShellSort_Classic(arr5, 500);
    int t5 = cf + mf;
    printf("---------------------------------------------------------------------\n");
    printf("|n  | h1 … hm по ф-е Д.Кнута|Shell Tf|h1 … hm по кл. ф-е   |Shell Tf|\n");
    printf("---------------------------------------------------------------------\n");
    printf("|100|     1,3,7,15,31       |   %d |   1,3,6,12,25,50     |  %d |\n", tf1, t1);
    printf("|200|  1,3,7,15,31,63       |   %d | 1,3,6,12,25,50,100   |  %d |\n", tf2, t2);
    printf("|300|1,3,7,15,31,63,127     |   %d |1,2,4,9,18,37,75,150  |  %d |\n", tf3, t3);
    printf("|400|1,3,7,15,31,63,127     |  %d  |1,3,6,12,25,50,100,200| %d |\n", tf4, t4);
    printf("|500|1,3,7,15,31,63,127     |  %d |1,3,7,15,31,62,125,250| %d |\n", tf5, t5);
    printf("---------------------------------------------------------------------\n");
}
