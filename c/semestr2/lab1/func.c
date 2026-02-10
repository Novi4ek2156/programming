#include "main.h"
char names_for_kros[N][64] = {"Abibas", "Puma  ", "Crocs ", "Nike  ", "ZZZ   "};
char models_for_kros[N][64] = {"Super ", "Ultra ", "Nano  ","Piko  ", "Z420  "};

void FillStruct(struct kros array[N]) {
    for (int i = 0; i < N; i++) {
        int n = rand() % 4;
        int sell = rand() % 5000;
        int razmer = rand() % 43;
        array[i].name = names_for_kros[n]; 
        array[i].model = models_for_kros[n];
        array[i].size = razmer;
        array[i].buy = sell;
    }
} 
void PrintStruct(struct kros mnogo_kros[]){
    for (int i = 0; i < N; i++) {
        printf("Номер | Бренд | Модель | Размер | Цена |\n");
        printf("  %d   | %s|%s  |  %d    | %d  |\n", i, mnogo_kros[i].name, mnogo_kros[i].model, mnogo_kros[i].size, mnogo_kros[i].buy);
    }
    printf("--------------------------------------------\n");
}
void Sort(struct kros mnogo_kros[]) {
    printf("Сортировка по цене\n");
    for (int i =0; i < N - 1; i++) {
        int k = i;
        struct kros term = mnogo_kros[i];
        for (int j = i + 1; j < N; j++) {
            if (mnogo_kros[j].buy< mnogo_kros[k].buy) {
                k = j;
            }
        }
        mnogo_kros[i] = mnogo_kros[k];
        mnogo_kros[k] = term;
    }

}