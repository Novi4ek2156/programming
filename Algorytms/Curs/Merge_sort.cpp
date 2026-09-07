#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define N 4000

using namespace std;

// Финальная структура с точностью до байта (ровно 64 байта)
#pragma pack(push, 1)
struct FileEmployee {
    char fio[30];         // Ровно 30 байт под ФИО (убирает мусорные буквы 'Ц', 'd' и т.д.)
    char position[22];    // Ровно 22 байта под должность
    short tabNumber;      // Ровно 2 байта под табельный номер (бинарный short)
    char birthDate[10];   // Ровно 10 байт под дату в формате "ДД-ММ-ГГ  "
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

// Очистка от пробелов и мусорных символов рамок DOS таблиц
string cleanRawString(const char* source, size_t size) {
    string str;
    for (size_t i = 0; i < size; ++i) {
        unsigned char c = source[i];
        if (c < 0x20 && c != '\0') continue;
        if (c >= 0xB0 && c <= 0xDF) continue; // Убираем псевдографику DOS
        str += c;
    }
    while (!str.empty() && (str.back() == ' ' || str.back() == '\0' || str.back() == '\r' || str.back() == '\n')) {
        str.pop_back();
    }
    size_t start = str.find_first_not_of(" ");
    if (start != string::npos) {
        str = str.substr(start);
    }
    return str;
}

// Декодер CP866 -> UTF-8 (исправлены пропущенные запятые и кавычки)
string decodeCP866ToUTF8(const string& input) {
    static const string table[256] = {
        "\x00","\x01","\x02","\x03","\x04","\x05","\x06","\x07","\x08","\x09","\x0a","\x0b","\x0c","\x0d","\x0e","\x0f",
        "\x10","\x11","\x12","\x13","\x14","\x15","\x16","\x17","\x18","\x19","\x1a","\x1b","\x1c","\x1d","\x1e","\x1f",
        " ","!","\"","#","$","%","&","'","(",")","*","+",",","-",".","/",
        "0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","?",
        "@","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
        "P","Q","R","S","T","U","V","W","X","Y","Z","[","\\","]","^","_",
        "`","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
        "p","q","r","s","t","u","v","w","x","y","z","{","|","}","~","\x7f",
        "А","Б","В","Г","Д","Е","Ж","З","И","Й","К","Л","М","Н","О","П",
        "Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ъ","Ы","Ь","Э","Ю","Я",
        "а","б","в","г","д","е","ж","з","и","й","к","л","м","н","о","п",
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
        "р","с","т","у","ф","х","ц","ч","ш","щ","ъ","ы","ь","э","ю","я",
        "Ё","ё","Є","є","Ї","ї","Ў","ў","°","∙","·","√","№","¤","■"," "
    };

    string output;
    for (unsigned char c : input) {
        output += table[c];
    }
    return output;
}

// Восстановление правильного формата даты ДД.ММ.ГГГГ из строки вида "ДД-ММ-ГГ"
string formatBirthDate(const string& rawDate) {
    if (rawDate.length() < 8 || rawDate[2] != '-' || rawDate[5] != '-') {
        return rawDate; 
    }
    string dd = rawDate.substr(0, 2);
    string mm = rawDate.substr(3, 2);
    string yy = rawDate.substr(6, 2);
    
    // Автоопределение века (если год > 26, то это 19хх, иначе 20хх)
    string yearPrefix = (stoi(yy) > 26) ? "19" : "20";
    
    return dd + "." + mm + "." + yearPrefix + yy;
}

int fillQueueFromBinary(Queue* q) {
    ifstream file("/Users/novi4ek/programming/Algorytms/Curs/testBase2.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }
    
    initQueue(q);
    FileEmployee rawData;
    int validRecords = 0;
    
    while (file.read(reinterpret_cast<char*>(&rawData), sizeof(FileEmployee))) {
        Employee emp;
        
        string rawFio = cleanRawString(rawData.fio, 30);
        string rawPos = cleanRawString(rawData.position, 22);
        string rawDate = cleanRawString(rawData.birthDate, 10);
        
        emp.fio = decodeCP866ToUTF8(rawFio);
        emp.position = decodeCP866ToUTF8(rawPos);
        emp.tabNumber = to_string(rawData.tabNumber); 
        emp.birthDate = formatBirthDate(rawDate);     
        
        pushQueue(q, emp);
        validRecords++;
    }
    
    file.close();
    cout << "Успешно прочитано записей: " << validRecords << endl;
    return validRecords;
}

void printQueue(Queue* q) {
    Node* current = q->head;
    int i = 0;
    while (current != nullptr && i < 20) {
        cout << "=============================" << endl;
        cout << "ФИО: " << current->data.fio << endl;
        cout << "Таб. номер: " << current->data.tabNumber << endl;
        cout << "Должность: " << current->data.position << endl;
        cout << "Дата рождения: " << current->data.birthDate << endl;
        current = current->next;
        i++;
    }
}

Node* createNode(Employee data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

Queue* createQueue(Queue* q, Employee data) {
    Node* newNode = createNode(data);
    if (q->head == nullptr) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    return q;
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
    int half = n / 2;
    
    // Перемещаем первую половину в first
    for (int i = 0; i < half; i++) {
        Employee emp = dequeue(q);
        createQueue(first, emp);
    }
    
    // Перемещаем вторую половину в sec
    while (!isEmpty(q)) {
        Employee emp = dequeue(q);
        createQueue(sec, emp);
    }
}

Queue* Merge(Queue* first, Queue* sec) {
    Queue* result = new Queue();
    initQueue(result);
    
    while (!isEmpty(first) && !isEmpty(sec)) {
        // Сравниваем как числа, а не как строки
        int num1 = stoi(first->head->data.tabNumber);
        int num2 = stoi(sec->head->data.tabNumber);
        
        if (num1 <= num2) {
            Employee emp = dequeue(first);
            createQueue(result, emp);
        } else {
            Employee emp = dequeue(sec);
            createQueue(result, emp);
        }
    }

    while (!isEmpty(first)) {
        Employee emp = dequeue(first);
        createQueue(result, emp);
    }
    
    while (!isEmpty(sec)) {
        Employee emp = dequeue(sec);
        createQueue(result, emp);
    }
    
    return result;
}

void Merge_sort(Queue* q) {
    int size = getSize(q);
    if (size <= 1) return;

    Queue first, sec;
    initQueue(&first);
    initQueue(&sec);

    Split(q, &first, &sec);  // q становится пустым

    Merge_sort(&first);
    Merge_sort(&sec);
    
    Queue* merged = Merge(&first, &sec);
    
    // Копируем отсортированные данные обратно в q
    while (!isEmpty(merged)) {
        Employee emp = dequeue(merged);
        createQueue(q, emp);
    }
    
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
        cout << "Нет данных для сортировки" << endl;
        return 1;
    }
    
    cout << "До сортировки (первые 20 записей):" << endl;
    printQueue(&employeeQueue);
    
    cout << endl << "После сортировки (первые 20 записей):" << endl;
    Merge_sort(&employeeQueue);
    printQueue(&employeeQueue);
    
    clearQueue(&employeeQueue);
    
    return 0;
}