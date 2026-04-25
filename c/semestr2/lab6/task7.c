#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int turn = 0;

void* childThread(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_mutex_unlock(&mutex);
            usleep(10000);
            pthread_mutex_lock(&mutex);
        }
        printf("Дочерний: строка %d\n", i + 1);
        turn = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, childThread, NULL);
    
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) {
            pthread_mutex_unlock(&mutex);
            usleep(10000);
            pthread_mutex_lock(&mutex);
        }
        printf("Родительский: строка %d\n", i + 1);
        turn = 1;
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}