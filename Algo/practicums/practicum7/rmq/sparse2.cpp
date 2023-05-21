#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

// Функция для вычисления log2
int log2(int n) {
    int res = 0;
    while (n >>= 1) {
        res++;
    }
    return res;
}

// Класс SparseTable
class SparseTable {
private:
    vector<vector<int>> table;  // Sparse Table
    vector<int> log;            // Предвычисленные значения log2
public:
    // Конструктор
    SparseTable(const vector<int>& nums) {
        int n = nums.size();
        int logN = log2(n) + 1;

        table.resize(logN, vector<int>(n));

        // Заполняем первый ряд таблицы значениями из исходного массива
        for (int i = 0; i < n; i++) {
            table[0][i] = nums[i];
        }

        // Предвычисляем значения для каждого ряда таблицы
        for (int row = 1; row < logN; row++) {
            int power = 1 << (row - 1);  // 2^(row-1)
            for (int i = 0; i + power < n; i++) {
                table[row][i] = min(table[row - 1][i], table[row - 1][i + power]);
            }
        }

        // Предвычисляем значения log2
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }
    }

    // Функция для выполнения запроса
    int query(int left, int right) {
        int length = right - left + 1;
        int row = log[length];
        int power = 1 << row;
        return min(table[row][left], table[row][right - power + 1]);
    }
};

int main() {
    srand(time(0));

    int n = 1000000;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        nums[i] = rand() % 1000;  // Генерируем случайные числа от 0 до 999
    }

    SparseTable st(nums);

    int m = 1000000;
    clock_t start = clock();
    for (int i = 0; i < m; i++) {
        int left = rand() % n;
        int right = rand() % n;
        if (left > right) {
            swap(left, right);
        }
        st.query(left, right);
    }
    clock_t end = clock();

    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed_secs << " seconds" << endl;

    return 0;
}
