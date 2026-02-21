#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#define FIFO "fifo.1"
#define MAXBUFF 80
int main(void) {
	int fd,n;
	char buff[MAXBUFF];
	if (mknod(FIFO, S_IFIFO | 0666,0) < 0) {
		printf("Невозможно содать FIFO\n");
		exit(1);
	}
	if ((fd = open(FIFO, O_RDONLY)) < 0) {
		printf("Невозможно открыть FIFO\n");
		exit(1);
	}
	while ((n = read(fd, buff, MAXBUFF)) > 0) {
		if (write(1, buff, n)!=n) {
			printf("Ошибка вывода!\n");	
			exit(1);
		}
	}
	char message[] = "Очень вкусно с капустой\n";
	size_t message_len = strlen(message);
	if (write(n, message, message_len) != message_len) {
		printf("Ошибка записи\n");
		close(fd);
		exit(1);
	}
	close(fd);
	if (unlink(FIFO) < 0) {
		printf("Невозможно удалить FIFO\n");
		exit(1);
	}
	exit(0);
}

