#include <stdio.h>
#include <stdlib.h>
#define N 5
struct kros {
    char *name;
    char *model;
    int size;
    int buy;
};
void FillStruct(struct kros array[N]);
void PrintStruct(struct kros mnogo_kros[]);
void Sort(struct kros mnogo_kros[]);