#include <iostream>
#include <chrono>
#include <random>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* createNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* merge(Node* left, Node* right);

Node* split(Node* root, int key) {
    if (root == nullptr)
        return nullptr;

    if (key < root->key) {
        root->left = split(root->left, key);
        return root;
    }

    if (key > root->key) {
        root->right = split(root->right, key);
        return root;
    }

    Node* leftSubtree = root->left;
    Node* rightSubtree = root->right;
    delete root;

    if (leftSubtree != nullptr)
        leftSubtree->right = nullptr;

    if (rightSubtree != nullptr)
        rightSubtree->left = nullptr;

    return merge(leftSubtree, rightSubtree);
}

Node* getMaxNode(Node* node);

Node* merge(Node* left, Node* right) {
    if (left == nullptr)
        return right;

    if (right == nullptr)
        return left;

    Node* maxLeft = getMaxNode(left);
    maxLeft->right = right;
    right->left = nullptr;

    return left;
}

Node* getMaxNode(Node* node) {
    if (node == nullptr)
        return nullptr;

    while (node->right != nullptr)
        node = node->right;

    return node;
}

void inorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

void testInsertionDeletion(int numInsertions, int numDeletions) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, numInsertions + numDeletions);

    auto start = chrono::high_resolution_clock::now();

    Node* root = nullptr;
    for (int i = 0; i < numInsertions; i++) {
        int key = distribution(generator);
        root = insert(root, key);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "insertions: " << numInsertions << " " << (double)duration.count() / 1000 << " s" << endl;

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numDeletions; i++) {
        int key = distribution(generator);
        root = deleteNode(root, key);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "deletions: " << numDeletions << " " << (double)duration.count() / 1000 << " s" << endl;
}

void testSortedSequence(int size) {
    auto start = chrono::high_resolution_clock::now();

    Node* root = nullptr;
    for (int i = 1; i <= size; i++) {
        root = insert(root, i);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Sorted sequence of size " << size << " " << (double)duration.count() / 1000 << "s" << endl;
}

int main() {
    // Testing random insertions and deletions
    for (int i = 1; i <= 10; i++) {
        int numInsertions = i * 100000;
        // int numInsertions = i * 1000;
        int numDeletions = numInsertions / 2;

        cout << "Test " << i << ":" << endl;
        testInsertionDeletion(numInsertions, numDeletions);
        cout << endl;
    }

    // Testing sorted sequence insertion
    testSortedSequence(1000000);
    // testSortedSequence(1000);

    return 0;
}