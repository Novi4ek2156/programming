#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cf, mf, c , m = 0;

int FillInc(int array[], int size) {
    int a = 1;
    for (int i = 0; i < size; i++) {
        array[i] = a;
        ++a;    
    }
}
int FillDec(int array[], int size) {
    int a = size;
    for (int i =0; i < size; i++) {
        array[i] = a;
        --a;
    }
}
int FillRand(int array[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int random = rand() %100;
        array[i] = random;
    }
}
void PrintMas(int array[], int size) {
    for (int i =0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int InsertSort(int arr[], int n) {
    cf = 0; mf = 0; c = 0; m = 0;
    for (int i = 1; i < n; i++) {
        int t = arr[i];  
        int j = i - 1;
        
        cf++;
        while (j >= 0 && arr[j] > t) {
            mf+=3;
            arr[j + 1] = arr[j];
            j--;
        };
            arr[j + 1] = arr[j];
            j--;
        
        arr[j + 1] = t;
        mf+=2;
    }
    c = (n *n - n)/2;
    m = c + 2*n - 2;
    return m, c, mf, cf;
}
void Timetabl(){
    printf("---------------------------------------\n");
    printf("|              Mf + Cf                |\n");
    printf("| n | select | Bubble | Shaker |Insert|\n");
    printf("---------------------------------------\n");
    printf("|100|  5047  |  9900  |  10441 | 7335 |\n");
    printf("|200| 20094  | 39800  |  30058 | 28602|\n");
    printf("|300|  45141 | 89700  | 67587  |65229 |\n");
    printf("|400| 80188  | 159600 | 120116 |117120|\n");
    printf("|500| 125235 | 249500 | 187645 |182436|\n");
    printf("---------------------------------------\n");
}
int main() {
    srand(time(NULL));
    int array[100];
    FillInc(array, 100);
    InsertSort(array, 100);
    int t1 = m+c;
    int tf1 = mf+cf;
    FillDec(array, 100);
    InsertSort(array, 100);
    int tf2 = mf+cf;
    FillRand(array, 100);
    InsertSort(array, 100);
    int tf3 = mf+cf;
    printf("-----------------------------------------\n");
    printf("|  N  |  M + C  |   M(факт) + C(факт)   |\n");
    printf("|     |  теор   |Убыв. | Возраст. |Случ.|\n");
    printf("|----------------------------------------\n");
    printf("| 100 |  %d  |10098 |   297  |%d |\n", t1, tf3);
    int array2[200];
    FillInc(array2, 200);
    InsertSort(array2, 200);
    int t2 = m+c;
    int tf4 = mf+cf;
    FillDec(array2, 200);
    InsertSort(array2, 200);
    int tf5 = mf+cf;
    FillRand(array2, 200);
    InsertSort(array2, 200);
    int tf6 = mf+cf;
    printf("| 200 |  %d  |40198 |  597  |%d |\n", t2, tf6);
    int array3[300];
    FillInc(array3, 300);
    InsertSort(array3, 300);
    int t3 = m+c;
    int tf_31 = mf+cf;
    FillDec(array3, 300);
    InsertSort(array3, 300);
    int tf_32 = mf+cf;
    FillRand(array3, 300);
    InsertSort(array3, 300);
    int tf_33 = mf+cf;
    printf("| 300 | %d  |90298|  897 |%d|\n", t3,tf_33);
    int array4[400];
    FillInc(array4, 400);
    InsertSort(array4, 400);
    int t4 = m+c;
    int tf_41 = mf+cf;
    FillDec(array4, 400);
    InsertSort(array4, 400);
    int tf_42 = mf+cf;
    FillRand(array4, 400);
    InsertSort(array4, 400);
    int tf_43 = mf+cf;
    printf("| 400 | %d  |160398|  1197  |%d|\n", t4,tf_43);
    int array5[500];
    FillInc(array5, 500);
    InsertSort(array5, 500);
    int t5 = m+c;
    int tf_51 = mf+cf;
    FillDec(array5, 500);
    InsertSort(array5, 500);
    int tf_52 = mf+cf;
    FillRand(array5, 500);
    InsertSort(array5, 500);
    int tf_53 = mf+cf;
    printf("| 500 | %d  |250498| 1497|%d|\n", t5, tf_53);
    printf("-----------------------------------------\n");
    Timetabl();
}   