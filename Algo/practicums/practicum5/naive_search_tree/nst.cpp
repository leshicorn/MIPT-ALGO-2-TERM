#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }

    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* remove(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }

    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        inorder(root->right);
    }
}

double runInsertionTest(int numElements) {
    Node* root = nullptr;
    clock_t startTime = clock();

    for (int i = 0; i < numElements; ++i) {
        int key = rand() % numElements;
        root = insert(root, key);
    }

    clock_t endTime = clock();
    double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    delete root;

    return elapsedTime;
}

double runDeletionTest(int numElements) {
    Node* root = nullptr;

    for (int i = 0; i < numElements; ++i) {
        int key = rand() % numElements;
        root = insert(root, key);
    }

    clock_t startTime = clock();

    for (int i = 0; i < numElements / 2; ++i) {
        int key = rand() % numElements;
        root = remove(root, key);
    }

    clock_t endTime = clock();
    double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    delete root;

    return elapsedTime;
}

double runSortedInsertionTest(int numElements) {
    Node* root = nullptr;
    clock_t startTime = clock();

    for (int i = 0; i < numElements; ++i) {
        root = insert(root, i);
    }

    clock_t endTime = clock();
    double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    delete root;

    return elapsedTime;
}

int main() {
    const int numTests = 5;
    const int numElements1 = 10000;
    const int numElements2 = 100000;

    // const int numElements1 = 1000;
    // const int numElements2 = 10000;

    double avgInsertionTime = 0.0;
    double avgDeletionTime = 0.0;
    double avgSortedInsertionTime = 0.0;

    for (int i = 0; i < numTests; ++i) {
        double insertionTime = runInsertionTest(numElements1);
        double deletionTime = runDeletionTest(numElements1);
        double sortedInsertionTime = runSortedInsertionTest(numElements2);

        avgInsertionTime += insertionTime;
        avgDeletionTime += deletionTime;
        avgSortedInsertionTime += sortedInsertionTime;

        cout << "Test " << i + 1 << " - Insertion Time: " << insertionTime << " seconds" << endl;
        cout << "Test " << i + 1 << " - Deletion Time: " << deletionTime << " seconds" << endl;
        cout << "Test " << i + 1 << " - Sorted Insertion Time: " << sortedInsertionTime << " seconds" << endl;
    }

    avgInsertionTime /= numTests;
    avgDeletionTime /= numTests;
    avgSortedInsertionTime /= numTests;

    cout << "Average Insertion Time: " << avgInsertionTime << " seconds" << endl;
    cout << "Average Deletion Time: " << avgDeletionTime << " seconds" << endl;
    cout << "Average Sorted Insertion Time: " << avgSortedInsertionTime << " seconds" << endl;

    return 0;
}
