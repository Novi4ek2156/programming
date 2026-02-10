#include <stdio.h>
#include <string.h>

int main() {
    char text[] = "Lorem ipsum dolor sit amet, consecteturk adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int j = 0;
    char result[] = "";
    int kol_vo_a = 0;
    int max_a = 0;
    char *word;
    word = strtok(text, " ,.");
    while (word != NULL) {
        kol_vo_a = 0;
        for (int i = 0; i < strlen(word); i++) {
            if (word[i]== 'a') {
                kol_vo_a++;
            }
            if (max_a < kol_vo_a) {
                max_a = kol_vo_a;
                strcpy(result, word);

            }
        }
        word = strtok(NULL, " ,.");
    }

    printf("Max a: %d\n slovo: %s\n", max_a, result);
}