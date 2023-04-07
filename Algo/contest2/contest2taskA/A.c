#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Node {
    int height;
    int key;
    struct Node *left;
    struct Node *right;
} node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(node* tree) {
    return (tree != NULL) ? tree -> height : 0;
}

void update_height(node * n) {
    if (n) {
        n -> height = max(height(n -> left), height(n -> right)) + 1;
    }
}

int Balance(node* tree) {
    return (tree != NULL) ? height(tree -> left) - height(tree -> right) : 0;
}

node* create(int key) {
    node* tree = (node*)
            malloc(sizeof(node));
    tree->key = key;
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    return tree;
}

node * rotate_right(node * y) {
    node * x = y -> left;
    node * t2 = x -> right;

    x -> right = y;
    y -> left = t2;

    update_height(y);
    update_height(x);

    return x;
}

node* rotate_left(node * x) {
    node* y = x -> right;
    node* t2 = y -> left;

    y -> left = x;
    x -> right = t2;

    update_height(x);
    update_height(y);

    return y;
}

node * insert(node * root, int val) {
    if (!root) {
        return create(val);
    }

    if (val < root -> key) {
        root -> left = insert(root -> left, val);
    } else if (val > root -> key) {
        root -> right = insert(root -> right, val);
    } else {
        // key already exists in the tree
        return root;
    }

    update_height(root);

    int bf = Balance(root);

    if (bf > 1 && val < root -> left -> key) {
        return rotate_right(root);
    }

    if (bf > 1 && val > root -> left -> key) {
        root -> left = rotate_left(root -> left);
        return rotate_right(root);
    }

    if (bf < -1 && val > root -> right -> key) {
        return rotate_left(root);
    }

    if (bf < -1 && val < root -> right -> key) {
        root -> right = rotate_right(root -> right);
        return rotate_left(root);
    }
    return root;
}

int find(node * root, int key) {
    if (!root) {
        return -1;
    }
    if (key == root -> key) {
        return root -> key;
    }

    if (key < root -> key) {
        int res = find(root -> left, key);
        if (res == -1) {
            return root -> key;
        } else {
            return res;
        }
    } else {
        return find(root -> right, key);
    }
}


int main() {
        int n, x = 0, result = 0;
        char op, prev_op = '+';
        if (scanf("%d", &n) != 1) {
            printf("n is not a number\n");
            return -1;
        }
        if (scanf(" %c %d", &op, &x) != 2) {
            printf("x is not a number\n");
            return -1;
        }
        node* root = create(x);
        for (int i = 1; i < n; i++) {
            if (scanf(" %c %d", &op, &x) != 2) {
                return -1;
            };
            if (op == '?') {
                result = find(root, x);
                printf("%d\n", result);
            } else {
                if (prev_op != '+') {
                    root = insert(root, (x + result) % (int)1e9);
                } else {
                    root = insert(root, x);
                }
            }
            prev_op = op;
        }
        return 0;
}