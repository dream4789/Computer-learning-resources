//
// Created by xulon on 2023/6/25.
//
#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

class CircularQueue {
private:
    int data[MAX_SIZE];
    int front;   // 队首指针
    int rear;    // 队尾指针
public:
    CircularQueue() {
        front = rear = 0;
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return (rear + 1) % MAX_SIZE == front;
    }

    void enqueue(int x) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        data[rear] = x;
        rear = (rear + 1) % MAX_SIZE;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int val = data[front];
        front = (front + 1) % MAX_SIZE;
        return val;
    }
};

int main() {
    CircularQueue q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
    }

    return 0;
}

// 1 2 3