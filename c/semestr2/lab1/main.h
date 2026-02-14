#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#define N 100

struct kros {
    char *name;
    char *model;
    int size;
    int buy;
};
void FillStruct(struct kros array[], int size);
void PrintStruct(struct kros mnogo_kros[]);
void Sort(struct kros mnogo_kros[], int size);