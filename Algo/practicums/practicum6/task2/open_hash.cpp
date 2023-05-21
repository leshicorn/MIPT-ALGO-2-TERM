#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>

// Хэш-таблица с использованием открытого хэширования
class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> occupied;
    size_t tableSize;

    // Функция хэширования
    size_t hashFunction(int key, size_t probe) const {
        return (key + probe) % tableSize;
    }

public:
    HashTable(size_t size) : table(size, 0), occupied(size, false), tableSize(size) {}

    // Добавление элемента в хэш-таблицу
    void add(int key) {
        size_t probe = 0;
        size_t hash;
        do {
            hash = hashFunction(key, probe);
            if (!occupied[hash]) {
                table[hash] = key;
                occupied[hash] = true;
                break;
            }
            ++probe;
        } while (probe < tableSize);
    }

    // Удаление элемента из хэш-таблицы
    void remove(int key) {
        size_t probe = 0;
        size_t hash;
        do {
            hash = hashFunction(key, probe);
            if (occupied[hash] && table[hash] == key) {
                occupied[hash] = false;
                break;
            }
            ++probe;
        } while (probe < tableSize);
    }

    // Проверка наличия элемента в хэш-таблице
    bool contains(int key) const {
        size_t probe = 0;
        size_t hash;
        do {
            hash = hashFunction(key, probe);
            if (occupied[hash] && table[hash] == key) {
                return true;
            }
            ++probe;
        } while (probe < tableSize);
        return false;
    }
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Размеры тестов
    std::vector<size_t> testSizes;
    for (size_t size = 10000; size <= 1000000; size += 10000) {
        testSizes.push_back(size);
    }

    // Замер времени работы программы в целом
    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t size : testSizes) {
        HashTable hashTable(size);

        // Генерация случайной последовательности операций
        std::vector<std::string> operations;
        std::uniform_int_distribution<> opDistribution(0, 2);
        std::uniform_int_distribution<> numDistribution(1, size);

        for (size_t i = 0; i < size; ++i) {
            int num = numDistribution(gen);
            int opCode = opDistribution(gen);

            if (opCode == 0)
                operations.push_back("+ " + std::to_string(num));
            else if (opCode == 1)
                operations.push_back("- " + std::to_string(num));
            else
                operations.push_back("? " + std::to_string(num));
        }

        // Замер времени выполнения операций
        std::vector<double> executionTimes(size / 10000);

        for (size_t i = 0; i < operations.size(); ++i) {
            if (i % 10000 == 0) {
                auto start = std::chrono::high_resolution_clock::now();

                // Выполнение операции
                std::string operation = operations[i];
                char op = operation[0];
                int num = std::stoi(operation.substr(2));

                switch (op) {
                    case '+':
                        hashTable.add(num);
                        break;
                    case '-':
                        hashTable.remove(num);
                        break;
                    case '?':
                        hashTable.contains(num);
                        break;
                    default:
                        break;
                }

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff = end - start;
                executionTimes[i / 10000] = diff.count();
            }
        }

        // Вывод результатов
        std::cout << size << " ";
        // std::cout << "Execution Times: ";
        auto time_sum = 0.0;
        for (double time : executionTimes) {
            // std::cout << time << " ";
            time_sum += time;
        }
        std::cout << time_sum << std::endl;
    }

    // Замер времени работы программы в целом
    // auto endTime = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> totalTime = endTime - startTime;

    // std::cout << "Total Execution Time: " << totalTime.count() << " seconds" << std::endl;

    return 0;
}
