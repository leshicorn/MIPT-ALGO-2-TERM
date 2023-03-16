#include <iostream>
#include <vector>


using namespace std;


class KHeap {
public:
    /**
     * @brief Construct a new KHeap object
     * 
     * @param k 
     * @param elements 
     */
    KHeap(int k, vector<int> elements) : k(k), heap(elements) {
        buildHeap();
    }

    /**
     * @brief Push an element into the heap
     * 
     * @param x 
     */
    void push(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;
        int parent = (i - 1) / k;
        while (i > 0 && heap[parent] > heap[i]) {
            swap(heap[i], heap[parent]);
            i = parent;
            parent = (i - 1) / k;
        }
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
     * @brief Get the size of the heap
     * 
     * @return size_t 
     */
    size_t size() const {
        return heap.size();
    }

    /**
     * @brief Get the Min Child object
     * 
     * @param i 
     * @return int 
     */
    int getMinChild(int i) const {
        int smallest = -1;
        for (int j = 1; j <= k; ++j) {
            int child = k * i + j;
            if (child < heap.size() && (smallest == -1 || compare(heap[child], heap[smallest]))) {
                smallest = child;
            }
        }
        return smallest;
    }

    /**
     * @brief Get the Max Child object
     * 
     * @param i 
     * @return int 
     */
    int getMaxChild(int i) const {
        int largest = -1;
        for (int j = 1; j <= k; ++j) {
            int child = k * i + j;
            if (child < heap.size() && (largest == -1 || compare(heap[largest], heap[child]))) {
                largest = child;
            }
        }
        return largest;
    }

private:
    int k;
    vector<int> heap;
    bool isMaxHeap;

    /**
     * @brief Compare two elements and checks if heap is min or max
     * 
     * @param a 
     * @param b 
     * @return true 
     * @return false 
     */
    bool compare(int a, int b) const {
        return isMaxHeap ? a > b : a < b;
    }

    /**
     * @brief Восстанавливает свойства кучи, начиная с узла i
     * 
     * @param i 
     */
    void heapify(int i) {
        int extreme = i;
        int child;
        do {
            i = extreme;
            extreme = getExtremeChild(i);
            if (extreme != -1 && compare(heap[extreme], heap[i])) {
                swap(heap[i], heap[extreme]);
            }
        } while (extreme != -1 && extreme != i);
    }

    /**
     * @brief находит дочерний узел с наименьшим или наибольшим значением в зависимости от того, является ли куча min-кучей или max-кучей, соответственно.
     * 
     * @param i 
     * @return int 
     */
    int getExtremeChild(int i) const {
        int extreme = -1;
        int child;
        for (int j = 1; j <= k; ++j) {
            child = k * i + j;
            if (child < heap.size()) {
                if (extreme == -1 || compare(heap[child], heap[extreme])) {
                    extreme = child;
                }
            }
        }
        return extreme;
    }

    /**
     * @brief Build a heap
     * 
     */
    void buildHeap() {
        for (int i = heap.size() / k; i >= 0; --i) {
            heapify(i);
        }
    }
};

/**
 * @brief Sort an array using k-heap
 * 
 * @param arr 
 * @param k 
 */
void heapSort(vector<int>& arr, int k) {
    KHeap kh(k, arr);
    arr.clear();
    while (!kh.empty()) {
        arr.push_back(kh.pop());
    }
}

int main() {
    int k = 1000;    
    for (int i = 100000; i <= 10000000; i += 100000)
    {
        vector <int> arr (i);
        for (int j = 0; j < i; j++)
        {
            arr[j] = rand() % 100000;
        }
        double time_spent = 0.0;
        clock_t begin = clock();
        heapSort(arr, k);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        arr.clear();
    }

    return 0;
}