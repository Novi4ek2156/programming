#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NAME 12
#define MAX_RECORDS 5

// Структура записи телефонного справочника
typedef struct {
    char lastName[30];
    char firstName[30];
    char phone[15];
    char city[30];
} PhoneRecord;

int compareByLastName(const void *a, const void *b) {
    PhoneRecord *recA = *(PhoneRecord**)a;
    PhoneRecord *recB = *(PhoneRecord**)b;
    return strcmp(recA->lastName, recB->lastName);
}
int compareByCity(const void *a, const void *b) {
    PhoneRecord *recA = *(PhoneRecord**)a;
    PhoneRecord *recB = *(PhoneRecord**)b;
    return strcmp(recA->city, recB->city);
}

void selectSort(char *ptrArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (*ptrArray[j] < *ptrArray[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            char *temp = ptrArray[i];
            ptrArray[i] = ptrArray[minIndex];
            ptrArray[minIndex] = temp;
        }
    }
}

void printPointerArray(char *ptrArray[], int n, const char* title) {
    printf("\n%s:\n", title);
    printf("%-5s %-20s %-10s %-15s\n", "Индекс", "Адрес указателя", "Значение", "Исходная позиция");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (ptrArray[i] != NULL) {
            printf("%-5d %-20p '%c' %-15ld\n", 
                   i, (void*)&ptrArray[i], *ptrArray[i], ptrArray[i] - ptrArray[0]);
        }
    }
}

void printPointerArrayStruct(PhoneRecord *ptrArray[], int n, const char* title, int field) {
    printf("\n%s:\n", title);
    printf("%-5s %-20s %-30s\n", "Индекс", "Адрес указателя", "Значение");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (field == 0) {
            printf("%-5d %-20p %s\n", i, (void*)&ptrArray[i], ptrArray[i]->lastName);
        } else {
            printf("%-5d %-20p %s\n", i, (void*)&ptrArray[i], ptrArray[i]->city);
        }
    }
}

void selectSortByLastName(PhoneRecord *ptrArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(ptrArray[j]->lastName, ptrArray[minIndex]->lastName) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            PhoneRecord *temp = ptrArray[i];
            ptrArray[i] = ptrArray[minIndex];
            ptrArray[minIndex] = temp;
        }
    }
}

void selectSortByCity(PhoneRecord *ptrArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(ptrArray[j]->city, ptrArray[minIndex]->city) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            PhoneRecord *temp = ptrArray[i];
            ptrArray[i] = ptrArray[minIndex];
            ptrArray[minIndex] = temp;
        }
    }
}

void buildIndexArrays(char *arr, int n) {
    printf("\n========== ИСХОДНЫЕ ДАННЫЕ ==========\n");
    printf("Исходный массив символов:\n");
    printf("%-5s %-15s %-10s\n", "Позиция", "Адрес", "Символ");
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-15p '%c'\n", i + 1, (void*)(arr + i), *(arr + i));
    }
    
    char *ptrAsc[12];
    for (int i = 0; i < n; i++) {
        ptrAsc[i] = arr + i;
    }
    printPointerArray(ptrAsc, n, "МАССИВ УКАЗАТЕЛЕЙ ДО СОРТИРОВКИ");
    
    selectSort(ptrAsc, n);
    
    printPointerArray(ptrAsc, n, "МАССИВ УКАЗАТЕЛЕЙ ПОСЛЕ СОРТИРОВКИ");
    
    printf("\nМассив символов после сортировки:\n");
    for (int i = 0; i < n; i++) {
        printf("%c ", *(ptrAsc[i]));
    }
    printf("\n");
}

void printOriginalPhoneBook(PhoneRecord phoneBook[], int n) {
    printf("\n========== ИСХОДНЫЙ ТЕЛЕФОННЫЙ СПРАВОЧНИК ==========\n");
    printf("%-3s %-20s %-20s %-15s %-20s %-15s\n", 
           "№", "Адрес записи", "Фамилия", "Имя", "Телефон", "Город");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-20p %-20s %-15s %-20s %-15s\n", 
               i + 1, 
               (void*)&phoneBook[i],
               phoneBook[i].lastName, 
               phoneBook[i].firstName,
               phoneBook[i].phone,
               phoneBook[i].city);
    }
}

// Функция вывода справочника через массив указателей
void printPhoneBookByPointers(PhoneRecord *ptrArray[], int n, const char* title) {
    printf("\n=== %s ===\n", title);
    printf("%-3s %-20s %-20s %-15s %-20s %-15s\n", 
           "№", "Адрес указателя", "Фамилия", "Имя", "Телефон", "Город");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-20p %-20s %-15s %-20s %-15s\n", 
               i + 1, 
               (void*)&ptrArray[i],
               ptrArray[i]->lastName, 
               ptrArray[i]->firstName,
               ptrArray[i]->phone,
               ptrArray[i]->city);
    }
}

int main() {
    // Исходный массив записей (5 записей)
    PhoneRecord phoneBook[MAX_RECORDS] = {
        {"Семёнов", "Владислав", "+7-912-345-6789", "Новосибирск"},
        {"Семёнов", "Юрий", "+7-921-456-7890", "Новосибирск"},
        {"Сидоров", "Петр", "+7-902-567-8901", "Москва"},
        {"Кузнецова", "Елена", "+7-911-678-9012", "Екатеринбург"},
        {"Метляев", "Никита", "+7-922-789-0123", "Братск"}
    };
    
    int n = MAX_RECORDS;
    
    // Вывод исходного справочника
    printOriginalPhoneBook(phoneBook, n);
   
 
    PhoneRecord *ptrByLastName[MAX_RECORDS];
    PhoneRecord *ptrByCity[MAX_RECORDS];
    
   
    for (int i = 0; i < n; i++) {
        ptrByLastName[i] = &phoneBook[i];
        ptrByCity[i] = &phoneBook[i];
    }
    
    printf("\n========== МАССИВЫ УКАЗАТЕЛЕЙ ДО СОРТИРОВКИ ==========");
    printPointerArrayStruct(ptrByLastName, n, "Массив указателей для сортировки по фамилии (ДО)", 0);
    printPointerArrayStruct(ptrByCity, n, "Массив указателей для сортировки по городу (ДО)", 1);
    
    printf("\n========== ВЫПОЛНЯЕМ СОРТИРОВКУ SELECTSORT ==========\n");
    printf("Сортируем по фамилии...\n");
    selectSortByLastName(ptrByLastName, n);
    printf("Сортируем по городу...\n");
    selectSortByCity(ptrByCity, n);
    
    printf("\n========== МАССИВЫ УКАЗАТЕЛЕЙ ПОСЛЕ СОРТИРОВКИ SELECTSORT ==========");
    printPointerArrayStruct(ptrByLastName, n, "Массив указателей для сортировки по фамилии", 0);
    printPointerArrayStruct(ptrByCity, n, "Массив указателей для сортировки по городу", 1);
    
    printPhoneBookByPointers(ptrByLastName, n, "СПРАВОЧНИК, ОТСОРТИРОВАННЫЙ ПО ФАМИЛИИ");
    printPhoneBookByPointers(ptrByCity, n, "СПРАВОЧНИК, ОТСОРТИРОВАННЫЙ ПО ГОРОДУ");
    
    return 0;
}