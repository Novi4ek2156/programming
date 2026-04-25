#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker(void* arg) {
    int id = *(int*)arg;
    for (int i = 1; i <= 10; i++) {
        printf("Поток %d\n", id);
        sleep(1);
    }
    return NULL;
}
void* sleep_and_print(void* arg) {
    int n = *((int*)arg);
    usleep(n * 1000); 
    printf("%d ", n);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }
    sleep(2);

    for (int i = 0; i < 3; i++) {
        pthread_cancel(threads[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    int arr[] = {5, 2, 8, 1, 9, 3, 4, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    pthread_t thread[n];
    printf("До сортировки: ");
    for(int i =0; i< n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("После сортировки: ");
    for (int i = 0; i < n; i++) {
        pthread_create(&thread[i], NULL, sleep_and_print, &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(thread[i], NULL);
    }
    printf("\n");

}