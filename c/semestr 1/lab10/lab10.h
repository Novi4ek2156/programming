#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct line
{
    int a;
    int b;
};
typedef struct
{
    int x;
    int y;
}dot;

int fx(int a, int b, dot f[], int n);