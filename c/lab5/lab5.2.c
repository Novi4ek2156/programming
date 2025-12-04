#include <stdio.h>
#define N 5

int max_index(int array1[], int n) {
    if (n<=0) return -1;
    int max_index = 0;
    for (int j = 0; j < n;j++)
    {
        if (array1[j] > array1[max_index]) {
            max_index = j;
        }
    }
    return max_index;
}
int min_index(int array2[], int k){
    if (k<0) return -1;
    int min_index = 0;
    for (int l = 0; l<k; l++) {
        if (array2[l]< array2[min_index])
        min_index = l;
    }
    return min_index;
}

int main() {
int array_x[N] ={}; 

for (int i = 0; i<sizeof(array_x)/sizeof(array_x[0]); i++) {
    int a;
    printf("Enter a = ");
    scanf("%d", &a);
    array_x[i] = a;
}
int min_indx = min_index(array_x,N);
int max_indx = max_index(array_x, N);
printf("Kol-vo elementov: %d\n",N);
if (min_indx> max_indx) {
    for (int i = 0; i <N-1; i++) {
        if ( i != 0 && i>max_indx+1 || i != 0 && i< min_indx){
            array_x[i] = 0;
            printf("a[%d]= %d\n", i, array_x[i]);
        }
    }
}
else if (max_indx> min_indx)
{
    for (int i = 0; i <N-1; i++) {
        if ( i != 0 && i>min_indx+1 || i != 0 && i< max_indx){
            array_x[i] = 0;
            printf("a[%d]= %d\n", i, array_x[i]);
        }
    }
}


}
