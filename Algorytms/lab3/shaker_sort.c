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
int shaker_sort(int array[], int size) {
    int left = 0;
    int right = size-1;
    int k = size-1;
    cf = 0 , mf = 0, c = 0 , m = 0;
    do {
        for (int j = right; j > left; j--){
            int temp = 0;
            cf++;
            if (array[j] < array[j-1]){
                mf+=3;
                temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
                k = j;
            }
        }
        left = k;
        
        int temp1 = 0;
        for (int i = left; i < right; i++) {
            cf++;
            if (array[i] > array[i +1]) {
                mf+=3;
                temp1 = array[i];
                array[i] = array[i+1];
                array[i+1] = temp1;
                k = i;
            }
        }
        right = k;
        
    }
    while (left < right);
    c = (size * size - size)/2;
    m = 3 * c;
    return m, c, mf, cf;
}

int main() {
    int array[100];
    FillInc(array, 100);
    shaker_sort(array, 100);
    int tf1 = mf+cf;
    FillDec(array, 100);
    shaker_sort(array, 100);
    int tf2 = mf+cf;
    FillRand(array, 100);
    shaker_sort(array, 100);
    int tf3 = mf+cf;
    printf("----------------------------------------------------\n");
    printf("|  N  |  M + C(bubble)      |M(факт) + C(факт)Shaker|\n");
    printf("|     |Убыв. |Возраст.|Случ.|Убыв. | Возраст. |Случ.|\n");
    printf("|---------------------------------------------------\n");
    printf("| 100 |19800 | 4950   |12666|%d |  %d   | %d |\n", tf2,tf1, tf3);
    int array2[200];
    FillInc(array2, 200);
    shaker_sort(array2, 200);
    int t2 = m+c;
    int tf4 = mf+cf;
    FillDec(array2, 200);
    shaker_sort(array2, 200);
    int tf5 = mf+cf;
    FillRand(array2, 200);
    shaker_sort(array2, 200);
    int tf6 = mf+cf;
    printf("| 200 |79600 | 19900|50920 |%d | %d  |%d |\n", t2, tf5,tf4, tf6);
    int array3[300];
    FillInc(array3, 300);
    shaker_sort(array3, 300);
    int t3 = m+c;
    int tf_31 = mf+cf;
    FillDec(array3, 300);
    shaker_sort(array3, 300);
    int tf_32 = mf+cf;
    FillRand(array3, 300);
    shaker_sort(array3, 300);
    int tf_33 = mf+cf;
    printf("| 300 |179400| 44850|110169 |%d | %d  |%d |\n", t3, tf_32,tf_31, tf_33);
    int array4[400];
    FillInc(array4, 400);
    shaker_sort(array4, 400);
    int t4 = m+c;
    int tf_41 = mf+cf;
    FillDec(array4, 400);
    shaker_sort(array4, 400);
    int tf_42 = mf+cf;
    FillRand(array4, 400);
    shaker_sort(array4, 400);
    int tf_43 = mf+cf;
    printf("| 400 |319200| 79800|193083 |%d | %d  |%d |\n", t4, tf_42,tf_41, tf_43);
    int array5[500];
    FillInc(array5, 500);
    shaker_sort(array5, 500);
    int t5 = m+c;
    int tf_51 = mf+cf;
    FillDec(array5, 500);
    shaker_sort(array5, 500);
    int tf_52 = mf+cf;
    FillRand(array5, 500);
    shaker_sort(array5, 500);
    int tf_53 = mf+cf;
    printf("| 500 |499000| 124750|303919 |%d | %d  |%d |\n", t5, tf_52,tf_51, tf_53);
    printf("----------------------------------------------\n");
}