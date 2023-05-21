#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

const int MAX_LEVEL = 6;  // Максимальный уровень в skip list

// Узел skip list
struct SkipNode {
    int value;
    SkipNode** forward;

    SkipNode(int level, int value) {
        this->value = value;
        forward = new SkipNode*[level + 1];
        memset(forward, 0, sizeof(SkipNode*) * (level + 1));
    }

    ~SkipNode() {
        delete[] forward;
    }
};

// Дерево skip list
class SkipList {
public:
    SkipList() {
        level = 0;
        header = new SkipNode(MAX_LEVEL, 0);
    }

    ~SkipList() {
        delete header;
    }

    // Вставка нового элемента в skip list
    void insertElement(int value) {
        SkipNode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(SkipNode*) * (MAX_LEVEL + 1));
        SkipNode* current = header;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                level = newLevel;
            }

            SkipNode* newNode = new SkipNode(newLevel, value);

            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    // Удаление элемента из skip list
    void removeElement(int value) {
        SkipNode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(SkipNode*) * (MAX_LEVEL + 1));
        SkipNode* current = header;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }
        }
    }

    // Вспомогательная функция для генерации случайного уровня
    int randomLevel() {
        int level = 0;
        while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
            level++;
        return level;
    }

    // Функция для печати элементов skip list
    void printList() {
        std::cout << "Skip List: " << std::endl;
        for (int i = level; i >= 0; i--) {
            SkipNode* node = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (node != nullptr) {
                std::cout << node->value << " ";
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }

private:
    int level;
    SkipNode* header;
};

int main() {
    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    int n = 100000;  // Начальное количество вставок
    int step = 100000;  // Шаг для увеличения количества вставок
    int maxInsertions = 1000000;  // Максимальное количество вставок

    while (n <= maxInsertions) {
        SkipList skipList;
        clock_t startTime, endTime;
        
        // Вставка элементов
        startTime = clock();
        for (int i = 0; i < n; i++) {
            skipList.insertElement(i);
        }
        endTime = clock();

        double insertTime = double(endTime - startTime) / CLOCKS_PER_SEC;

        // Удаление половины элементов
        startTime = clock();
        for (int i = 0; i < n / 2; i++) {
            skipList.removeElement(i);
        }
        endTime = clock();

        double deleteTime = double(endTime - startTime) / CLOCKS_PER_SEC;

        // std::cout << n << " " << insertTime << " " << deleteTime << std::endl;
        std::cout << "i " << n << " " << insertTime << std::endl;
        std::cout << "d " << n << " " << deleteTime << std::endl; 

        n += step;
    }

    return 0;
}
