#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct ThreadData {
    int index;
    char* data[3];
}ThreadData;


void* printText(void* arg) {
    for(int i =0; i < 5; ++i) {
        puts(arg);
        
    }
    return NULL;
}
void* printLines(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Поток %d:\n", data->index);
    for (int i = 0; i < 3; i++) {
        printf("  %s\n", data->data[i]);
    }
    return NULL;
}

int main() {
    //pthread_t thread1, thread2;
    //pthread_create(&thread1, NULL, printText, "Parent");
    //pthread_create(&thread2, NULL, printText, "Doughter");
    //pthread_join(thread2, NULL);
    //pthread_join(thread1, NULL);
    //pthread_exit(NULL);
    //----------------------------------------------------------------
    pthread_t thread[4];
    ThreadData data[4] = {{1, {"HI", "Bb", "Cc"} },
                            {2, {"Dd", "Ee", "Ff"}},
                           {3, {"Gg","Kk", "Ll"}},
                            {4, {"Mm", "Nn", "Ss"}}
    };
    for (int i = 0; i < 4; i++) {
        pthread_create(&thread[i], NULL, printLines, &data[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(thread[i], NULL);
    }
    //----------------------------------------------------------------
    



}