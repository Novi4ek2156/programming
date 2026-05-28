#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct contact {
    char name[32];
    char surname[32];
    char otchestvo[32];
    int number;
};
typedef struct contact contact;


int key1 = 0;  // 0 - фамилия, 1 - имя, 2 - отчество, 3 - номер
int key2 = 1;
int key3 = 2;
int direction = 1;  // 1 - по возрастанию, -1 - по убыванию


int compareStr(const char* a, const char* b) {
    return strcmp(a, b) * direction;
}

// Функция сравнения чисел
int compareInt(int a, int b) {
    return (a - b) * direction;
}

// Функция сравнения двух контактов по составному ключу
int less(const contact* a, const contact* b) {
    if (a->surname < b->surname){
        return 1;
    } else if (a->name > b->name){
        return 0;
    } else if (a->otchestvo < b->otchestvo){
        return 1;
    }
    return 0;
}



void SelectSortContacts(contact* array, int N) {
    for (int i = 0; i < N - 1; i++) {
        int k = i;
        for (int j = i + 1; j < N; j++) {
            int res = strcmp(array[j].surname, array[k].surname);
            
            if (res < 0) { 
                k = j;
            } 
            else if (res == 0) { 
                int resName = strcmp(array[j].name, array[k].name);
                if (resName < 0) {
                    k = j;
                } 
                else if (resName == 0) {
                    if (strcmp(array[j].otchestvo, array[k].otchestvo) < 0) {
                        k = j;
                    }
                }
            }
        }
        if (i != k) {
            contact term = array[i];
            array[i] = array[k];
            array[k] = term;
        }
    }
}



contact* newcontact(const char* name, const char* surname, const char* otchestvo, int number) {
    contact* new = (contact*)malloc(sizeof(contact));
    if (new != NULL) {
        strcpy(new->name, name);
        strcpy(new->surname, surname);
        strcpy(new->otchestvo, otchestvo);
        new->number = number;
    }
    return new;
}


void printContact(const contact* c) {
    printf("%-12s %-12s %-15s %-10d\n", 
           c->surname, c->name, c->otchestvo, c->number);
}

// Вывод всех контактов
void printAll(contact* arr[], int n, const char* title) {
    printf("\n=== %s ===\n", title);
    printf("----------------------------------------\n");
    printf("%-12s %-12s %-15s %-10s\n", "Фамилия", "Имя", "Отчество", "Телефон");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printContact(arr[i]);
    }
    printf("----------------------------------------\n");
}

// Освобождение памяти
void freeContacts(contact* arr[], int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
}

// Показать настройки сортировки
void showSettings() {
    const char* fields[] = {"Фамилия", "Имя", "Отчество", "Номер"};
    const char* dir = (direction == 1) ? "По возрастанию" : "По убыванию";
    
    printf("\n--- Настройки сортировки ---\n");
    printf("1 ключ: %s\n", fields[key1]);
    printf("2 ключ: %s\n", fields[key2]);
    printf("3 ключ: %s\n", fields[key3]);
    printf("Направление: %s\n", dir);
    printf("----------------------------\n");
}

int main() {
    // Создаем массив контактов
    contact* sprav[5];
    
    sprav[0] = newcontact("Владислав", "Семёнов", "Юрьевич", 1234567);
    sprav[1] = newcontact("Никита", "Метляев", "Сергеевич", 2345678);
    sprav[2] = newcontact("Алексей", "Сидоров", "Иванович", 3456789);
    sprav[3] = newcontact("Юрий", "Семёнов", "Алексеевич", 4567890);
    sprav[4] = newcontact("Иван", "Кузнецов", "Сергеевич", 5678901);
    
    int n = 5;
    int choice;
    
    printf("ТЕЛЕФОННЫЙ СПРАВОЧНИК\n");
    printAll(sprav, n, "ИСХОДНЫЙ");
    
    do {
        printf("\n--- МЕНЮ ---\n");
        printf("1 - Сортировать\n");
        printf("2 - Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            
            contact* copy[5];
            for (int i = 0; i < n; i++) {
                copy[i] = newcontact(sprav[i]->name, sprav[i]->surname, 
                                     sprav[i]->otchestvo, sprav[i]->number);
            }
            
            // Преобразуем массив указателей в массив структур для сортировки
            contact arr[5];
            for (int i = 0; i < n; i++) {
                arr[i] = *copy[i];
            }
            
            // Сортируем
            SelectSortContacts(arr, n);
            
            // Выводим результат
            printf("\n=== ОТСОРТИРОВАННЫЙ ===\n");
            printf("----------------------------------------\n");
            printf("%-12s %-12s %-15s %-10s\n", "Фамилия", "Имя", "Отчество", "Телефон");
            printf("----------------------------------------\n");
            for (int i = 0; i < n; i++) {
                printContact(&arr[i]);
            }
            printf("----------------------------------------\n");
            
            // Освобождаем копии
            freeContacts(copy, n);
        }
        
    } while (choice != 2);
    
    // Освобождаем память
    freeContacts(sprav, n);
    
    return 0;
}