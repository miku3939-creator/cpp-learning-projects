#include <iostream>
using namespace std;

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;

    void swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }

    // 向上调整（插入时用）
    void heapifyUp(int idx) {
        while (idx > 1 && heap[idx] < heap[idx / 2]) {
            swap(heap[idx], heap[idx / 2]);
            idx = idx / 2;
        }
    }

    // 向下调整（删除时用）
    void heapifyDown(int idx) {
        while (idx * 2 <= size) {
            int child = idx * 2;
            // 选较小的子节点
            if (child + 1 <= size && heap[child + 1] < heap[child]) {
                child++;
            }
            if (heap[idx] <= heap[child]) {
                break;
            }
            swap(heap[idx], heap[child]);
            idx = child;
        }
    }

public:
    MinHeap(int cap) {
        capacity = cap;
        heap = new int[capacity + 1];  // 下标从 1 开始
        size = 0;
    }

    ~MinHeap() {
        delete[] heap;
    }

    // 插入元素
    void push(int val) {
        if (size >= capacity) return;  // 堆满
        heap[++size] = val;
        heapifyUp(size);
    }

    // 取最小值
    int top() {
        if (size == 0) return -1;
        return heap[1];
    }

    // 删除最小值
    void pop() {
        if (size == 0) return;
        heap[1] = heap[size];
        size--;
        heapifyDown(1);
    }

    bool empty() {
        return size == 0;
    }
};

int main() {
    int n, op, x;
    cin >> n;
    
    MinHeap heap(n);  // 最多 n 个元素
    
    for (int i = 0; i < n; i++) {
        cin >> op;
        switch (op) {
            case 1:
                cin >> x;
                heap.push(x);
                break;
            case 2:
                if (!heap.empty()) {
                    cout << heap.top() << endl;
                }
                break;
            case 3:
                if (!heap.empty()) {
                    heap.pop();
                }
                break;
        }
    }
    
    return 0;
}