#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct staff
{
    char name[128];
    int id;
    char level[128];
};


int main() {
    FILE *file;
    FILE *database;
    char buffer[100];
    file = fopen("../lab4/staff.csv", "r");
    database = fopen("../lab4/database.dat", "w+");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    struct staff new;
    while (fgets(buffer, 100, file)) {
        char *a = strtok(buffer,";");
        strcpy(new.name,a);
        a = strtok(NULL, ";");
        new.id = atoi(a);
        a = strtok(NULL, ";");
        strcpy(new.level, a);
        fwrite(&new,sizeof(struct staff),1, database);
        printf("%s\n", buffer);

    }
    rewind(database);
    char buffer2[100];
    int user_id;
    printf("Enter user id: ");
    scanf("%d", &user_id);
    int find = 0;
    while (fread(&new, sizeof(struct staff), 1, database)) {
    if (new.id == user_id) {
        find = 1;
        printf("Найдено: %s, Уровень: %s\n", new.name, new.level);
        break;
    }
}
if (find != 1) {
    perror("Пользователя с таким id не существует");
    exit(1);
}

    fclose(file);
    fclose(database);

}