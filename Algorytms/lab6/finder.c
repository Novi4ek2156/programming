#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int cf = 0;
void FillInc(int array[], int size) {
    for (int i =0; i < size; i++) {
        array[i] = i+1;
    }
}
void PrintMassive(int arr[], int size){
    for (int i =0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int Finder1(int arr[], int size, int x) {
    int L = 0;
    cf =0;
    int R = size -1;
    bool Y = false;
    while (L <= R) {
        int m = (L + R) / 2;
        cf +=2;
        if (arr[m] == x) {
            Y = true;
        }
        if (arr[m] < x) {
            L = m +1;
        } else {
            R = m-1;
        }
    }
    cf++;
    if (Y == true) {

        return cf;
    } else {

        return cf;
    }
}
int Finder1_All(int arr[], int size) {
    int L = 0;
    cf =0;
    int R = size -1;
    bool Y = false;
    for (int i =1; i < size; i++) {
        Finder1(arr, size, i);
        cf += cf;
    }
    return cf;
}

int Finder2(int array[], int size, int x) {
    int L = 0;
    cf = 0;
    int R = size -1;
    while (L < R) {
        int m = (L + R)/2;
        cf++;
        if (array[m] < x) {
            L = m +1;
        } else { 
            R = m;
        }
    }
    cf++;
    if (array[R] == x) {
            return cf;
        } else {
            return cf;
        }
}
int Finder2_All(int arr[], int size) {
    int L = 0;
    cf =0;
    int R = size -1;
    bool Y = false;
    for (int i =1; i < size; i++) {
        Finder2(arr, size, i);
        cf += cf;
    }
    return cf;
}
int main() {
    int arr1[100];
    int x;
    FillInc(arr1, 100);
    printf("Введите желаемый элемент массива:");
    scanf("%d", &x);
    Finder1(arr1, 100, x);
    int t1_1 = cf;
    Finder2(arr1, 100, x);
    int t2_1 = cf;
    printf("----------------------------------\n");
    printf("| N |     Cf1     |      Cf2     |\n");
    printf("----------------------------------\n");
    printf("|100|      %d     |      %d       |\n", t1_1, t2_1);
    int arr2[200];
    FillInc(arr2, 200);
    Finder1(arr2, 200, x);
    int t1_2 = cf;
    Finder2(arr2, 200, x);
    int t2_2 = cf;
    printf("|200|      %d     |      %d       |\n", t1_2, t2_2);
    int arr3[300];
    FillInc(arr3, 300);
    Finder1(arr3, 300, x);
    int t1_3 = cf;
    Finder2(arr3, 300, x);
    int t2_3 = cf;
    printf("|300|      %d     |      %d       |\n", t1_3, t2_3);
    int arr4[400];
    FillInc(arr4, 400);
    Finder1(arr4, 400, x);
    int t1_4 = cf;
    Finder2(arr4, 400, x);
    int t2_4 = cf;
    printf("|400|      %d     |      %d       |\n", t1_4, t2_4);
    int arr5[500];
    FillInc(arr5, 500);
    Finder1(arr5, 500, x);
    int t1_5 = cf;
    Finder2(arr5, 500, x);
    int t2_5 = cf;
    printf("|500|      %d     |      %d       |\n", t1_5, t2_5);
    int arr6[600];
    FillInc(arr6, 600);
    Finder1(arr6, 600, x);
    int t1_6 = cf;
    Finder2(arr6, 600, x);
    int t2_6 = cf;
    printf("|600|      %d     |      %d       |\n", t1_6, t2_6);
    int arr7[700];
    FillInc(arr7, 700);
    Finder1(arr7, 700, x);
    int t1_7 = cf;
    Finder2(arr7, 700, x);
    int t2_7 = cf;
    printf("|700|      %d     |      %d       |\n", t1_7, t2_7);
    int arr8[800];
    FillInc(arr8, 800);
    Finder1(arr8, 800, x);
    int t1_8 = cf;
    Finder2(arr8, 800, x);
    int t2_8 = cf;
    printf("|800|      %d     |      %d       |\n", t1_8, t2_8);
    int arr9[900];
    FillInc(arr9, 900);
    Finder1(arr9, 900, x);
    int t1_9 = cf;
    Finder2(arr9, 900, x);
    int t2_9 = cf;
    printf("|900|      %d     |      %d       |\n", t1_9, t2_9);
    int arr10[1000];
    FillInc(arr10, 1000);
    Finder1(arr10, 1000, x);
    int t1_10 = cf;
    Finder2(arr10, 1000, x);
    int t2_10 = cf;
    printf("|1000|      %d     |      %d       |\n", t1_10, t2_10);
    printf("------------------------------------\n");
    printf("All\n");
    Finder1_All(arr1, 100);
    int t1_a1 = cf;
    Finder2_All(arr1, 100);
    int t2_a1 = cf;
    printf("----------------------------------\n");
    printf("| N |     Cf1     |      Cf2     |\n");
    printf("----------------------------------\n");
    printf("|100|      %d     |      %d       |\n", t1_a1, t2_a1);
    Finder1_All(arr2, 200);
    int t1_a2 = cf;
    Finder2_All(arr2, 200);
    int t2_a2 = cf;
    printf("|200|      %d     |      %d       |\n", t1_a2, t2_a2);
    Finder1_All(arr3, 300);
    int t1_a3 = cf;
    Finder2_All(arr3, 300);
    int t2_a3 = cf;
    printf("|300|      %d     |      %d       |\n", t1_a3, t2_a3);
    Finder1_All(arr4, 400);
    int t1_a4 = cf;
    Finder2_All(arr4, 400);
    int t2_a4 = cf;
    printf("|400|      %d     |      %d       |\n", t1_a4, t2_a4);
    Finder1_All(arr5, 500);
    int t1_a5 = cf;
    Finder2_All(arr5, 500);
    int t2_a5 = cf;
    printf("|500|      %d     |      %d       |\n", t1_a5, t2_a5);
    Finder1_All(arr6, 600);
    int t1_a6 = cf;
    Finder2_All(arr6, 600);
    int t2_a6 = cf;
    printf("|600|      %d     |      %d       |\n", t1_a6, t2_a6);
    Finder1_All(arr7, 700);
    int t1_a7 = cf;
    Finder2_All(arr7, 700);
    int t2_a7 = cf;
    printf("|700|      %d     |      %d       |\n", t1_a7, t2_a7);
    Finder1_All(arr8, 800);
    int t1_a8 = cf;
    Finder2(arr8, 800, x);
    int t2_a8 = cf;
    printf("|800|      %d     |      %d       |\n", t1_a8, t2_a8);
    Finder1_All(arr9, 900);
    int t1_a9 = cf;
    Finder2_All(arr9, 900);
    int t2_a9 = cf;
    printf("|900|      %d     |      %d       |\n", t1_a9, t2_a9);
    Finder1_All(arr10, 1000);
    int t1_a10 = cf;
    Finder2_All(arr10, 1000);
    int t2_a10 = cf;
    printf("|1000|      %d     |      %d       |\n", t1_a10, t2_a10);
    printf("------------------------------------\n");
}