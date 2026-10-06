/* Circular Queue: insert, delete, display using array */
#include <stdio.h>
#define SIZE 5

int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) {          /* full check */
        printf("Queue is FULL\n");
        return;
    }
    if (front == -1) front = rear = 0;          /* first element */
    else rear = (rear + 1) % SIZE;
    queue[rear] = item;
    printf("Inserted %d\n", item);
}

void delete(void) {
    if (front == -1) { printf("Queue is EMPTY\n"); return; }
    printf("Deleted %d\n", queue[front]);
    if (front == rear) front = rear = -1;      /* queue became empty */
    else front = (front + 1) % SIZE;
}

void display(void) {
    int i;
    if (front == -1) { printf("Queue is EMPTY\n"); return; }
    printf("Queue: ");
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
    printf("\n");
}

int main() {
    insert(10); insert(20); insert(30); insert(40); insert(50); /* full */
    display();
    delete(); delete();                                          /* wrap-around */
    insert(60); insert(70);                                      /* reuses freed slots */
    display();
    return 0;
}
