#include <iostream>
#include <vector>

using namespace std;

class FibonacciHeap {
public:
    /**
     * @brief Construct a new FibonacciHeap object
     * 
     * @param elements 
     */
    FibonacciHeap(vector<int> elements) : heap(elements) {
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



