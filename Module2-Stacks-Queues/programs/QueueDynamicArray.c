/* Queue represented using a dynamically allocated array (grows via realloc).
   Answers: "Define Queue. Discuss how to represent queue using dynamic arrays" */
#include <stdio.h>
#include <stdlib.h>

int *queue;
int front = -1, rear = -1;
int capacity = 2;

void insert(int item) {
    if (rear == capacity - 1) {                 /* full: grow the array */
        capacity *= 2;
        queue = (int*) realloc(queue, capacity * sizeof(int));
        printf("(capacity doubled to %d)\n", capacity);
    }
    queue[++rear] = item;
    if (front == -1) front = 0;
}

int deleteFront() {
    if (front == -1 || front > rear) { printf("Queue is empty\n"); return -1; }
    int item = queue[front++];
    if (front > rear) front = rear = -1;
    return item;
}

int main() {
    queue = (int*) malloc(capacity * sizeof(int));
    for (int i = 1; i <= 5; i++) insert(i * 10);   /* triggers doubling as it grows */

    printf("Queue: ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");

    free(queue);
    return 0;
}
