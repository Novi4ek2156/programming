#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int cf = 0;
int mf = 0;
int c = 0;
int m = 0;
int chet = 0;
void fillinc(int array[], int n) {
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
}
void filldec(int array[], int n) {
    int a = n;
    for (int i = 0; i < n; i++) {
        array[i] = a - i;
    }
}
void fillrand(int array[], int n) {
    int a;
    for (int i =0; i < n; i++) {
        a = rand() % 500;
        array[i] = a;
    }
}
int teoretical(int n) {
    m = 0, c = 0;
    m = 3 * (n - 1);
    c = (n * n + 5 * n + 4) / 2;
    return c + m;
}
void clear_chet() {
    chet = 0;
}
void clear_tf() {
    cf = 0;
    mf = 0;
}
int quicksort1(int array[], int l, int r) {
    int x = array[l];
    int i = l;
    int j = r;
    while (i <= j) {
        chet++;
        while (1) {
            cf++;
            if (array[i] < x) {
                i++;
            } else {
                break;
            }
        }
        while (1) {
            cf++;
            if (array[j] > x) {
                j--;
            } else {
                break;
            }
        }
        
        if (i <= j) {
            mf+=3;
            int term = array[j];
            array[j] = array[i];
            array[i] = term;
            i++;
            j--;
        }
    }
    
    if (l < j) {
        quicksort1(array, l, j);
    }
    
    if (i < r) {
        quicksort1(array, i, r);
    }
    
}
int quicksort2(int array[], int l, int r) {
    while (l < r) {
        int x = array[l];
        int i = l;
        int j = r;
        chet++;
        while (i <= j) {
            while(i <= r && array[i] < x ) {
                i++;
            }
            while (j >= l && array[j] > x) {
                j--;
            }
            if (i <= j) {
                int term = array[j];
                array[j] = array[i];
                array[i] = term;
                i++;
                j--;
            }
            if (j - l > r -i) {
                quicksort2(array, i, r);
                r = j;
            } else {
                quicksort2(array, l, j);
                l = i;
            }
        }
    }
    return cf, mf;
}
int main() {
    srand(time(NULL));
    printf("=============================QuickSort.v1=============================\n");
    int arr1_inc[100];
    fillinc(arr1_inc, 100);
    quicksort1(arr1_inc, 0, 99);
    int tf1_inc = cf + mf;
    int chet1_inc = chet;
    clear_chet();
    clear_tf();
    int arr1_dec[100];
    filldec(arr1_dec, 100);
    quicksort1(arr1_dec, 0, 99);
    int tf1_dec = cf + mf;
    int chet1_dec = chet;
    clear_chet();
    clear_tf();
    int arr1_rand[100];
    fillrand(arr1_rand, 100);
    quicksort1(arr1_rand, 0, 99);
    int tf1_rand = cf + mf;
    clear_tf();
    int chet1_rand = chet;
    clear_chet();
    printf("-------------------------------------------\n");
    printf("|  N  |             QuickSort             |\n");
    printf("|     |   Убыв.   |   Возр.   |   Случ.   |\n");
    printf("-------------------------------------------\n");
    printf("| 100 |    %d    | %d     |    %d   |\n", tf1_dec, tf1_inc, tf1_rand);
    int arr2_inc[200];
    fillinc(arr2_inc, 200);
    quicksort1(arr2_inc, 0, 199);
    int tf2_inc = cf + mf;
    clear_tf();
    int chet2_inc = chet;
    clear_chet();
    int arr2_dec[200];
    filldec(arr2_dec, 200);
    quicksort1(arr2_dec, 0, 199);
    int tf2_dec = cf + mf;
    clear_tf();
    int chet2_dec = chet;
    clear_chet();
    int arr2_rand[200];
    fillrand(arr2_rand,200);
    quicksort1(arr2_rand, 0, 199);
    int tf2_rand = cf + mf;
    clear_tf();
    int chet2_rand = chet;
    clear_chet();
    printf("| 200 |    %d   |  %d    |   %d   |\n", tf2_dec, tf2_inc, tf2_rand);
    int arr3_inc[300];
    fillinc(arr3_inc, 300);
    quicksort1(arr3_inc, 0, 299);
    int tf3_inc = cf + mf;
    clear_tf();
    int chet3_inc = chet;
    clear_chet();
    int arr3_dec[300];
    filldec(arr3_dec, 300);
    quicksort1(arr3_dec, 0, 299);
    int tf3_dec = cf + mf;
    clear_tf();
    int chet3_dec = chet;
    clear_chet();
    int arr3_rand[300];
    fillrand(arr3_rand, 300);
    quicksort1(arr3_rand, 0, 299);
    int tf3_rand = cf + mf;
    clear_tf();
    int chet3_rand = chet;
    clear_chet();
    printf("| 300 |    %d   |    %d  |   %d   |\n", tf3_dec, tf3_inc, tf3_rand);
    int arr4_inc[400];
    fillinc(arr4_inc, 400);
    quicksort1(arr4_inc, 0, 399);
    int tf4_inc = cf + mf;
    clear_tf();
    int chet4_inc = chet;
    clear_chet();
    int arr4_dec[400];
    filldec(arr4_dec, 400);
    quicksort1(arr4_dec, 0, 399);
    int tf4_dec = cf + mf;
    clear_tf();
    int chet4_dec = chet;
    clear_chet();
    int arr4_rand[400];
    fillrand(arr4_rand, 400);
    quicksort1(arr4_rand, 0, 399);
    int tf4_rand = cf + mf;
    clear_tf();
    int chet4_rand = chet;
    clear_chet();
    printf("| 400 |    %d   |  %d    |   %d   |\n", tf4_dec, tf4_inc, tf4_rand);
    int arr5_inc[500];
    fillinc(arr5_inc, 500);
    quicksort1(arr5_inc, 0, 499);
    int tf5_inc = cf + mf;
    clear_tf();
    int chet5_inc = chet;
    clear_chet();
    int arr5_dec[500];
    filldec(arr5_dec, 500);
    quicksort1(arr5_dec, 0, 499);
    int tf5_dec = cf + mf;
    clear_tf();
    int chet5_dec = chet;
    clear_chet();
    int arr5_rand[500];
    fillrand(arr5_rand, 500);
    quicksort1(arr5_rand, 0, 499);
    int tf5_rand = cf + mf;
    clear_tf();
    int chet5_rand = chet;
    clear_chet();
    printf("| 500 |    %d  |  %d   |  %d   |\n", tf5_dec, tf5_inc, tf5_rand);
    printf("-------------------------------------------\n");
    printf("======================Сравнение глубины рекурсии======================\n");
    int ar1_inc[100];
    fillinc(ar1_inc, 100);
    quicksort2(ar1_inc, 0, 99);
    int che1_inc = chet;
    clear_chet();
    int ar1_dec[100];
    filldec(ar1_dec, 100);
    quicksort2(ar1_dec, 0, 99);
    int che1_dec = chet;
    clear_chet();
    int ar1_rand[100];
    fillrand(ar1_rand, 100);
    quicksort2(ar1_rand, 0, 99);
    int che1_rand = chet;
    clear_chet();
    printf("-------------------------------------------------------\n");
    printf("|  n  |       QuickSort1      |       Quicksort2      |\n");
    printf("|     | Убыв. | Возр. | Случ. | Убыв. | Возр. | Случ. |\n");
    printf("-------------------------------------------------------\n");
    printf("| 100 |   %d  |  %d   |  %d   |  %d   |  %d   |  %d   |\n", chet1_inc, chet1_dec, chet1_rand, che1_inc, che1_dec, che1_rand);
    int ar2_inc[200];
    fillinc(ar2_inc, 200);
    quicksort2(ar2_inc, 0, 199);
    int che2_inc = chet;
    clear_chet();
    int ar2_dec[200];
    filldec(ar2_dec, 200);
    quicksort2(ar2_dec, 0, 199);
    int che2_dec = chet;
    clear_chet();
    int ar2_rand[200];
    fillrand(ar2_rand, 200);
    quicksort2(ar2_rand, 0, 199);
    int che2_rand = chet;
    clear_chet();
    printf("| 200 |   %d  |  %d   |  %d   |  %d   |  %d   |  %d   |\n", chet2_inc, chet2_dec, chet2_rand, che2_inc, che2_dec, che2_rand);
    int ar3_inc[300];
    fillinc(ar3_inc, 300);
    quicksort2(ar3_inc, 0, 299);
    int che3_inc = chet;
    clear_chet();
    int ar3_dec[300];
    filldec(ar3_dec, 300);
    quicksort2(ar3_dec, 0, 299);
    int che3_dec = chet;
    clear_chet();
    int ar3_rand[300];
    fillrand(ar3_rand, 300);
    quicksort2(ar3_rand, 0, 299);
    int che3_rand = chet;
    clear_chet();
    printf("| 300 |   %d  |  %d   |  %d   |  %d   |  %d   |  %d   |\n", chet3_inc, chet3_dec, chet3_rand, che3_inc, che3_dec, che3_rand);
    int ar4_inc[400];
    fillinc(ar4_inc, 400);
    quicksort2(ar4_inc, 0, 399);
    int che4_inc = chet;
    clear_chet();
    int ar4_dec[400];
    filldec(ar4_dec, 400);
    quicksort2(ar4_dec, 0, 399);
    int che4_dec = chet;
    clear_chet();
    int ar4_rand[400];
    fillrand(ar4_rand, 400);
    quicksort2(ar4_rand, 0, 399);
    int che4_rand = chet;
    clear_chet();
    printf("| 400 |   %d  |  %d   |  %d   |  %d   |  %d   |  %d   |\n", chet4_inc, chet4_dec, chet4_rand, che4_inc, che4_dec, che4_rand);
    int ar5_inc[500];
    fillinc(ar5_inc, 500);
    quicksort2(ar5_inc, 0, 499);
    int che5_inc = chet;
    clear_chet();
    int ar5_dec[500];
    filldec(ar5_dec, 500);
    quicksort2(ar5_dec, 0, 499);
    int che5_dec = chet;
    clear_chet();
    int ar5_rand[500];
    fillrand(ar5_rand, 500);
    quicksort2(ar5_rand, 0, 499);
    int che5_rand = chet;
    clear_chet();
    printf("| 500 |   %d  |  %d   |  %d   |  %d   |  %d   |  %d   |\n", chet5_inc, chet5_dec, chet5_rand, che5_inc, che5_dec, che5_rand);
    printf("-------------------------------------------------------\n");
}