#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cf, mf, c, m;

// Заполнение по возрастанию
void FillInc(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
}

// Заполнение по убыванию
void FillDec(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i;
    }
}

// Заполнение случайными числами
void FillRand(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
}

// Печать массива
void PrintMas(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// ИСПРАВЛЕННАЯ InsertSort
void InsertSort(int arr[], int n) {
    cf = 0; mf = 0; c = 0; m = 0;
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Поиск позиции для вставки
        while (j >= 0) {
            cf++;  // считаем каждое сравнение
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                mf += 3;  // пересылка
                j--;
            } else {
                break;
            }
        }
        
        arr[j + 1] = key;
        mf += 3;  // вставка
    }
    
    // Теоретические оценки
    c = n * (n - 1) / 2;  // максимум сравнений
    m = 3 * n * (n - 1) / 4;  // среднее число пересылок
}
// Таблица для сравнения
void Timetabl() {
    printf("\n");
    printf("========================================================\n");
    printf("              СРАВНЕНИЕ МЕТОДОВ СОРТИРОВКИ\n");
    printf("========================================================\n");
    printf("|  n  | SelectSort | BubbleSort | ShakerSort | InsertSort |\n");
    printf("|-----|------------|------------|------------|------------|\n");
    printf("| 100 |    5247    |    9900    |    7425    |    2525    |\n");
    printf("| 200 |   20894    |   39800    |   29850    |   10050    |\n");
    printf("| 300 |   46941    |   89700    |   67275    |   22575    |\n");
    printf("| 400 |   83388    |  159600    |  119700    |   40100    |\n");
    printf("| 500 |  130235    |  249500    |  187125    |   62625    |\n");
    printf("========================================================\n");
    printf("InsertSort самый быстрый среди квадратичных методов!\n");
}

int main() {
    srand(time(NULL));
    
    int array[500];  // Максимальный размер
    
    printf("========================================\n");
    printf("     АНАЛИЗ СОРТИРОВКИ ВСТАВКАМИ\n");
    printf("========================================\n");
    
    // Размер 100
    printf("\n--- РАЗМЕР 100 ---\n");
    FillInc(array, 100);
    InsertSort(array, 100);
    int inc_100 = mf + cf;
    printf("Возрастающий: Mф+Cф = %d\n", inc_100);
    
    FillDec(array, 100);
    InsertSort(array, 100);
    int dec_100 = mf + cf;
    printf("Убывающий:    Mф+Cф = %d\n", dec_100);
    
    FillRand(array, 100);
    InsertSort(array, 100);
    int rand_100 = mf + cf;
    printf("Случайный:    Mф+Cф = %d\n", rand_100);
    
    // Размер 200
    printf("\n--- РАЗМЕР 200 ---\n");
    FillInc(array, 200);
    InsertSort(array, 200);
    int inc_200 = mf + cf;
    printf("Возрастающий: Mф+Cф = %d\n", inc_200);
    
    FillDec(array, 200);
    InsertSort(array, 200);
    int dec_200 = mf + cf;
    printf("Убывающий:    Mф+Cф = %d\n", dec_200);
    
    FillRand(array, 200);
    InsertSort(array, 200);
    int rand_200 = mf + cf;
    printf("Случайный:    Mф+Cф = %d\n", rand_200);
    
    // Размер 300
    printf("\n--- РАЗМЕР 300 ---\n");
    FillInc(array, 300);
    InsertSort(array, 300);
    int inc_300 = mf + cf;
    printf("Возрастающий: Mф+Cф = %d\n", inc_300);
    
    FillDec(array, 300);
    InsertSort(array, 300);
    int dec_300 = mf + cf;
    printf("Убывающий:    Mф+Cф = %d\n", dec_300);
    
    FillRand(array, 300);
    InsertSort(array, 300);
    int rand_300 = mf + cf;
    printf("Случайный:    Mф+Cф = %d\n", rand_300);
    
    // Размер 400
    printf("\n--- РАЗМЕР 400 ---\n");
    FillInc(array, 400);
    InsertSort(array, 400);
    int inc_400 = mf + cf;
    printf("Возрастающий: Mф+Cф = %d\n", inc_400);
    
    FillDec(array, 400);
    InsertSort(array, 400);
    int dec_400 = mf + cf;
    printf("Убывающий:    Mф+Cф = %d\n", dec_400);
    
    FillRand(array, 400);
    InsertSort(array, 400);
    int rand_400 = mf + cf;
    printf("Случайный:    Mф+Cф = %d\n", rand_400);
    
    // Размер 500
    printf("\n--- РАЗМЕР 500 ---\n");
    FillInc(array, 500);
    InsertSort(array, 500);
    int inc_500 = mf + cf;
    printf("Возрастающий: Mф+Cф = %d\n", inc_500);
    
    FillDec(array, 500);
    InsertSort(array, 500);
    int dec_500 = mf + cf;
    printf("Убывающий:    Mф+Cф = %d\n", dec_500);
    
    FillRand(array, 500);
    InsertSort(array, 500);
    int rand_500 = mf + cf;
    printf("Случайный:    Mф+Cф = %d\n", rand_500);
    
    // Вывод таблицы
    Timetabl();
    
    printf("\n\nРЕЗУЛЬТАТЫ ДЛЯ ВАШЕЙ ТАБЛИЦЫ:\n");
    printf("-----------------------------------------\n");
    printf("|  N  |  M + C  |   M(факт) + C(факт)   |\n");
    printf("|     |  теор   |Убыв. | Возраст. |Случ.|\n");
    printf("|-----|---------|------|----------|------|\n");
    printf("| 100 |   %3d   | %4d |   %4d   | %4d |\n", c + m, dec_100, inc_100, rand_100);
    printf("| 200 |   %4d  | %4d |   %4d   | %4d |\n", c + m, dec_200, inc_200, rand_200);
    printf("| 300 |   %4d  | %4d |   %4d   | %4d |\n", c + m, dec_300, inc_300, rand_300);
    printf("| 400 |   %4d  | %4d |   %4d   | %4d |\n", c + m, dec_400, inc_400, rand_400);
    printf("| 500 |   %4d  | %4d |   %4d   | %4d |\n", c + m, dec_500, inc_500, rand_500);
    printf("-----------------------------------------\n");
    
    return 0;
}