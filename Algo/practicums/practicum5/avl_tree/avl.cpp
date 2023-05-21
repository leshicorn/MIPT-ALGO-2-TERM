#include <iostream>
#include <cstdlib>
#include <ctime>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};


Node* removeMin(Node* node);

// Получение высоты узла
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Получение разницы высот между левым и правым поддеревьями
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Обновление высоты узла
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Вращение влево
Node* rotateLeft(Node* node) {
    Node* pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

// Вращение вправо
Node* rotateRight(Node* node) {
    Node* pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

// Балансировка дерева
Node* balance(Node* node) {
    updateHeight(node);
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// Вставка ключа в AVL-дерево
Node* insert(Node* node, int key) {
    if (node == nullptr) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->height = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return balance(node);
}

// Поиск минимального узла в дереве
Node* findMin(Node* node) {
    if (node == nullptr)
        return nullptr;
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// Удаление ключа из AVL-дерева
Node* remove(Node* node, int key) {
    if (node == nullptr)
        return nullptr;
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        Node* leftChild = node->left;
        Node* rightChild = node->right;
        delete node;
        if (rightChild == nullptr)
            return leftChild;
        Node* minNode = findMin(rightChild);
        minNode->right = removeMin(rightChild);
        minNode->left = leftChild;
        return balance(minNode);
    }
    return balance(node);
}

// Удаление минимального узла из дерева
Node* removeMin(Node* node) {
    if (node->left == nullptr)
        return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

// Печать дерева в виде отсортированной последовательности
void printTree(Node* node) {
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << node->key << " ";
    printTree(node->right);
}

// Очистка памяти, выделенной под дерево
void clearTree(Node* node) {
    if (node == nullptr)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

int main() {
    std::srand(std::time(nullptr));

    // Тестирование для случайных элементов
    std::cout << "Testing with random elements:" << std::endl;
    for (int n = 100000; n <= 1000000; n += 100000) {
        Node* root = nullptr;

        // Вставка n случайных элементов
        clock_t startTime = clock();
        for (int i = 0; i < n; ++i) {
            int key = std::rand();
            root = insert(root, key);
        }
        clock_t endTime = clock();
        double insertionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        // Удаление n/2 элементов
        int removalCount = n / 2;
        startTime = clock();
        for (int i = 0; i < removalCount; ++i) {
            int key = std::rand();
            root = remove(root, key);
        }
        endTime = clock();
        double removalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        std::cout << n << " " << insertionTime << ", " << removalTime << std::endl;

        clearTree(root);
    }

    // Тестирование для отсортированной последовательности
    std::cout << "\nTesting with sorted elements:" << std::endl;
    for (int n = 100000; n <= 1000000; n += 100000) {
        Node* root = nullptr;

        // Вставка отсортированной последовательности
        clock_t startTime = clock();
        for (int i = 0; i < n; ++i) {
            root = insert(root, i);
        }
        clock_t endTime = clock();
        double insertionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        // Удаление n/2 элементов
        int removalCount = n / 2;
        startTime = clock();
        for (int i = 0; i < removalCount; ++i) {
            root = remove(root, i);
        }
        endTime = clock();
        double removalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        std::cout << n << " " << insertionTime << ", " << removalTime << std::endl;

        clearTree(root);
    }

    return 0;
}
