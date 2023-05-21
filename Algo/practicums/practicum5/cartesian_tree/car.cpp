#include <iostream>
#include <ctime>

using namespace std;

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

// Split операция разделения декартова дерева на два поддерева.
// Результатом будут два декартовых дерева, первое содержит все элементы <= key,
// а второе содержит все элементы > key.
void Split(Node* root, int key, Node*& left, Node*& right) {
    if (!root) {
        left = nullptr;
        right = nullptr;
    } else if (root->key <= key) {
        Split(root->right, key, root->right, right);
        left = root;
    } else {
        Split(root->left, key, left, root->left);
        right = root;
    }
}

// Merge операция объединения двух декартовых деревьев.
// Предполагается, что все элементы в left дереве меньше чем все элементы в right дереве.
Node* Merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->right = Merge(left->right, right);
        return left;
    } else {
        right->left = Merge(left, right->left);
        return right;
    }
}

// Вставка нового элемента в декартово дерево.
Node* Insert(Node* root, Node* newNode) {
    if (!root) return newNode;
    if (newNode->priority > root->priority) {
        Split(root, newNode->key, newNode->left, newNode->right);
        return newNode;
    } else if (newNode->key <= root->key) {
        root->left = Insert(root->left, newNode);
    } else {
        root->right = Insert(root->right, newNode);
    }
    return root;
}

// Удаление элемента из декартова дерева.
Node* Remove(Node* root, int key) {
    if (!root) return nullptr;
    if (root->key == key) {
        Node* temp = root;
        root = Merge(root->left, root->right);
        delete temp;
    } else if (key < root->key) {
        root->left = Remove(root->left, key);
    } else {
        root->right = Remove(root->right, key);
    }
    return root;
}

// Тестирование
void runTest(int n) {
    Node* root = nullptr;

    // Засекаем время вставок
    clock_t startTime = clock();
    for (int i = 0; i < n; i++) {
        root = Insert(root, new Node(i));
    }
    clock_t endTime = clock();
    double insertTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    // Засекаем время удалений
    startTime = clock();
    for (int i = 0; i < n / 2; i++) {
        root = Remove(root, i);
    }
    endTime = clock();
    double removeTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    // cout << n << " " << insertTime << " " << removeTime << endl;
    cout << "i " << n << insertTime << endl;
    cout << "r " << n << removeTime << endl;

}

int main() {
    // Выполняем 10 тестов
    for (int i = 1; i <= 10; i++) {
        int n = i * 100000;
        runTest(n);
    }

    return 0;
}
