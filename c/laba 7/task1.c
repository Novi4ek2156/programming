#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "uuuuuuuuuuuuuuuuuuuuuuu est alaborum.k";
    char *first_a, *first_k;
    char string[100];
    first_a = strchr(str, 'a');
    if (first_a != NULL) {  
        first_k = strchr(first_a + 1, 'k');
        if (first_k != NULL) {
            int len = first_k - first_a;
            strncpy(string, first_a, len);
            string[len] = '\0';
            
            printf("Подстрока: %s\n", string);
        } else {
            printf("Буква 'k' не найдена после 'a'\n");
        }
    } else {
        printf("Буква 'a' не найдена\n");
    }
    return 0;
}
        
    
    
    



