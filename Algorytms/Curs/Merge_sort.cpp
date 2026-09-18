#include <iostream>
#include <string>
#include <fstream>
#define N 4000

using namespace std;

#pragma pack(push, 1)
struct FileEmployee {
    char fio[30];         // ФИО
    char position[22];    // первые 2 байта служебные (не текст), текст должности в оставшихся 20
    short tabNumber;      // табельный номер (в тестовой базе не содержит валидных значений)
    char birthDate[10];   // дата в формате "ДД-ММ-ГГ"
};
#pragma pack(pop)

struct Employee {
    string fio;
    string tabNumber;
    string position;
    string birthDate;
};

struct Node {
    Node* next;
    Employee data;
};

struct Queue {
    Node* head;
    Node* tail;
};

void initQueue(Queue* q) {
    q->head = nullptr;
    q->tail = nullptr;
}

void pushQueue(Queue* q, Employee data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (q->head == nullptr) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

// Обрезка пробелов/нулей по краям поля
string trimField(const char* source, size_t size) {
    size_t start = 0, end = size;
    while (start < end && (unsigned char)source[start] <= 0x20) start++;
    while (end > start && ((unsigned char)source[end - 1] <= 0x20)) end--;
    return string(source + start, end - start);
}

string trimPositionField(const char* source, size_t size) {
    const size_t skip = 2;
    if (size <= skip) return "";
    return trimField(source + skip, size - skip);
}

string formatBirthDate(const string& rawDate) {
    if (rawDate.length() < 8 || rawDate[2] != '-' || rawDate[5] != '-') {
        return rawDate;
    }
    string dd = rawDate.substr(0, 2);
    string mm = rawDate.substr(3, 2);
    string yy = rawDate.substr(6, 2);
    string yearPrefix = (stoi(yy) > 26) ? "19" : "20";
    return dd + "." + mm + "." + yearPrefix + yy;
}

int fillQueueFromBinary(Queue* q) {
    ifstream file("/Users/novi4ek/projects/testBase2.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }

    initQueue(q);
    FileEmployee rawData;
    int validRecords = 0;

    while (file.read(reinterpret_cast<char*>(&rawData), sizeof(FileEmployee))) {
        Employee emp;
        emp.fio = trimField(rawData.fio, sizeof(rawData.fio));
        emp.position = trimPositionField(rawData.position, sizeof(rawData.position));
        emp.birthDate = formatBirthDate(trimField(rawData.birthDate, sizeof(rawData.birthDate)));

        emp.tabNumber = to_string(rawData.tabNumber);

        pushQueue(q, emp);
        validRecords++;
    }

    file.close();
    cout << "\x93\xE1\xAF\xA5\xE8\xAD\xAE\x20\xAF\xE0\xAE\xE7\xA8\xE2\xA0\xAD\xAE\x20\xA7\xA0\xAF\xA8\xE1\xA5\xA9\x3A\x20" << validRecords << endl;
    return validRecords;
}

int getSize(Queue* q) {
    int count = 0;
    Node* p = q->head;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

void printQueue(Queue* q, int limit) {
    Node* current = q->head;
    int i = 0;
    while (current != nullptr && i < limit) {
        cout << "=============================" << endl;
        cout << "\x94\x88\x8E\x3A\x20 " << current->data.fio << endl;
        cout << "\x92\xA0\xA1\x2E\x20\xAD\xAE\xAC\xA5\xE0\x3A\x20 " << current->data.tabNumber << endl;
        cout << "\x84\xAE\xAB\xA6\xAD\xAE\xE1\xE2\xEC\x3A\x20 " << current->data.position << endl;
        cout << "\x84\xA0\xE2\xA0\x20\xE0\xAE\xA6\xAB\xA5\xAD\xA8\xEF\x3A\x20 " << current->data.birthDate << endl;
        current = current->next;
        i++;
    }
}

bool isEmpty(Queue* q) {
    return q->head == nullptr;
}

Employee dequeue(Queue* q) {
    if (isEmpty(q)) {
        return Employee{};
    }
    Node* temp = q->head;
    Employee data = temp->data;
    q->head = q->head->next;
    if (q->head == nullptr) {
        q->tail = nullptr;
    }
    delete temp;
    return data;
}

void Split(Queue* q, Queue* first, Queue* sec) {
    int n = getSize(q);
    if (n == 0) return;

    int half = n / 2;
    Node* curr = q->head;

    first->head = curr;
    for (int i = 0; i < half - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }

    if (curr != nullptr) {
        first->tail = curr;
        sec->head = curr->next;
        curr->next = nullptr;
    }

    if (sec->head != nullptr) {
        Node* p = sec->head;
        while (p->next != nullptr) {
            p = p->next;
        }
        sec->tail = p;
    } else {
        sec->tail = nullptr;
    }

    q->head = nullptr;
    q->tail = nullptr;
}

bool lessThan(const Employee& a, const Employee& b) {
    int numA = stoi(a.tabNumber);
    int numB = stoi(b.tabNumber);
    if (numA != numB) {
        return numA < numB;
    }
    return a.fio < b.fio;
}

Queue* Merge(Queue* first, Queue* sec) {
    Queue* result = new Queue();
    initQueue(result);

    Node* f = first->head;
    Node* s = sec->head;

    while (f != nullptr && s != nullptr) {
        Node* moveNode = nullptr;
        if (lessThan(f->data, s->data)) {
            moveNode = f;
            f = f->next;
        } else {
            moveNode = s;
            s = s->next;
        }

        moveNode->next = nullptr;
        if (result->head == nullptr) {
            result->head = moveNode;
            result->tail = moveNode;
        } else {
            result->tail->next = moveNode;
            result->tail = moveNode;
        }
    }

    while (f != nullptr) {
        Node* nextNode = f->next;
        f->next = nullptr;
        if (result->head == nullptr) {
            result->head = f;
            result->tail = f;
        } else {
            result->tail->next = f;
            result->tail = f;
        }
        f = nextNode;
    }

    while (s != nullptr) {
        Node* nextNode = s->next;
        s->next = nullptr;
        if (result->head == nullptr) {
            result->head = s;
            result->tail = s;
        } else {
            result->tail->next = s;
            result->tail = s;
        }
        s = nextNode;
    }

    return result;
}

void Merge_sort(Queue* q) {
    int size = getSize(q);
    if (size <= 1) return;

    Queue first, sec;
    initQueue(&first);
    initQueue(&sec);

    Split(q, &first, &sec);

    Merge_sort(&first);
    Merge_sort(&sec);

    Queue* merged = Merge(&first, &sec);

    q->head = merged->head;
    q->tail = merged->tail;

    delete merged;
}

void clearQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    Queue employeeQueue;
    initQueue(&employeeQueue);

    int count = fillQueueFromBinary(&employeeQueue);
    if (count == 0) {
        cout << "\x8D\xA5\xE2\x20\xA4\xA0\xAD\xAD\xEB\xE5\x20\xA4\xAB\xEF\x20\xE1\xAE\xE0\xE2\xA8\xE0\xAE\xA2\xAA\xA8" << endl;
        return 1;
    }

    cout << "\x88\xE1\xE5\xAE\xA4\xAD\xA0\xEF\x20\xA1\xA0\xA7\xA0\x20\xA4\xA0\xAD\xAD\xEB\xE5\x20\x28\xAF\xA5\xE0\xA2\xEB\xA5\x20\x32\x30\x20\xA7\xA0\xAF\xA8\xE1\xA5\xA9\x29\x3A" << endl;
    printQueue(&employeeQueue, 20);
    cout << endl << "\x8F\xAE\xE1\xAB\xA5\x20\xE1\xAE\xE0\xE2\xA8\xE0\xAE\xA2\xAA\xA8\x20\x28\xAF\xA5\xE0\xA2\xEB\xA5\x20\x32\x30\x20\xA7\xA0\xAF\xA8\xE1\xA5\xA9\x29\x3A" << endl;
    Merge_sort(&employeeQueue);
    printQueue(&employeeQueue, 20);
    clearQueue(&employeeQueue);
    return 0;
}