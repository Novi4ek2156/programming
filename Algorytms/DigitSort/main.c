#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_BUCKETS 256

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* create_queue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

int is_empty_queue(Queue *q) {
    return q->size == 0;
}

void enqueue(Queue *q, int value, int *moves) {
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
    (*moves)++;  
}

int dequeue(Queue *q, int *moves) {
    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    (*moves)++;
    return value;
}

void free_queue(Queue *q) {
    free(q->data);
    free(q);
}

int* digital_sort(int *arr, int n, int num_bytes, int reverse, int *moves) {
    if (n == 0) return NULL;
    
    *moves = 0;
    
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
    }
    int offset = (min_val < 0) ? -min_val : 0;
    
    int *working_arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        working_arr[i] = arr[i] + offset;
    }
    int num_digits = num_bytes;
    
    Queue *buckets[MAX_BUCKETS];
    for (int i = 0; i < MAX_BUCKETS; i++) {
        buckets[i] = create_queue(n);
    }
    
    int *temp_arr = (int*)malloc(n * sizeof(int));
    memcpy(temp_arr, working_arr, n * sizeof(int));
    
    for (int byte_pos = 0; byte_pos < num_digits; byte_pos++) {
        for (int i = 0; i < n; i++) {
            int byte_val = (temp_arr[i] >> (byte_pos * 8)) & 0xFF;
            enqueue(buckets[byte_val], temp_arr[i], moves);
        }
        
        int idx = 0;
        if (!reverse) {
            for (int b = 0; b < MAX_BUCKETS; b++) {
                while (!is_empty_queue(buckets[b])) {
                    temp_arr[idx++] = dequeue(buckets[b], moves);
                }
            }
        } else {
            for (int b = MAX_BUCKETS - 1; b >= 0; b--) {
                while (!is_empty_queue(buckets[b])) {
                    temp_arr[idx++] = dequeue(buckets[b], moves);
                }
            }
        }
    }
    
    int *result = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = temp_arr[i] - offset;
    }
    
    for (int i = 0; i < MAX_BUCKETS; i++) {
        free_queue(buckets[i]);
    }
    free(working_arr);
    free(temp_arr);
    *moves = *moves / 2;
    
    return result;
}

int* generate_random_array(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() | (rand() << 15) | ((rand() & 0xFF) << 30);
        if (rand() % 2) arr[i] = -arr[i];
    }
    return arr;
}

int* generate_ascending_array(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

int* generate_descending_array(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = n - i - 1;
    }
    return arr;
}

void compare_ordering() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = 5;
    int num_bytes = 4;
    
    printf("\n-------------------------------------------------------------\n");
    printf("ТРУДОЕМКОСТЬ ЦИФРОВОЙ СОРТИРОВКИ (4 байта)\n");
    printf("-------------------------------------------------------------\n");
    printf("N    M теоретич.  Убыв.   Случ.   Возр.\n");
    printf("--------------------------------------------------------------\n");
    
    srand(12345);
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int M_theor = n * num_bytes; 
        
        int *ascending = generate_ascending_array(n);
        int *descending = generate_descending_array(n);
        int *random_arr = generate_random_array(n);
        
        int moves_asc, moves_desc, moves_rand;
        
        int *result_asc = digital_sort(ascending, n, num_bytes, 0, &moves_asc);
        int *result_desc = digital_sort(descending, n, num_bytes, 0, &moves_desc);
        int *result_rand = digital_sort(random_arr, n, num_bytes, 0, &moves_rand);
        
        printf("%3d    %6d    %5d   %5d   %5d\n",
               n, M_theor, moves_desc, moves_rand, moves_asc);
        
        free(ascending);
        free(descending);
        free(random_arr);
        free(result_asc);
        free(result_desc);
        free(result_rand);
    }
    printf("-------------------------------------------------------------\n");
}

void print_tables() {
    printf("\n-------------------------------------------------------------\n");
    printf("ТАБЛИЦА ТРУДОЕМКОСТИ ДЛЯ 2-БАЙТНЫХ И 4-БАЙТНЫХ ЧИСЕЛ\n");
    printf("-------------------------------------------------------------\n");
    
    srand(12345);
    
    // Таблица для 2-х байт
    printf("Таблица 1: 2-байтовые числа (фиксированные 2 прохода)\n");
    printf("-------------------------------------------------------------\n");
    printf("|   N   | M теоретич. |  Убыв.   |  Случ.   |  Возр.    |\n");
    printf("-------------------------------------------------------------\n");
    
    int sizes[] = {100, 200, 300, 400, 500};
    int num_bytes_2 = 2;
    
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int M_theor = n * num_bytes_2;
        
        int *ascending = generate_ascending_array(n);
        int *descending = generate_descending_array(n);
        int *random_arr = generate_random_array(n);
        
        int moves_asc, moves_desc, moves_rand;
        
        int *result_asc = digital_sort(ascending, n, num_bytes_2, 0, &moves_asc);
        int *result_desc = digital_sort(descending, n, num_bytes_2, 0, &moves_desc);
        int *result_rand = digital_sort(random_arr, n, num_bytes_2, 0, &moves_rand);
        
        printf("| %4d  |    %5d    |  %5d  |  %5d  |   %5d   |\n",
               n, M_theor, moves_desc, moves_rand, moves_asc);
        
        free(ascending);
        free(descending);
        free(random_arr);
        free(result_asc);
        free(result_desc);
        free(result_rand);
    }
    
    printf("-------------------------------------------------------------\n\n");
    
    // Таблица для 4-х байт
    printf("Таблица 2: 4-байтовые числа (фиксированные 4 прохода)\n");
    printf("-------------------------------------------------------------\n");
    printf("|   N   | M теоретич. |  Убыв.   |  Случ.   |  Возр.    |\n");
    printf("-------------------------------------------------------------\n");
    
    int num_bytes_4 = 4;
    
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int M_theor = n * num_bytes_4;
        
        int *ascending = generate_ascending_array(n);
        int *descending = generate_descending_array(n);
        int *random_arr = generate_random_array(n);
        
        int moves_asc, moves_desc, moves_rand;
        
        int *result_asc = digital_sort(ascending, n, num_bytes_4, 0, &moves_asc);
        int *result_desc = digital_sort(descending, n, num_bytes_4, 0, &moves_desc);
        int *result_rand = digital_sort(random_arr, n, num_bytes_4, 0, &moves_rand);
        
        printf("| %4d  |    %5d    |  %5d  |  %5d  |   %5d   |\n",
               n, M_theor, moves_desc, moves_rand, moves_asc);
        
        free(ascending);
        free(descending);
        free(random_arr);
        free(result_asc);
        free(result_desc);
        free(result_rand);
    }
    printf("------------------------------------------------------\n");
}

int main() {
    srand(time(NULL));
    
    int test_arr[] = {5, 2, 8, 1, 9, 3, -5, -1, 0, 7};
    int n = sizeof(test_arr) / sizeof(test_arr[0]);
    int moves;
    int *sorted = digital_sort(test_arr, n, 4, 0, &moves);
    
    printf("\n---------------------------------------------\n");
    printf("Трудоемкость цифровой сортировки DigitalSort\n");
    printf("---------------------------------------------\n");
    printf("N    2 байта  4 байта                \n");
    printf("---------------------------------------------\n");
    for (int i = 100; i <= 500; i+=100) {
        printf("%d     %d     %d\n", i, i*2, i*4);
    }
    printf("---------------------------------------------\n");
    free(sorted);
    print_tables();
    
    return 0;
}