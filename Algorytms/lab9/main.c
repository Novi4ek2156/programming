#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

unsigned long long Mf = 0;
unsigned long long Cf = 0;

void reset_counters() {
    Mf = 0;
    Cf = 0;
}

unsigned long long checksum(int *arr, int n) {
    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (unsigned long long)arr[i];
    }
    return sum;
}

int count_series(int *arr, int n) {
    if (n <= 1) return n;
    int series = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            series++;
        }
    }
    return series;
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            return 0;
        }
    }
    return 1;
}

void build_pyramid(int *a, int L, int R) {
    int x = a[L];
    Mf++;
    int i = L;
    
    while (1) {
        int j = 2 * i;
        if (j > R) break;
        if (j < R) {
            Cf++;
            if (a[j] < a[j+1]) {
                j = j + 1;
            }
        }
        Cf++;
        if (x >= a[j]) break;
        a[i] = a[j];
        Mf++;
        i = j;
    }
    a[i] = x;
    Mf++;
}

void build_heap(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        build_pyramid(a, i, n);
    }
}

void heap_sort(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        build_pyramid(a, i, n);
    }
    
    for (int i = n; i > 1; i--) {
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        Mf += 3;
        
        build_pyramid(a, 1, i - 1);
    }
}

void generate_ascending(int *arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = i;
}

void generate_descending(int *arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = n - i + 1;
}

void generate_random(int *arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = rand() % 100;
}

void copy_array(int *dest, int *src, int n) {
    for (int i = 1; i <= n; i++)
        dest[i] = src[i];
}

void print_array(int *a, int n, const char *title) {
    printf("%s: [", title);
    for (int i = 1; i <= n; i++) {
        printf("%d", a[i]);
        if (i < n) printf(", ");
    }
    printf("]\n");
}

int theoretical_pyramid_C(int L, int R) {
    if (L >= R) return 0;
    return (int)(2 * log2((double)R / L));
}

int theoretical_pyramid_M(int L, int R) {
    if (L >= R) return 0;
    return (int)(log2((double)R / L)) + 2;
}

int theoretical_heap_M(int n) {
    if (n <= 1) return 0;
    return (int)(n * log2(n) + 6.5 * n - 4);
}

int theoretical_heap_C(int n) {
    if (n <= 1) return 0;
    return (int)(2 * n * log2(n) + n + 2);
}

int theoretical_heap_total(int n) {
    return theoretical_heap_M(n) + theoretical_heap_C(n);
}

void demo_heap_sort() {
    int n = 10;
    int *arr = (int*)malloc((n + 1) * sizeof(int));
    int *arr_copy = (int*)malloc((n + 1) * sizeof(int));
    
    printf("\n");
    printf("================================================================================\n");
    printf("ДЕМОНСТРАЦИЯ РАБОТЫ ПИРАМИДАЛЬНОЙ СОРТИРОВКИ (N=10)\n");
    printf("================================================================================\n");
    
    // Генерируем случайный массив
    generate_random(arr, n);
    copy_array(arr_copy, arr, n);
    
    // Вывод неотсортированного массива
    printf("\n--- НЕОТСОРТИРОВАННЫЙ МАССИВ ---\n");
    print_array(arr, n, "Массив");
    printf("Контрольная сумма: %llu\n", checksum(arr + 1, n));
    printf("Число серий: %d\n", count_series(arr + 1, n));
    
    // Сортируем
    heap_sort(arr, n);
    
    // Вывод отсортированного массива
    printf("\n--- ОТСОРТИРОВАННЫЙ МАССИВ ---\n");
    print_array(arr, n, "Массив");
    printf("Контрольная сумма: %llu\n", checksum(arr + 1, n));
    printf("Число серий: %d\n", count_series(arr + 1, n));
    
    printf("\n================================================================================\n");
    
    free(arr);
    free(arr_copy);
}
void study_pyramid_building() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = 5;
    
    printf("\n");
    printf("=====================Таблица 1. Трудоемкость построения пирамиды (M+C)=====================\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-8s | %-10s | %-45s\n", "N", "Теоретич. ", "Мфакт + Сфакт");
    printf("%-8s | %-10s | %-12s | %-12s | %-12s|\n", "", "(M+C)", "Убыв.  ", "   Случ.", "   Возр.");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int idx = 0; idx < num_sizes; idx++) {
        int n = sizes[idx];
        
        int *orig_asc = (int*)malloc((n + 1) * sizeof(int));
        int *orig_desc = (int*)malloc((n + 1) * sizeof(int));
        int *orig_rand = (int*)malloc((n + 1) * sizeof(int));
        int *work = (int*)malloc((n + 1) * sizeof(int));
        
        generate_ascending(orig_asc, n);
        generate_descending(orig_desc, n);
        generate_random(orig_rand, n);
        
        int total_theor = 0;
        for (int L = n / 2; L >= 1; L--) {
            total_theor += theoretical_pyramid_C(L, n) + theoretical_pyramid_M(L, n);
        }
        
        copy_array(work, orig_desc, n);
        reset_counters();
        build_heap(work, n);
        int desc_total = Mf + Cf;
        
        copy_array(work, orig_rand, n);
        reset_counters();
        build_heap(work, n);
        int rand_total = Mf + Cf;
        
        copy_array(work, orig_asc, n);
        reset_counters();
        build_heap(work, n);
        int asc_total = Mf + Cf;
        
        printf("%-8d | %-10d | %-12d %-12d %-12d\n", 
               n, total_theor, desc_total, rand_total, asc_total);
        
        free(orig_asc);
        free(orig_desc);
        free(orig_rand);
        free(work);
    }
    printf("--------------------------------------------------------------------------------\n");
}

void study_heap_sort() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = 5;
    
    printf("\n");
    printf("=====================Таблица 2. Трудоемкость пирамидальной сортировки HeapSort (Mф+Сф)=====================\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-8s | %-20s | %-20s | %-20s | %-12s|\n", 
           "N", "Убыв.", "Возр.", "Случ. ", "Теоретич.");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int idx = 0; idx < num_sizes; idx++) {
        int n = sizes[idx];
        
        int *work = (int*)malloc((n + 1) * sizeof(int));
        
        // Убывающий массив
        generate_descending(work, n);
        reset_counters();
        heap_sort(work, n);
        int desc_total = Mf + Cf;
        
        // Возрастающий массив
        generate_ascending(work, n);
        reset_counters();
        heap_sort(work, n);
        int asc_total = Mf + Cf;
        
        // Случайный массив
        generate_random(work, n);
        reset_counters();
        heap_sort(work, n);
        int rand_total = Mf + Cf;
        
        int theor_total = theoretical_heap_total(n);
        
        printf("%-8d | %-15d | %-17d | %-17d | %-12d |\n", 
               n, desc_total, asc_total, rand_total, theor_total);
        
        free(work);
    }
    printf("-------------------------------------------------------------------------------\n");
}

int main() {
    srand(time(NULL));
    study_pyramid_building();
    study_heap_sort();
    
    return 0;
}