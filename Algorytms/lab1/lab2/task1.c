#include <stdio.h>
#include <stdlib.h>

void Sort(char *array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        char *term;
        for (int j = i + 1; j < n; j++ ) {
            if (*array[j] < *array[k]) {
                k = j;
            }   
            
        }
        
        if (i != k) {
            term = array[i];
            *array[i] = *array[k];
            array[k] = term;
        }
    }
}
void Print(char *array[], int n) {
    for (int i=0; i< n; i++) {
        printf("%s ", array[i]);
    }
    printf("\n");


}
int main() {
    char *array[8] = {"с", "е", "м", "ё", "н", "о", "в", "в"};
    Sort(array, 8);
    Print(array, 8);

}