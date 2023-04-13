#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int number;
    int priority;
    int size_of_tree;
    struct Node* left;
    struct Node* right;
    struct Node* parent;

} Node;

Node* nodes [51000] = {NULL};

Node* create_node(int key, int priority, Node* parent, int number)
{
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->size_of_tree = 1;
    node->number = number;

    return node;
}

Node* insert(int key, int priority, Node* cur, Node** tree, int number)
{
    if (cur == NULL) {
        Node* new_tree = create_node(key, priority, NULL, number);
        new_tree->left = *tree;
        (*tree)->parent = new_tree;
        (*tree) = new_tree;

        return new_tree;
    }

    if (cur->priority > priority) {
        Node* new_node = create_node(key, priority, cur, number);
        new_node->left = cur->right;
        if (new_node->left != NULL) {
            new_node->left->parent = new_node;
        }
        cur->right = new_node;

        return new_node;
    }
    else {
        return insert(key, priority, cur->parent, tree, number);
    }
}

Node * build(int n) {
    Node * tree = NULL;
    Node * cur = NULL;
    int key = 0;
    int priority = 0;

    scanf("%d %d", & key, & priority);
    tree = create_node(key, -priority, NULL, 1);
    nodes[1] = tree;
    cur = tree;

    for (int i = 2; i <= n; ++i) {
        scanf("%d %d", & key, & priority);

        cur = insert(key, -priority, cur, &tree, i);
        nodes[i] = cur;
    }

    return tree;
}

Node* merge(Node* left, Node* right)
{
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->right->parent = left;
        return left;
    }
    else {
        right->left = merge(left, right->left);
        right->left->parent = right;
        return right;
    }
}

void split(Node* tree, int key, Node** left, Node** right)
{
    if (tree == NULL) {
        *left = NULL;
        *right = NULL;
        return;
    }

    if (tree->key <= key) {
        split(tree->right, key, &tree->right, right);
        *left = tree;
    }
    else {
        split(tree->left, key, left, &tree->left);
        *right = tree;
    }
}

void print_key(Node* node)
{
    if (node == NULL) {
        printf("0");
    } else {
        printf("%d", node->number);
    }
}

void print_tree(Node* tree) {
    if (tree == NULL) {
        return;
    }

    print_key(tree->parent); printf(" ");
    print_key(tree->left); printf(" ");
    print_key(tree->right); printf("\n");
}

int main() {
    int n = 0;
    scanf("%d", & n);
    Node* tree = build(n);
    printf("YES\n");

    for (int i = 1; i <= n; i++) {
        print_tree(nodes[i]);
    }

    return 0;
}