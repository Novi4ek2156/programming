#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct staff
{
    char name[128];
    int id;
    char level[128];
};
void compress() {
    FILE *database;
    database = fopen("../lab4/database.dat", "r+");
    if (database == NULL) {
        perror("Error opening file");
        exit(1);
    } 
    FILE *newdatabase;
    newdatabase = fopen("../lab4/database.rle", "w+");
    char buf[100];
    while (fread(buf, 1, sizeof(buf), database)) {
        unsigned char current_byte, next_byte;
        unsigned char count;
        long i;
        for(i = 0; i < sizeof(buf); i++) {
            current_byte = buf[i];
            if (i != 100) {
                next_byte = buf[i+1];
            }
            if (current_byte == next_byte){
                count++;
            } else {
                fwrite(&count, 1 ,1, newdatabase);
                fwrite(&current_byte,1, 1, newdatabase);
                count = 0;
            }
        }
        
        fwrite(&current_byte,1, 1, newdatabase);
    }
        
        fclose(database);
        fclose(newdatabase);
        printf("Сжатие завершено: создан файл database.rle\n");
}
void decompress() {
    FILE *comp;
    comp = fopen("../lab4/database.rle", "r+");
    if (comp ==NULL){
        perror("Error opening file");
        exit(1);
    }
    FILE *decomp;
    decomp = fopen("../lab4/decompdata.dat", "w+");
    unsigned char count, value;
    int i;
    size_t bytes_read;
    
    while (1) {
        bytes_read = fread(&count, 1, 1, comp);
        if (bytes_read != 1) {
            break; 
        }
        
        bytes_read = fread(&value, 1, 1, comp);
        if (bytes_read != 1) {
            printf("Ошибка: некорректный формат RLE файла (не хватает value)\n");
            break;
        }
        
        for (i = 0; i < count; i++) {
            if (fwrite(&value, 1, 1, decomp) != 1) {
                printf("Ошибка: не удалось записать в выходной файл\n");
                fclose(comp);
                fclose(decomp);
                return;
            }
        }
    }
    printf("Разжатие завершено: создан файл decompdata.dat\n");
        
}
void printdatasize() {
    FILE *original = fopen("../lab4/database.dat", "rb");
    FILE *compressed = fopen("../lab4/database.rle", "rb");
    
    if (original == NULL || compressed == NULL) {
        printf("Ошибка: не удалось открыть файлы\n");
        exit(1);
    }
    
    fseek(original, 0, SEEK_END);
    long original_size = ftell(original);
    rewind(original);
    
    fseek(compressed, 0, SEEK_END);
    long compressed_size = ftell(compressed);
    rewind(compressed);
    
    fclose(original);
    fclose(compressed);
    
    float compression_ratio = 0;
    if (original_size > 0) {
        compression_ratio = (1 - (float)compressed_size / original_size) * 100;
    }
    
    // Выводим отчет (в килобайтах)
    printf("\n========== ОТЧЕТ О СЖАТИИ ==========\n");
    printf("Размер до: %.2f Кб\n", original_size / 1024.0);
    printf("Размер после: %.2f Кб\n", compressed_size / 1024.0);
    printf("Сжатие: %.2f%%\n", compression_ratio);
    printf("=====================================\n");
}

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
    compress();
    decompress();
    printdatasize();
    fclose(file);
    fclose(database);

}