#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int val;
    int degree;
    Node *parent;
    Node *child;
    Node *sibling;

    Node(int v) : val(v), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    Node *head;

public:
    BinomialHeap() : head(nullptr) {}

    void merge(BinomialHeap &other) {
        Node *h1 = head;
        Node *h2 = other.head;
        Node *h = nullptr;

        if (h1 == nullptr) {
            head = h2;
            return;
        } else if (h2 == nullptr) {
            return;
        }

        if (h1->degree <= h2->degree) {
            h = h1;
            h1 = h1->sibling;
        } else {
            h = h2;
            h2 = h2->sibling;
        }

        Node *tail = h;

        while (h1 != nullptr && h2 != nullptr) {
            if (h1->degree <= h2->degree) {
                tail->sibling = h1;
                h1 = h1->sibling;
            } else {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }

        if (h1 != nullptr) {
            tail->sibling = h1;
        } else {
            tail->sibling = h2;
        }

        head = h;
    }

    void insert(int val) {
        BinomialHeap temp;
        temp.head = new Node(val);
        merge(temp);
    }

    int findMin() {
        int minVal = head->val;
        Node *temp = head->sibling;
        while (temp != nullptr) {
            if (temp->val < minVal) {
                minVal = temp->val;
            }
            temp = temp->sibling;
        }
        return minVal;
    }

    Node *extractMin() {
        Node *minNode = head;
        Node *prev = nullptr;
        Node *temp = head->sibling;

        while (temp != nullptr) {
            if (temp->val < minNode->val) {
                minNode = temp;
                prev = head;
            } else {
                prev = temp;
            }
            temp = temp->sibling;
        }

        if (prev == nullptr) {
            head = minNode->sibling;
        } else {
            prev->sibling = minNode->sibling;
        }

        BinomialHeap tempHeap;
        Node *child = minNode->child;
        while (child != nullptr) {
            Node *next = child->sibling;
            child->parent = nullptr;
            child->sibling = tempHeap.head;
            tempHeap.head = child;
            child = next;
        }

        merge(tempHeap);

        return minNode;
    }

    bool empty() {
        return head == nullptr;
    }
};

vector<int> heapsort(vector<int> arr) {
    BinomialHeap heap;

    for (int i : arr) {
        heap.insert(i);
    }

    vector<int> sortedArr;

    while (!heap.empty()) {
        sortedArr.push_back(heap.extractMin()->val);
    }

    return sortedArr;
}

