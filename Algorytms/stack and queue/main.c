#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    struct Node *next;
    int data;
} Node;

typedef struct Stack {
    Node *top;
}Stack;

typedef struct Queue {
    Node *front;
    Node *rear;
}Queue;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error\n");
    }
    newNode ->data = data;
    newNode ->next = NULL;
    return newNode;
}
void initStack(Stack *s) {
    s ->top = NULL;
}
void push(Stack *s, int data) {
    Node *newNode = createNode(data);
    newNode->next = s->top;
    s -> top = newNode;
}
void ControlSumStack(Stack *s) {
    Node* current = s->top;
    int sum = 0;
    printf("Контрольная сумма: ");
    while (current != NULL) {
        sum+= current->data;
        current = current->next;
    }
    printf("%d\n", sum);
}
void SeriesStack(Stack *s){
    Node* current = s->top;
    int series = 1;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    printf("Кол-во серий: %d\n", series);
}
void printStack(Stack* s) {
    Node* current = s->top;
    printf("Стек: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void fillIncStack(int size, Stack *s) {
    initStack(s);
    for (int i =1; i <= size; i++) {
        push(s, i);
    }
}
void fillDecStack(int size, Stack *s) {
    initStack(s);
    for (int i = size; i > 0; i--) {
        push(s, i);
    }
}
void fillRandStack(int size, Stack *s) {
    initStack(s);
    for (int i =1; i <= size; i++) {
        int a = rand() % 100;
        push(s, a);
    }
}

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}
void pushQueue(Queue *q,int data) {
    Node *newNode = createNode(data);
    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
void fillIncQueue(Queue *q, int size) {
    initQueue(q);   
    for(int i = 1; i <= size; i++) {
        pushQueue(q, i);
    }
}
void fillDecQueue(Queue *q, int size) {
    initQueue(q);
    for(int i = size; i > 0; i--) {
        pushQueue(q, i);
    }
}
void fillRandQueue(Queue *q, int size) {
    initQueue(q);
    for(int i = 1; i <= size; i++) {
        int a = rand()%100;
        pushQueue(q, a);
    }
}
void printQueue(Queue* q) {
    Node* current = q->front;
    printf("Очередь: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void ControlSumQueue(Queue* q) {
    Node* current = q->front;
    int sum = 0;
    printf("Контрольная сумма: ");
    while (current != NULL) {
        sum+= current->data;
        current = current->next;
    }
    printf("%d\n", sum);
}
void SeriesQueue(Queue* q) {
    Node* current = q->front;
    int series = 1;
    
    while (current->next != NULL) {

        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    
    printf("Кол-во серий: %d\n", series);
}

void deleteList(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("Список полностью удален\n");
}

void deleteStack(Stack* s) {
    deleteList(&(s->top));
}

void deleteQueue(Queue* q) {
    deleteList(&(q->front));
    q->rear = NULL;
}

int main() {
    srand(time(NULL));
    Stack s;
    printf("======================Стек======================\n");
    fillIncStack(10, &s);
    printStack(&s);
    ControlSumStack(&s);
    SeriesStack(&s);
    deleteStack(&s);
    printf("================================================\n");
    Stack s2;
    fillDecStack(10, &s2);
    printStack(&s2);
    ControlSumStack(&s2);
    SeriesStack(&s2);
    deleteStack(&s2);
    printf("================================================\n");
    Stack s3;
    fillRandStack(10, &s3);
    printStack(&s3);
    ControlSumStack(&s3);
    SeriesStack(&s3);
    deleteStack(&s3);
    printf("=====================Очередь=====================\n");
    Queue q1;
    fillIncQueue(&q1, 10);
    printQueue(&q1);
    ControlSumQueue(&q1);
    SeriesQueue(&q1);
    deleteQueue(&q1);
    printf("================================================\n");
    Queue q2;
    fillDecQueue(&q2, 10);
    printQueue(&q2);
    ControlSumQueue(&q2);
    SeriesQueue(&q2);
    deleteQueue(&q2);
    printf("================================================\n");
    Queue q3;
    fillRandQueue(&q3, 10);
    printQueue(&q3);
    ControlSumQueue(&q3);
    SeriesQueue(&q3);
    deleteQueue(&q3);
    printf("================================================\n");
    
}