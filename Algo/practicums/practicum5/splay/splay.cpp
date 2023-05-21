#include <iostream>
#include <ctime>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        if (root->left == nullptr) {
            return root;
        }
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        }
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = rotateLeft(root->left);
        }
        if (root->left == nullptr)
            return root;
        else
            return rotateRight(root);
    }
    else {
        if (root->right == nullptr) {
            return root;
        }
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rotateRight(root->right);
        }
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }
        if (root->right == nullptr)
            return root;
        else
            return rotateLeft(root);
    }
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    root = splay(root, key);
    if (key < root->key) {
        Node* newNode = new Node(key);
        newNode->left = root->left;
        newNode->right = root;
        root->left = nullptr;
        return newNode;
    }
    else if (key > root->key) {
        Node* newNode = new Node(key);
        newNode->right = root->right;
        newNode->left = root;
        root->right = nullptr;
        return newNode;
    }
    else {
        return root;
    }
}

Node* merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    right = splay(right, left->key);
    right->left = left;
    return right;
}

pair<Node*, Node*> split(Node* root, int key) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    root = splay(root, key);
    if (root->key == key) {
        Node* left = root->left;
        Node* right = root->right;
        root->left = nullptr;
        root->right = nullptr;
        return {left, right};
    }
    else if (key < root->key) {
        Node* left = root->left;
        root->left = nullptr;
        return {left, root};
    }
    else {
        Node* right = root->right;
        root->right = nullptr;
        return {root, right};
    }
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    srand(time(nullptr));

    int n = 1000000; // Количество вставок
    int m = n / 2;   // Количество удалений

    Node* root = nullptr;

    clock_t startInsert = clock();
    for (int i = 0; i < n; i++) {
        root = insert(root, i + 1);
    }
    clock_t endInsert = clock();

    clock_t startDelete = clock();
    for (int i = 0; i < m; i++) {
        pair<Node*, Node*> splitResult = split(root, i + 1);
        Node* left = splitResult.first;
        Node* right = splitResult.second;
        if (left != nullptr) {
            deleteTree(left);
        }
        root = right;
    }
    clock_t endDelete = clock();

    double timeInsert = static_cast<double>(endInsert - startInsert) / CLOCKS_PER_SEC;
    double timeDelete = static_cast<double>(endDelete - startDelete) / CLOCKS_PER_SEC;

    cout << "Insertions: " << n << ", Time: " << timeInsert << " seconds" << endl;
    cout << "Deletions: " << m << ", Time: " << timeDelete << " seconds" << endl;

    deleteTree(root);

    return 0;
}
