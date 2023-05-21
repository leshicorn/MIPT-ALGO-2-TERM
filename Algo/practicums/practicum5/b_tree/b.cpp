#include <iostream>
#include <vector>
#include <chrono>

const int MIN_DEGREE = 2;

struct BTreeNode {
    bool leaf;
    std::vector<int> keys;
    std::vector<BTreeNode*> child_ptrs;

    BTreeNode(bool leaf_node) : leaf(leaf_node) {}
};

class BTree {
private:
    BTreeNode* root;

    void splitChild(BTreeNode* parent, int child_index) {
        BTreeNode* new_node = new BTreeNode(parent->child_ptrs[child_index]->leaf);
        BTreeNode* child_node = parent->child_ptrs[child_index];

        parent->keys.insert(parent->keys.begin() + child_index, child_node->keys[MIN_DEGREE]);
        parent->child_ptrs.insert(parent->child_ptrs.begin() + child_index + 1, new_node);

        new_node->keys.assign(child_node->keys.begin() + MIN_DEGREE + 1, child_node->keys.end());
        child_node->keys.resize(MIN_DEGREE);

        if (!child_node->leaf) {
            new_node->child_ptrs.assign(child_node->child_ptrs.begin() + MIN_DEGREE + 1,
                                        child_node->child_ptrs.end());
            child_node->child_ptrs.resize(MIN_DEGREE + 1);
        }
    }

    void mergeChild(BTreeNode* parent, int child_index) {
        BTreeNode* child_node = parent->child_ptrs[child_index];
        BTreeNode* sibling_node = parent->child_ptrs[child_index + 1];

        child_node->keys.push_back(parent->keys[child_index]);
        child_node->keys.insert(child_node->keys.end(), sibling_node->keys.begin(), sibling_node->keys.end());

        if (!child_node->leaf) {
            child_node->child_ptrs.insert(child_node->child_ptrs.end(),
                                          sibling_node->child_ptrs.begin(),
                                          sibling_node->child_ptrs.end());
        }

        parent->keys.erase(parent->keys.begin() + child_index);
        parent->child_ptrs.erase(parent->child_ptrs.begin() + child_index + 1);

        delete sibling_node;
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);

            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }

            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }

            i++;
            if (node->child_ptrs[i]->keys.size() == (2 * MIN_DEGREE) - 1) {
                splitChild(node, i);

                if (key > node->keys[i]) {
                    i++;
                }
            }

            insertNonFull(node->child_ptrs[i], key);
        }
    }

    void remove(BTreeNode* node, int key) {
        int key_index = findKeyIndex(node, key);

        if (key_index < node->keys.size() && node->keys[key_index] == key) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + key_index);
            } else {
                BTreeNode* predecessor = node->child_ptrs[key_index];
                BTreeNode* successor = node->child_ptrs[key_index + 1];

                if (predecessor->keys.size() >= MIN_DEGREE) {
                    int predecessor_key = getPredecessor(predecessor);
                    node->keys[key_index] = predecessor_key;
                    remove(predecessor, predecessor_key);
                } else if (successor->keys.size() >= MIN_DEGREE) {
                    int successor_key = getSuccessor(successor);
                    node->keys[key_index] = successor_key;
                    remove(successor, successor_key);
                } else {
                    mergeChild(node, key_index);
                    remove(predecessor, key);
                }
            }
        } else {
            if (node->leaf) {
                std::cout << "Key " << key << " not found in the B-tree." << std::endl;
                return;
            }

            bool is_last_child = (key_index == node->keys.size());
            BTreeNode* child_node = node->child_ptrs[key_index];

            if (child_node->keys.size() < MIN_DEGREE) {
                fillChild(node, key_index);
            }

            if (is_last_child && key_index > node->keys.size()) {
                remove(node->child_ptrs[key_index - 1], key);
            } else {
                remove(node->child_ptrs[key_index], key);
            }
        }
    }

    int findKeyIndex(const BTreeNode* node, int key) {
        int index = 0;
        while (index < node->keys.size() && key > node->keys[index]) {
            index++;
        }
        return index;
    }

    int getPredecessor(const BTreeNode* node) {
        if (node->leaf) {
            return node->keys[node->keys.size() - 1];
        }
        return getPredecessor(node->child_ptrs[node->child_ptrs.size() - 1]);
    }

    int getSuccessor(const BTreeNode* node) {
        if (node->leaf) {
            return node->keys[0];
        }
        return getSuccessor(node->child_ptrs[0]);
    }

    void fillChild(BTreeNode* node, int child_index) {
        if (child_index != 0 && node->child_ptrs[child_index - 1]->keys.size() >= MIN_DEGREE) {
            borrowFromPrev(node, child_index);
        } else if (child_index != node->keys.size() && node->child_ptrs[child_index + 1]->keys.size() >= MIN_DEGREE) {
            borrowFromNext(node, child_index);
        } else {
            if (child_index != node->keys.size()) {
                mergeChild(node, child_index);
            } else {
                mergeChild(node, child_index - 1);
            }
        }
    }

    void borrowFromPrev(BTreeNode* node, int child_index) {
        BTreeNode* child_node = node->child_ptrs[child_index];
        BTreeNode* sibling_node = node->child_ptrs[child_index - 1];

        child_node->keys.insert(child_node->keys.begin(), node->keys[child_index - 1]);
        node->keys[child_index - 1] = sibling_node->keys.back();
        sibling_node->keys.pop_back();

        if (!child_node->leaf) {
            child_node->child_ptrs.insert(child_node->child_ptrs.begin(),
                                          sibling_node->child_ptrs.back());
            sibling_node->child_ptrs.pop_back();
        }
    }

    void borrowFromNext(BTreeNode* node, int child_index) {
        BTreeNode* child_node = node->child_ptrs[child_index];
        BTreeNode* sibling_node = node->child_ptrs[child_index + 1];

        child_node->keys.push_back(node->keys[child_index]);
        node->keys[child_index] = sibling_node->keys[0];
        sibling_node->keys.erase(sibling_node->keys.begin());

        if (!child_node->leaf) {
            child_node->child_ptrs.push_back(sibling_node->child_ptrs[0]);
            sibling_node->child_ptrs.erase(sibling_node->child_ptrs.begin());
        }
    }

