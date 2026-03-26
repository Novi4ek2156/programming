#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    char buffer[100];
    file = fopen("../lab4/staff.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
        char*str=    strtok(buffer,";");
        str =strtok(buffer,NULL);

    while (fgets(buffer, 100, file)) {
        strtok(buffer,";");
        printf("%s\n", buffer);

    }

    fclose(file);

}