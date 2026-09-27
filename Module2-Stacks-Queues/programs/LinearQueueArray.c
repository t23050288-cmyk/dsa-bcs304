/* Linear queue using array: insertion, deletion, display.
   Answers: "Develop a C program to implement insertion, deletion and display
             operations on Linear queue" */
#include <stdio.h>
#define MAX_QUEUE_SIZE 5

int queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void insert(int item) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full, cannot insert %d\n", item);
        return;
    }
    queue[++rear] = item;
    if (front == -1) front = 0;    /* first element inserted */
}

int deleteFront() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue[front++];
    if (front > rear) front = rear = -1;   /* queue emptied, reset */
    return item;
}

void display() {
    if (front == -1 || front > rear) { printf("Queue is empty\n"); return; }
    printf("Queue (front to rear): ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    display();

    printf("Deleted: %d\n", deleteFront());
    display();

    return 0;
}
