#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void cleanup_handler(void* arg) {
    printf("Поток %d: завершаю работу!\n", *(int*)arg);
}
void* printText(void* arg) {
    for(int i =0; i < 5; ++i) {
        puts(arg);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, printText, "Parent");
    pthread_create(&thread2, NULL, printText, "Doughter");

    sleep(2);

    pthread_cancel(thread1);
    pthread_cancel(thread2);
    pthread_exit(NULL);
}    