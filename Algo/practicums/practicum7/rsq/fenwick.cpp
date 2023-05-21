#include <iostream>
#include <vector>

using namespace std;

// Реализация дерева Фенвика
class FenwickTree {
private:
    vector<int> tree;

public:
    FenwickTree(int size) {
        tree.resize(size + 1, 0);
    }

    void update(int index, int value) {
        while (index < tree.size()) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    int queryRange(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int main() {
    int n = 1000000; // Размер массива

    // Создание случайного массива из 10^6 элементов
    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100; // Заполняем случайными значениями от 0 до 99
    }

    // Построение дерева Фенвика
    FenwickTree fenwickTree(n);
    for (int i = 0; i < n; i++) {
        fenwickTree.update(i + 1, array[i]);
    }

    // Генерация 10^6 невырожденных отрезков с случайными запросами
    int numQueries = 1000000;
    clock_t startTime, endTime;

    startTime = clock();
    for (int i = 0; i < numQueries; i++) {
        int left = rand() % n + 1;
        int right = rand() % n + 1;

        if (left > right) {
            swap(left, right);
        }

        int sum = fenwickTree.queryRange(left, right);
    }
    endTime = clock();

    double fenwickTreeTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Time taken by Fenwick Tree: " << fenwickTreeTime << " seconds" << endl;

    return 0;
}
