#include "../include/main.h"

char *names_for_kros[5] = {"Abibas", "Puma  ", "Crocs ", "Nike  ", "ZZZ   "};
char *models_for_kros[5] = {"Super ", "Ultra ", "Nano  ","Piko  ", "Z420  "};

void FillStruct(struct kros array[], int size) {
    for (int i = 0; i < size; i++) {
        int n = rand() % 5;
        int sell = rand() % 5000;
        int razmer = rand() % 43;
        array[i].name = names_for_kros[n]; 
        array[i].model = models_for_kros[n];
        array[i].size = razmer;
        array[i].buy = sell;
    }
}
struct timeval start, end; 
void PrintStruct(struct kros mnogo_kros[]){
    for (int i = 0; i < N; i++) {
        printf("Номер | Бренд | Модель | Размер | Цена |\n");
        printf("  %d   | %s|%s  |  %d    | %d  |\n", i, mnogo_kros[i].name, mnogo_kros[i].model, mnogo_kros[i].size, mnogo_kros[i].buy);
    }
    printf("--------------------------------------------\n");
}
void Sort(struct kros mnogo_kros[], int size) {
        printf("Сортировка по цене\n");
        struct timeval start, end;
        gettimeofday(&start, NULL);
        for (int i =0; i < N - 1; i++) {
            int k = i;
            struct kros term = mnogo_kros[i];
            for (int j = i + 1; j < N; j++) {
                if (mnogo_kros[j].buy< mnogo_kros[k].buy) {
                    k = j;
                }
            }
            if (k != i) {
                mnogo_kros[i] = mnogo_kros[k];
                mnogo_kros[k] = term;
            }
        }
        gettimeofday(&end, NULL);
        double seconds = ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/size);;
        
        printf("Для сортировки массива из %d элементов было затрачено %.6f секунд!\n", size, seconds);
    
}

