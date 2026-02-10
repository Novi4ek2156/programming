#include "lab10.h"

int fx(int a, int b, dot f[], int n) {
    for (int i=0; i < n; i++) {
        if (f[i].y == a * f[i].x + b) {
            printf("Точка (%d;%d) лежит на прямой\n", f[i].x, f[i].y);
        }
        else {
            printf("Точка (%d;%d) не лежит на прямой\n", f[i].x, f[i].y);
        }
    }
}
