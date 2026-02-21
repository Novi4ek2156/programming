#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Функция обработки текста: находит все подстроки между 'a' и 'k'
void process(char *s, FILE *out) {
    if (!s || !out) return;
    
    char *start = s;
    int found = 0;
    
    while (*start) {
        // Ищем начало подстроки (символ 'a')
        char *a_pos = strchr(start, 'a');
        if (!a_pos) break;
        
        // Ищем конец подстроки (символ 'k') после найденного 'a'
        char *k_pos = strchr(a_pos + 1, 'k');
        if (!k_pos) break;
        
        int len = k_pos - a_pos + 1; 
        
        // Выделяем память для подстроки
        char *substr = malloc(len + 1); // +1 для нуль-терминатора
        if (!substr) {
            perror("malloc");
            break;
        }
        
        strncpy(substr, a_pos, len);
        substr[len] = '\0';
        
        // Записываем в файл
        fprintf(out, "%s\n", substr);
        free(substr);
        
        found = 1;
        
        // Продолжаем поиск с символа после 'k'
        start = k_pos + 1;
    }
    
    if (!found) {
        fprintf(out, "Подстроки 'a...k' не найдены\n");
    }
}

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    
    if (pid > 0) {
        // Родительский процесс - пишет в канал
        close(fd[0]); // закрываем чтение
        
        FILE *f = fopen("input.txt", "r");
        if (!f) { 
            perror("input.txt"); 
            exit(1); 
        }
        
        char c;
        while ((c = fgetc(f)) != EOF) {
            write(fd[1], &c, 1); // запись символа в канал
        }
        
        // Отправляем признак конца данных (Ctrl+Z в Windows, не EOF)
        c = 0x1A; // ASCII 26 - SUB (substitute)
        write(fd[1], &c, 1);
        
        close(fd[1]);
        fclose(f);
    }
    else if (pid == 0) {
        // Дочерний процесс - читает из канала и обрабатывает
        close(fd[1]); // закрываем запись
        
        char buf[5000];
        long unsigned int len = 0;
        char c;
        
        // Читаем данные из канала
        while (read(fd[0], &c, 1) == 1) {
            // Проверяем признак конца данных
            if ((unsigned char)c == 0x1A) break;
            
            // Проверяем переполнение буфера
            if (len >= sizeof(buf) - 1) {
                fprintf(stderr, "Буфер переполнен\n");
                break;
            }
            
            buf[len++] = c;
        }
        
        buf[len] = '\0'; // завершаем строку
        
        // Открываем файл для вывода
        FILE *out = fopen("output.txt", "w");
        if (!out) {
            perror("output.txt");
            close(fd[0]);
            exit(1);
        }
        
        // Обрабатываем текст
        process(buf, out);
        
        // Закрываем файлы и канал
        fclose(out);
        close(fd[0]);
        exit(0); // важно для дочернего процесса
    }
    else {
        // Ошибка fork
        perror("fork");
        exit(1);
    }
    
    return 0;
}