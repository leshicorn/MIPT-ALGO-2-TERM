#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BinomialHeap {
public:
    /**
     * @brief Construct a new BinomialHeap object
     * 
     * @param elements 
     */
    BinomialHeap(vector<int> elements) : heap(elements) {
        buildHeap();
    }

    /**
    * @brief Sort the heap in non-decreasing order using HeapSort
    * 
    */
    void HeapSort() {
        // Build a max heap
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(i, heap.size());
        }
        // Sort the heap in non-decreasing order
        for (int i = heap.size() - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            maxHeapify(0, i);
        }
    }

    /**
     * @brief Heapify the max heap
     * 
     * @param i 
     * @param n 
     */
    void maxHeapify(int i, int n) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < n && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            maxHeapify(largest, n);
        }
    }


    /**
     * @brief Push an element into the heap
     * 
     * @param x 
     */
    void push(int x) {
        BinomialHeap h({x});
        merge(h);
    }

    /**
     * @brief Pop the root element from the heap
     * 
     * @return int 
     */
    int pop() {
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }

    /**
     * @brief Get the top element from the heap
     * 
     * @return int 
     */
    int top() const {
        return heap[0];
    }

    /**
     * @brief Check if the heap is empty
     * 
     * @return true 
     * @return false 
     */
    bool empty() const {
        return heap.empty();
    }

    /**
     * @brief Merge two heaps
     * 
     * @param h 
     */
    void merge(BinomialHeap& h) {
        heap.insert(heap.end(), h.heap.begin(), h.heap.end());
        h.heap.clear();
        buildHeap();
    }

    /**
     * @brief Print the heap
     * 
     */
    void print() const {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

private:

    /**
     * @brief Build the heap
     * 
     */
    void buildHeap() {
        for (int i = 0; i < heap.size(); i++) {
            int parent = (i - 1) / 2;
            while (i > 0 && heap[parent] > heap[i]) {
                swap(heap[i], heap[parent]);
                i = parent;
                parent = (i - 1) / 2;
            }
        }
    }

    /**
     * @brief Heapify the heap
     * 
     * @param i 
     */
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

    vector<int> heap;
};

int main() {
    for (int i = 100000; i >= 1000; i -= 1000)
        {
            vector <int> arr (i);
            for (int j = 0; j < i; j++)
            {
                arr[j] = rand() % 100000;
            }
            BinomialHeap heap(arr);
            double time_spent = 0.0;
            clock_t begin = clock();
            heap.HeapSort();
            clock_t end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("%d %lf\n", i, time_spent);
            arr.clear();
        }
}
