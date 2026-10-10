#include <stdio.h>
#define MAX 5
int queue[MAX], front = -1, rear = -1;
void enqueue(int x) {
    if (rear == MAX - 1) { printf("Queue Overflow\n"); return; }
    if (front == -1) front = 0;
    queue[++rear] = x;
    printf("%d inserted\n", x);
}
void dequeue() {
    if (front == -1 || front > rear) { printf("Queue Underflow\n"); return; }
    printf("%d deleted\n", queue[front++]);
    if (front > rear) front = rear = -1;
}
void display() {
    int i;
    if (front == -1) { printf("Queue is empty\n"); return; }
    printf("Queue: ");
    for (i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}
int main() {
    enqueue(10); enqueue(20); enqueue(30);
    display();
    dequeue();
    display();
    dequeue(); dequeue(); dequeue();
    return 0;
}
