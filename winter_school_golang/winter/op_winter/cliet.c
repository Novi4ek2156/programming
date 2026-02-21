#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Соглашение об имени FIFO */
#define FIFO "fifo.1"

int main(void) {
    int fd;
    char message[] = "А за окном идет дождь, я сижу на кухне хаваю борщ!\n";
    size_t message_len = strlen(message);
    
    /* Получим доступ к FIFO */
    if ((fd = open(FIFO, O_WRONLY)) < 0) {
        printf("Невозможно открыть FIFO\n");
        exit(1);
    }
    
    /* Передадим сообщение серверу FIFO */
    if (write(fd, message, message_len) != message_len) {
        printf("Ошибка записи\n");
        close(fd);
        exit(1);
    }
    
    close(fd);
    exit(0);
}
