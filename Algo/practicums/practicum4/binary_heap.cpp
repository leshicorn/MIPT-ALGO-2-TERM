#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>

using namespace std;

class BinaryHeap {
public:
    BinaryHeap() {}

    BinaryHeap(vector<int> elements) {
        heap = elements;
        buildHeap();
    }

    /**
     * @brief Функция push добавляет новый элемент в кучу и регулирует кучу для поддержания свойства кучи.
     * @param x - новый элемент
     */
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

    /**
     * @brief Функция pop удаляет наименьший элемент из кучи и регулирует кучу для поддержания свойства кучи.
     * @return int - наименьший элемент кучи
     */
    int pop() {
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }

    /**
     * @brief Функция top возвращает наименьший элемент в куче.
     * @return int - наименьший элемент кучи 
     */
    int top() const {
        return heap[0];
    }

    /**
     * @brief Функция empty проверяет, пуста ли куча.
     * @return true 
     * @return false 
     */
    bool empty() const {
        return heap.empty();
    }

    /**
     * @brief Функция size возвращает количество элементов в куче.
     * 
     * @return size_t 
     */
    size_t size() const {
        return heap.size();
    }

private:
    vector<int> heap;

    /**
     * @brief Функция heapify регулирует кучу для поддержания свойства кучи.
     * @details Она берет индекс i и проверяет, является ли левый дочерний элемент (2*i+1) или правый дочерний элемент (2*i+2) меньше текущего элемента по индексу i. Если да, то она меняет наименьший дочерний элемент с текущим элементом и рекурсивно вызывает себя по новому индексу наименьшего дочернего элемента.
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

    /**
     * @brief Функция buildHeap используется для построения кучи из несортированного вектора элементов.
     * @details Она начинает с последнего элемента вектора и работает до корня кучи, вызывая heapify на каждом индексе для поддержания свойства кучи.
     * 
     */
    void buildHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }
};

void heapSort(vector<int>& arr) {
    BinaryHeap bh(arr);
    arr.clear();
    while (!bh.empty()) {
        arr.push_back(bh.pop());
    }
}

int main() {
    BinaryHeap bh;
    
    for (int i = 100000; i <= 10000000; i += 100000)
    {
        vector <int> arr (i);
        for (int j = 0; j < i; j++)
        {
            arr[j] = rand() % 100000;
        }
        double time_spent = 0.0;
        clock_t begin = clock();
        heapSort(arr);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        arr.clear();
    }

    return 0;
}

// set terminal png size 1024, 768 
// set output 'kheap.png' 
// plot "test1.txt" w line title "k = 5", "test2.txt" w line title "k = 10", "test3.txt" w line title "k = 25", "test4.txt" w line title "k = 50", "test5.txt" w line title "k = 100", "test6.txt" w line title "k = 200", "test7.txt" w line title "k = 300", "test8.txt" w line title "k = 400", "test9.txt" w line title "k = 500"
