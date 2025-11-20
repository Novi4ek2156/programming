#include <stdio.h>
#include <string.h>

int main() {
    char text[] = "Lorem ipsum dolor sit amet, consecteturk adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char result[] = "";
    int j = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == 'L') {
            result[j++] = text[i];
        }
        if ((text[i-1] == ' ') && (text[i] != ' ' || text[i] != '.' || text[i] != ',')) {
            result[j++] = text[i];
        }
    }
    result[j]= '\0';
    printf("%s\n", result);
}