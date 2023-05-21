#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

// Класс SparseTable
class SparseTable {
private:
    vector<vector<int>> st;  // sparse table
    vector<int> log2;  // предварительно вычисленные значения log2

public:
    // Конструктор
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        int logN = std::log2(n) + 1;

        st.assign(logN, vector<int>(n));

        // Заполняем первый уровень Sparse Table
        for (int i = 0; i < n; i++) {
            st[0][i] = arr[i];
        }

        // Заполняем остальные уровни Sparse Table
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }

        // Вычисляем значения log2
        log2.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            log2[i] = log2[i / 2] + 1;
        }
    }

    // Ответ на запрос минимума на отрезке [l, r]
    int query(int l, int r) {
        int j = log2[r - l + 1];
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

// Функция для генерации случайного массива
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;  // генерируем случайное число от 0 до 999999
    }
    return arr;
}

int main() {
    srand(time(0));

    int n = 1000000;
    vector<int> arr = generateRandomArray(n);

    // Создаем Sparse Table
    SparseTable st(arr);

    // Генерируем и выполняем запросы
    clock_t start = clock();

    // Генерируем 10^6 невырожденных отрезков и выполняем запросы
    for (int i = 0; i < n; i++) {
        int l = rand() % n;  // генерируем случайный левый индекс
        int r = rand() % n;  // генерируем случайный правый индекс
        if (l > r) {
            swap(l, r);  // если левый индекс больше правого, меняем их местами
        }
        st.query(l, r);  // выполняем запрос
    }

    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

    cout << "Elapsed time: " << elapsed_time << " seconds" << endl;

    return 0;
}
