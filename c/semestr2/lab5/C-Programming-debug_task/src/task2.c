#include <stdio.h>
#include <string.h>

// Проблема: number.num != 1025?

typedef struct {
    char str[5];
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    sprintf(number->str, "%3s", "1025" ,number->num);
}

int main() {
    NumberRepr number = { .str = "1025" , .num = 1025};
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
