#include <iostream>
using namespace std;

class CQueue {
private:
    int* data;
    int front, rear;
    int capacity;
public:
    CQueue(int size) {
        capacity = size + 1; 
        data = new int[capacity];
        front = rear = 0;
    }
    
    ~CQueue() {
        delete[] data;
    }
    
    bool isEmpty() {
        return front == rear;
    }
    
    bool isFull() {
        return (rear + 1) % capacity == front;
    }
    
    bool enqueue(int val) {
        if (isFull()) return false;
        data[rear] = val;
        rear = (rear + 1) % capacity;
        return true;
    }
    
    bool dequeue(int& val) {
        if (isEmpty()) return false;
        val = data[front];
        front = (front + 1) % capacity;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return data[front];
    }
    
    void print() {
        int i = front;
        while (i != rear) {
            cout << data[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

class Stack {
private:
    int* data;
    int top;
    int capacity;
public:
    Stack(int size) {
        capacity = size;
        data = new int[capacity];
        top = -1;
    }
    
    ~Stack() {
        delete[] data;
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == capacity - 1;
    }
    
    bool push(int val) {
        if (isFull()) return false;
        data[++top] = val;
        return true;
    }
    
    bool pop(int& val) {
        if (isEmpty()) return false;
        val = data[top--];
        return true;
    }
};

int main() {
    int n, val;
    cin >> n;
    
    CQueue q(n);
    Stack s(n);
    
    for (int i = 0; i < n; i++) {
        cin >> val;
        q.enqueue(val);
    }
    
    for (int i = 0; i < n; i++) {
        q.dequeue(val);
        s.push(val);
    }
    
    for (int i = 0; i < n; i++) {
        s.pop(val);
        q.enqueue(val);
    }
    
    q.print();
    
    return 0;
}