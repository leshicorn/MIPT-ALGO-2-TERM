#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/**
 * @brief AVL tree node
 * 
 */
typedef struct Node {
    size_t height;
    int key;
    struct Node *left;
    struct Node *right;
} node;

/**
 * @brief Returns the maximum of two integers
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(const int a, const int b) {
    return (a > b) ? a : b;
}


/**
 * @brief Returns the height of the tree
 * 
 * @param tree 
 * @return int 
 */
int height(node* tree) {
    return (tree != NULL) ? tree -> height : 0;
}


/**
 * @brief Updates the height of the node
 * 
 * @param n 
 */
void update_height(node * n) {
    if (n) {
        n -> height = max(height(n -> left), height(n -> right)) + 1;
    }
}


/**
 * @brief Returns the balance factor of the tree
 * 
 * @param tree 
 * @return int 
 */
int Balance(node* tree) {
    return (tree != NULL) ? height(tree -> left) - height(tree -> right) : 0;
}


/**
 * @brief Creates a new node
 * 
 * @param key 
 * @return node* 
 */
node* create(const int key) {
    node* tree = (node*)
            malloc(sizeof(node));
    tree->key = key;
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    return tree;
}


/**
 * @brief Rotates the tree to the right
 * 
 * @param y 
 * @return node* 
 */
node * rotate_right(node * y) {
    node * x = y -> left;
    node * t2 = x -> right;

    x -> right = y;
    y -> left = t2;

    update_height(y);
    update_height(x);

    return x;
}


/**
 * @brief Rotates the tree to the left
 * 
 * @param x 
 * @return node* 
 */
node* rotate_left(node * x) {
    node* y = x -> right;
    node* t2 = y -> left;

    y -> left = x;
    x -> right = t2;

    update_height(x);
    update_height(y);

    return y;
}

/**
 * @brief Rotates the tree to the side
 * 
 * @param tree 
 * @param side == 0 => right; side == 1 => left
 * @return node* 
 */
node* rotate_side(node* tree, int side) {
    if (side == 0) {
        return rotate_right(tree);
    } else {
        return rotate_left(tree);
    }
}

/**
 * @brief Returns the case of the balance factor
 * 
 * @param bf 
 * @param val 
 * @param root 
 * @return int 
 */
int BfCase(int bf, int val, node* root) {
    if (bf > 1 && val < root -> left -> key) {
        return 1;
    }

    if (bf > 1 && val > root -> left -> key) {
        return 2;
    }

    if (bf < -1 && val > root -> right -> key) {
        return 3;
    }

    if (bf < -1 && val < root -> right -> key) {
        return 4;
    }
    return 0;
}

/**
 * @brief Inserts a new node into the tree
 * 
 * @param root 
 * @param val 
 * @return node* 
 */
node * insert(node * root, const int val) {
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
    int bf_case = BfCase(bf, val, root);

    switch (bf_case)
    {
    case 1:
        return rotate_side(root, 0);
        break;
    case 2:
        root -> left = rotate_side(root -> left, 1);
        return rotate_side(root, 0);
        break;
    case 3:
        return rotate_side(root, 1);
        break;
    case 4:
        root -> right = rotate_side(root -> right, 0);
        return rotate_side(root, 1);
        break;
    default:
        break;
    }
    return root;
}

/**
 * @brief Finds the closest node to the key
 * 
 * @param root 
 * @param key 
 * @return int 
 */
int find(node * root, const int key) {
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

void Solution(int n) {
    int x = 0, result = 0;
    char op, prev_op;
    if (scanf(" %c %d", &op, &x) != 2) {
            printf("x is not a number\n");
            return -1;
        }
        prev_op = op;
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
}

int main() {
        int n;
        if (scanf("%d", &n) != 1) {
            printf("n is not a number\n");
            return -1;
        }
        
        Solution(n);

        return 0;
}