#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *names_rooms[3] = {"xleb","kumis","salo"};
struct room{
    char *name;
    int level;
    int number;
    int resolution;
};

struct node {
    struct room room;
    struct node* next;

};
typedef struct node node_t;

node_t *newNode(struct room room) {

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->room = room;
    new_node->next = NULL;

    return new_node;
}
node_t* appendBack(node_t* head, struct room room)
{
    node_t* new_node = newNode(room);

    if (head == NULL) {
        head = new_node;
        return new_node;
    }

    node_t* cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new_node;

    return head;
}
void printList(node_t *head) {

    node_t* cur = head;
    while (cur) {
        printf("%d -> ", cur->room.number);
        cur = cur->next;
    }
    printf("NULL\n");
}

int main() {
    srand(time(NULL));
    int n;
    printf("Введите кол-во элементов: ");
    scanf("%d", &n);
    struct room room;
    node_t *head = NULL;
    struct node array[n];
    for (int i =0; i < n; i++) {
        int random = rand()%3;
        int rand_level = i;
        int rand_number = i+1;
        int rand_resolution = rand()%100;
        room.name = names_rooms[random];
        room.level = i;
        room.number = rand_number;
        room.resolution = rand_resolution;
        //array[i].room = room;
        node_t *tmp = newNode(room);
        if (head ==NULL) {
            head = tmp;
        } else {
            node_t *cur = head;
            while(cur->next != NULL){
                cur = cur ->next;

            }
            cur->next = tmp;
        }
        node_t* t = array ->next;
        // printList(t);    
    }
    printList(head);
     
}