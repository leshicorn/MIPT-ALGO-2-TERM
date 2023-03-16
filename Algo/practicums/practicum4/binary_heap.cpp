#include <iostream>
#include <vector>

using namespace std;

class BinaryHeap {
public:
    BinaryHeap() {}

    BinaryHeap(vector<int> elements) {
        heap = elements;
        buildHeap();
    }

    void push(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && heap[parent] > heap[i]) {
            swap(heap[i], heap[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    int pop() {
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }

    int top() const {
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

private:
    vector<int> heap;

    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    void buildHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }
};

int main() {
    BinaryHeap bh;
    bh.push(5);
    bh.push(3);
    bh.push(7);
    bh.push(2);
    bh.push(8);

    while (!bh.empty()) {
        cout << bh.pop() << " ";
    }
    cout << endl;

    return 0;
}
