#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct {
    int start_row;
    int end_row;
    int N;
    double* A;
    double* B;
    double* C;
} MatrixData;

void* multiplyRows(void* arg) {
    MatrixData* data = (MatrixData*)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            double sum = 0;
            for (int k = 0; k < data->N; k++) {
                sum += data->A[i * data->N + k] * data->B[k * data->N + j];
            }
            data->C[i * data->N + j] = sum;
        }
    }
    return NULL;
}

void printMatrix(double* M, int N, const char* name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.2f ", M[i * N + j]);
        }
        printf("\n");
    }
}

double multiplyMatricesParallel(double* A, double* B, double* C, int N, int num_threads) {
    pthread_t threads[num_threads];
    MatrixData data[num_threads];
    
    int rows_per_thread = N / num_threads;
    int remainder = N % num_threads;
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int current_row = 0;
    for (int t = 0; t < num_threads; t++) {
        data[t].start_row = current_row;
        data[t].end_row = current_row + rows_per_thread + (t < remainder ? 1 : 0);
        data[t].N = N;
        data[t].A = A;
        data[t].B = B;
        data[t].C = C;
        current_row = data[t].end_row;
        
        pthread_create(&threads[t], NULL, multiplyRows, &data[t]);
    }
    
    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000.0;
    
    return elapsed;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Использование: %s <размер матрицы> <количество потоков>\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    
    // Выделение памяти
    double* A = (double*)malloc(N * N * sizeof(double));
    double* B = (double*)malloc(N * N * sizeof(double));
    double* C = (double*)calloc(N * N, sizeof(double));
    
    // Заполнение матриц единицами
    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 1.0;
    }
    
    if (N < 5) {
        printMatrix(A, N, "Матрица A");
        printMatrix(B, N, "Матрица B");
    }
    
    double time_ms = multiplyMatricesParallel(A, B, C, N, num_threads);
    
    if (N < 5) {
        printMatrix(C, N, "Матрица C (результат)");
    }
    
    printf("Размер: %d x %d, Потоков: %d, Время: %.2f мс\n", N, N, num_threads, time_ms);
    
    // Проверка (все элементы должны быть равны N)
    printf("Проверка: C[0][0] = %.0f\n", C[0]);
    
    free(A);
    free(B);
    free(C);
    
    return 0;
}