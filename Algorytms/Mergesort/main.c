#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Statistics {
    long long comparisons;
    long long moves;
} Stats;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

void printList(Node* head, const char* name) {
    printf("%s: ", name);
    int count = 0;
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
        count++;
        if (count > 50) {
            printf("...");
            break;
        }
    }
    printf("\nКоличество элементов: %d\n", count);
}

void splitList(Node* source, Node** list1, Node** list2) {
    int index = 0;
    Node* current = source;
    
    while (current) {
        if (index % 2 == 0) {
            append(list1, current->data);
        } else {
            append(list2, current->data);
        }
        current = current->next;
        index++;
    }
}

int countNodes(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

long long checksum(Node* head) {
    long long sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

int countSeries(Node* head) {
    if (!head) return 0;
    int series = 1;
    Node* current = head;
    
    while (current && current->next) {
        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    return series;
}

Node* mergeSeries(Node* list1, Node* list2, Stats* stats) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;
    
    while (list1 && list2) {
        stats->comparisons++;
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
            stats->moves++;
        } else {
            tail->next = list2;
            list2 = list2->next;
            stats->moves++;
        }
        tail = tail->next;
    }
    
    if (list1) {
        tail->next = list1;
        while (list1) {
            stats->moves++;
            list1 = list1->next;
        }
    }
    if (list2) {
        tail->next = list2;
        while (list2) {
            stats->moves++;
            list2 = list2->next;
        }
    }
    
    return dummy.next;
}

void splitListForMerge(Node* source, Node** front, Node** back) {
    Node* slow = source;
    Node* fast = source->next;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Node* mergeSort(Node* head, Stats* stats) {
    if (!head || !head->next) return head;
    
    Node* left = NULL;
    Node* right = NULL;
    
    splitListForMerge(head, &left, &right);
    
    left = mergeSort(left, stats);
    right = mergeSort(right, stats);
    
    return mergeSeries(left, right, stats);
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* createListFromArray(int arr[], int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        append(&head, arr[i]);
    }
    return head;
}

void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void fillAscending(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void fillDescending(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

int theoreticalComplexity(int n) {
    return n * (int)(log2(n)) + n;
}

void testSplitting() {
    printf("\n========== ПРОВЕРКА РАСЩЕПЛЕНИЯ СПИСКА ==========\n");
    
    Node* source = NULL;
    Node* list1 = NULL;
    Node* list2 = NULL;
    
    printf("Создание исходного списка (20 элементов):\n");
    for (int i = 1; i <= 20; i++) {
        append(&source, i);
    }
    printList(source, "Исходный список");
    
    splitList(source, &list1, &list2);
    
    printf("\nПосле расщепления (через один элемент):\n");
    printList(list1, "Список 1 (четные позиции)");
    printList(list2, "Список 2 (нечетные позиции)");
    
    printf("\nКонтрольная сумма исходного списка: %lld\n", checksum(source));
    printf("Контрольная сумма списка 1: %lld\n", checksum(list1));
    printf("Контрольная сумма списка 2: %lld\n", checksum(list2));
    
    freeList(source);
    freeList(list1);
    freeList(list2);
}

void testMerging() {
    printf("\n========== ПРОВЕРКА СЛИЯНИЯ СЕРИЙ ==========\n");
    
    Node* list1 = NULL;
    Node* list2 = NULL;
    Stats stats = {0, 0};
    
    printf("Создание двух отсортированных списков:\n");
    int arr1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int arr2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    
    for (int i = 0; i < 10; i++) append(&list1, arr1[i]);
    for (int i = 0; i < 10; i++) append(&list2, arr2[i]);
    
    printList(list1, "Список 1");
    printList(list2, "Список 2");
    
    Node* merged = mergeSeries(list1, list2, &stats);
    printList(merged, "Результат слияния");
    
    printf("\nСтатистика слияния:\n");
    printf("  Количество серий в результате: %d\n", countSeries(merged));
    printf("  Контрольная сумма: %lld\n", checksum(merged));
    printf("  Количество сравнений (Сф): %lld\n", stats.comparisons);
    printf("  Количество перемещений (Мф): %lld\n", stats.moves);
    printf("  Сф + Мф: %lld\n", stats.comparisons + stats.moves);
    
    int theoretical = 20 * (int)(log2(20)) + 20;
    printf("  Теоретическая оценка для слияния: %d\n", theoretical);
    
    freeList(merged);
}

typedef struct {
    int n;
    long long ascending;
    long long descending;
    long long random;
} TestResult;

long long testMergeSortWithResult(int n, int type) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 0;
    
    Stats stats = {0, 0};
    
    switch(type) {
        case 0: fillAscending(arr, n); break;
        case 1: fillDescending(arr, n); break;
        case 2: fillRandom(arr, n); break;
    }
    
    Node* head = createListFromArray(arr, n);
    head = mergeSort(head, &stats);
    
    long long result = stats.comparisons + stats.moves;
    
    freeList(head);
    free(arr);
    
    return result;
}

void printTable() {
    int sizes[] = {100, 200, 300, 400, 500};
    int numSizes = 5;
    TestResult results[5];
    
    for (int i = 0; i < numSizes; i++) {
        results[i].n = sizes[i];
        results[i].ascending = testMergeSortWithResult(sizes[i], 0);
        results[i].descending = testMergeSortWithResult(sizes[i], 1);
        results[i].random = testMergeSortWithResult(sizes[i], 2);
    }
    
    printf("\n\n");
    printf("                               ТАБЛИЦА MERGESORT                             \n");
    printf("--------------------------------------------------------------------\n");
    printf("|   N   |  M+C теоретич. |     Фактическая трудоемкость (Мф+Сф)    |\n");
    printf("|       |                |-------------------------------------------\n");
    printf("|       |                |  Убывающий |  Случайный |  Возрастающий   |\n");
    printf("|-------|----------------|------------------------------------------|\n");
    
    for (int i = 0; i < numSizes; i++) {
        printf("| %5d | %14d | %10lld | %10lld | %14lld |\n",
               results[i].n,
               theoreticalComplexity(results[i].n),
               results[i].descending,
               results[i].random,
               results[i].ascending);
    }
    
    printf("---------------------------------------------------------------------\n");
}

int main() {
    srand(time(NULL));
    
    testSplitting();
    testMerging();
    printTable();
    
}