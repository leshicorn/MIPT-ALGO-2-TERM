#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    long long priority;
    long long key;
    long long cached_sum;
    struct Node* left;
    struct Node* right;
};

static inline struct Node* new_node(long long key) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Failed to allocate memory for node");
        return NULL;
    }
    memset(node, 0, sizeof(struct Node));
    node->key = key;
    node->priority = (rand() << 15) | rand();
    node->cached_sum = key;
    return node;
}

void update(struct Node** node_ptr) {
    struct Node* node = *node_ptr;
    if (node == NULL) {
        return;
    }
    node->cached_sum = node->key;
    if (node->left) {
        long long left_cached_sum = node->left->cached_sum;
        node->cached_sum += left_cached_sum;
    }
    if (node->right) {
        long long right_cached_sum = node->right->cached_sum;
        node->cached_sum += right_cached_sum;
    }
}

void split(struct Node* root, long long key, struct Node** left, struct Node** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
        return;
    }
    if (root->key <= key) {
        split(root->right, key, &root->right, right);
        *left = root;
        update(&root);
    } else {
        split(root->left, key, left, &root->left);
        *right = root;
        update(&root);
    }
}

struct Node* merge(struct Node* left, struct Node* right) {
    if (!left || !right) {
        return left ? left : right;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(&left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(&right);
        return right;
    }
}

struct Node* find(struct Node* root, long long key) {
    while (root) {
        if (root->key == key) {
            return root;
        } else if (root->key < key) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}

struct Node* insert(struct Node* root, long long key) {
    if(find(root, key) != NULL){
        return root;
    }
    struct Node* node = new_node(key);
    struct Node *left, *right;
    split(root, key, &left, &right);
    return merge(merge(left, node), right);
}

long long sum(struct Node* root, long long start, long long end) {
    struct Node *left = NULL, *middle = NULL, *right = NULL;
    split(root, end, &root, &right);
    split(root, start - 1, &left, &middle);
    long long result = middle ? middle->cached_sum : 0;
    root = merge(merge(left, middle), right);
    return result;
}

int main() {
    struct Node* root = NULL;
    long long n;
    long long result = 0;
    if(scanf("%lld ", &n) != 1) {
        printf("Error while reading \"n\"");
        return 1;
    }
    char str, prev_str;
    for (long long i = 0; i < n; ++i) {
        if (scanf("%c ", &str) != 1) {
            printf("Error while reading \"str\"");
            return 1;
        }
        if (str == '?') {
            long long l, r;
            if (scanf("%lld %lld ", &l, &r) != 2) {
                printf("Error while reading \"l\" or \"r\"");
                return 1;
            }
            result = sum(root, l, r);
            printf("%lld\n", result);
        } else {
            long long x;
            if (scanf("%lld ", &x) != 1) {
                printf("Error while reading \"x\"");
                return 1;
            }
            if (prev_str != '+') {
                root = insert(root, (x + result) % 1000000000);
            } else {
                root = insert(root, x);
            }
        }
        prev_str = str;
    }
    return 0;
}