public:
    BTree() : root(nullptr) {}

    void clear() {
        clear(root);
        root = nullptr;
    }

    void clear(BTreeNode* node) {
        if (node == nullptr) {
            return;
        }

        if (!node->leaf) {
            for (int i = 0; i < node->child_ptrs.size(); ++i) {
                clear(node->child_ptrs[i]);
            }
        }

        delete node;
    }


    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == (2 * MIN_DEGREE) - 1) {
                BTreeNode* new_node = new BTreeNode(false);
                new_node->child_ptrs.push_back(root);
                root = new_node;
                splitChild(new_node, 0);
            }
            insertNonFull(root, key);
        }
    }

    void remove(int key) {
        if (root == nullptr) {
            std::cout << "The B-tree is empty." << std::endl;
            return;
        }

        remove(root, key);

        if (root->keys.empty()) {
            BTreeNode* old_root = root;
            if (root->leaf) {
                root = nullptr;
            } else {
                root = root->child_ptrs[0];
            }
            delete old_root;
        }
    }

    void printBTree() const {
        printBTree(root, "");
    }

    void printBTree(const BTreeNode* node, const std::string& prefix) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < node->keys.size(); ++i) {
            std::cout << prefix << node->keys[i] << std::endl;
        }

        if (!node->leaf) {
            for (int i = 0; i < node->child_ptrs.size(); ++i) {
                printBTree(node->child_ptrs[i], prefix + "\t");
            }
        }
    }
};

int main() {
    BTree btree;
    std::vector<int> test_sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};

    for (int i = 0; i < test_sizes.size(); ++i) {
        int n = test_sizes[i];
        int delete_count = n / 2;

        auto start_insert = std::chrono::high_resolution_clock::now();
        for (int j = 1; j <= n; ++j) {
            btree.insert(j);
        }
        auto end_insert = std::chrono::high_resolution_clock::now();
        auto duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

        auto start_delete = std::chrono::high_resolution_clock::now();
        for (int j = 1; j <= delete_count; ++j) {
            btree.remove(j);
        }
        auto end_delete = std::chrono::high_resolution_clock::now();
        auto duration_delete = std::chrono::duration_cast<std::chrono::milliseconds>(end_delete - start_delete);

        // std::cout << "n = " << n << ", Insert Time: " << duration_insert.count() << " ms, Delete Time: "
                //   << duration_delete.count() << " ms" << std::endl;
        std::cout << "i " << n << " "  << (double)duration_insert.count() / 1000 << std::endl;
        std::cout << "d " << n << " "  << (double)duration_delete.count() / 1000 << std::endl;

        // Очистка дерева перед следующим тестом
        btree.clear();
    }

    return 0;
}
