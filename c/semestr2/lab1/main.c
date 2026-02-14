#include "main.h"




int main() {
    struct kros mnogo_kros[N];
    FillStruct(mnogo_kros, N);
    Sort(mnogo_kros, N);
    printf("---------------------\n");
    #undef N
    #define N 10000
    struct kros *mnogo_kros2 = malloc(N * sizeof(struct kros));
    FillStruct(mnogo_kros2, N);
    Sort(mnogo_kros2, N);
    free(mnogo_kros2);
    printf("---------------------\n");
    #undef N
    #define N 1000000
    struct kros *verymnogo_kros = malloc(N * sizeof(struct kros));
    FillStruct(verymnogo_kros, N);
    Sort(verymnogo_kros, N);
    free(verymnogo_kros);
}