#include <iostream>
#include <vector>

using namespace std;

// Реализация дерева отрезков
class SegmentTree {
private:
    vector<int> tree;
    int size;

    void build(const vector<int>& array, int node, int left, int right) {
        if (left == right) {
            tree[node] = array[left];
        } else {
            int mid = (left + right) / 2;
            build(array, 2 * node, left, mid);
            build(array, 2 * node + 1, mid + 1, right);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int left, int right, int queryLeft, int queryRight) {
        if (left > queryRight || right < queryLeft) {
            return 0;
        }
        if (left >= queryLeft && right <= queryRight) {
            return tree[node];
        }
        int mid = (left + right) / 2;
        int leftSum = query(2 * node, left, mid, queryLeft, queryRight);
        int rightSum = query(2 * node + 1, mid + 1, right, queryLeft, queryRight);
        return leftSum + rightSum;
    }

public:
    SegmentTree(const vector<int>& array) {
        size = array.size();
        tree.resize(4 * size);
        build(array, 1, 0, size - 1);
    }

    int queryRange(int left, int right) {
        return query(1, 0, size - 1, left, right);
    }
};

int main() {
    int n = 1000000; // Размер массива

    // Создание случайного массива из 10^6 элементов
    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 10000; // Заполняем случайными значениями от 0 до 99
    }

    // Построение дерева отрезков
    SegmentTree segmentTree(array);

    // Генерация 10^6 невырожденных отрезков с случайными запросами
    int numQueries = 1000000;
    clock_t startTime, endTime;

    startTime = clock();
    for (int i = 0; i < numQueries; i++) {
        int left = rand() % n;
        int right = rand() % n;

        if (left > right) {
            swap(left, right);
        }

        int sum = segmentTree.queryRange(left, right);
    }
    endTime = clock();

    double segmentTreeTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Time taken by Segment Tree: " << segmentTreeTime << " seconds" << endl;

    return 0;
}
