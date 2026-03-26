#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Room {
    char *name;  
    int level;
    int number;
    int resolution;
} Room;

typedef struct Node {
    Room *room;
    struct Node *prev;
    struct Node *next;
    struct Node *jump; 
} Node;

typedef struct RoomHistory {
    Node *head;
    Node *tail;
    int size;
} RoomHistory;


Room *createRoom(const char *name, int number, int level, int resolution) {
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room) return NULL;
    room->level = level;
    room->number = number;
    room->resolution = resolution;
    room->name = (char *)malloc(strlen(name) + 1);
    if (room->name) strcpy(room->name, name);
    return room;
}

Node *createNode(Room *room) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->room = room;
    node->prev = node->next = node->jump = NULL; 
    return node;
}

void addToHistory(RoomHistory *h, Room *r) {
    Node *newNode = createNode(r);
    if (!h->head) {
        h->head = h->tail = newNode;
    } else {
        newNode->prev = h->tail;
        h->tail->next = newNode;
        h->tail = newNode;
    }
    h->size++;
}
void linkLists(RoomHistory *top, RoomHistory *bot) {
    Node *t = top->head;
    Node *b = bot->head;
    while (t != NULL || b != NULL) {
        if (t && b) {
            t->jump = b;
            b->jump = t;
            t = t->next;
            b = b->next;
        } else if (t) {
            t->jump = NULL; 
            t = t->next;
        } else if (b) {
            b->jump = NULL; 
            b = b->next;
        }
    }
}

void startNavigation(Node *S) {
    Node *curr = S;
    char cmd;

    while (1) {
        printf("\n------------------------------------------\n");
        printf("ТЕКУЩИЙ УЗЕЛ: [%s] №%d (Уровень: %d)\n", 
                curr->room->name, curr->room->number, curr->room->level);
        printf("Управление: W/S (прыжок), A (назад), D (вперед), Q (выход)\n");
        printf("Введите команду и нажмите Enter: ");

        if (scanf(" %c", &cmd) != 1) break; 
        
        if (cmd == 'q' || cmd == 'Q') break;

        Node *nextPos = NULL;
        if (cmd == 'd' || cmd == '6') nextPos = curr->next;
        else if (cmd == 'a' || cmd == '4') nextPos = curr->prev;
        else if (cmd == 'w' || cmd == 's' || cmd == '8' || cmd == '2') nextPos = curr->jump;

        if (nextPos) {
            curr = nextPos;
        } else {
            printf("\a[!] Ошибка: Перемещение невозможно (достигнут NULL).\n");
            if (curr->prev == NULL && (cmd == 'a' || cmd == '4')) {
                printf("Вы в самом начале. Вернуться в начало списка S? (y/n): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y') curr = S;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    char *names[] = {"xleb", "kumis", "salo"};
    int n, k;

    printf("Введите длину верхнего списка (N): ");
    scanf("%d", &n);
    printf("Введите длину нижнего списка (K): ");
    scanf("%d", &k);

    RoomHistory *topList = (RoomHistory*)calloc(1, sizeof(RoomHistory));
    RoomHistory *botList = (RoomHistory*)calloc(1, sizeof(RoomHistory));

    for (int i = 0; i < n; i++) 
        addToHistory(topList, createRoom(names[rand()%3], i+1, 1, 1080));
    for (int i = 0; i < k; i++) 
        addToHistory(botList, createRoom(names[rand()%3], i+1, 2, 720));

    linkLists(topList, botList);


    Node *S = topList->head;

    startNavigation(S);

    return 0;
}
