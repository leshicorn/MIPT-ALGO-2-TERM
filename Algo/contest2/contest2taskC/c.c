#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/**
 * @brief Node of the tree
 *
 */
typedef struct Node
{
    int key;
    int priority;
    int size;
    struct Node *left;
    struct Node *right;
} Node;

/**
 * @brief Get the size of the tree
 *
 * @param root
 * @return int
 */
static inline int size(Node *root)
{
    return root ? root->size : 0;
}

/**
 * @brief Update the size of the tree
 *
 * @param root
 */
static inline void update_size(Node *root)
{
    if (root)
    {
        root->size = size(root->left) + size(root->right) + 1;
    }
}

/**
 * @brief Create a Node object
 *
 * @param key
 * @return Node*
 */
Node *createNode(const int key)
{
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->priority = rand();
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief Merge two trees
 *
 * @param left
 * @param right
 * @return Node*
 */
Node *merge(Node *left, Node *right)
{
    if (!left || !right)
        return left ? left : right;

    if (left->priority > right->priority)
    {
        left->right = merge(left->right, right);
        return left;
    }
    else
    {
        right->left = merge(left, right->left);
        return right;
    }
}

/**
 * @brief Split the tree into two trees
 *
 * @param node
 * @param key
 * @param left
 * @param right
 */
void split(Node *node, const int key, Node **left, Node **right)
{
    if (!node)
    {
        *left = NULL;
        *right = NULL;
        return;
    }
    if (node->key < key)
    {
        *left = node;
        split(node->right, key, &((*left)->right), right);
    }
    else
    {
        *right = node;
        split(node->left, key, left, &((*right)->left));
    }
}

/**
 * @brief Rotates tree right side by given
 *
 * @param node
 * @return Node*
 */
Node *rotate_right(Node *node)
{
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

/**
 * @brief Rotates tree left side by given
 *
 * @param node
 * @return Node*
 */
Node *rotate_left(Node *node)
{
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

/**
 * @brief Insert a new node into the tree
 *
 * @param root
 * @param key
 * @param priority
 * @return Node*
 */
Node *insert(Node *root, const int key, const int priority)
{
    if (root == NULL)
    {
        Node *new_root = (Node *)malloc(sizeof(Node));
        new_root->key = key;
        new_root->priority = priority;
        new_root->size = 1;
        new_root->left = new_root->right = NULL;
        return new_root;
    }

    if (key < root->key)
    {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority)
        {
            root = rotate_right(root);
        }
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority)
        {
            root = rotate_left(root);
        }
    }

    update_size(root);
    return root;
}

/**
 * @brief Delete a node from the tree
 *
 * @param root
 * @param key
 * @return Node*
 */
Node *delete(Node *root, const int key)
{
    if (!root)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = delete (root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete (root->right, key);
    }
    else
    {
        if (!root->left || !root->right)
        {
            Node *new_root = root->left ? root->left : root->right;
            free(root);
            root = new_root;
        }
        else
        {
            Node *node = root->left;
            while (node->right)
            {
                node = node->right;
            }
            root->key = node->key;
            root->left = delete (root->left, node->key);
        }
    }
    if (root)
    {
        if (root->left)
        {
            if (root->left->priority > root->priority)
            {
                Node *new_root = root->left;
                root->left = new_root->right;
                new_root->right = root;
                root = new_root;
            }
        }
        else if (root->right)
        {
            if (root->right->priority > root->priority)
            {
                Node *new_root = root->right;
                root->right = new_root->left;
                new_root->left = root;
                root = new_root;
            }
        }
        update_size(root);
    }
    return root;
}

/**
 * @brief Search for a node in the tree
 *
 * @param root
 * @param key
 * @return Node*
 */
Node *search(Node *root, const int key)
{
    while (root)
    {
        if (key == root->key)
        {
            return root;
        }
        else if (key < root->key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return NULL;
}

/**
 * @brief Check if a node exists in the tree
 *
 * @param root
 * @param key
 * @return true
 * @return false
 */
bool exists(Node *root, const int key)
{
    while (root)
    {
        if (key == root->key)
        {
            return true;
        }
        else if (key < root->key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return false;
}

/**
 * @brief Get the next node in the tree
 *
 * @param root
 * @param key
 * @return Node*
 */
Node *next(Node *root, const int key)
{
    Node *node = NULL;
    while (root)
    {
        if (key < root->key)
        {
            node = root;
            root = root->left;
        }
        else if (key > root->key)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return node;
}

/**
 * @brief Get the previous node in the tree
 * 
 * @param root 
 * @param key 
 * @return Node* 
 */
Node *prev(Node *root, const int key)
{
    Node *node = NULL;
    while (root)
    {
        if (key < root->key)
        {
            root = root->left;
        }
        else if (key > root->key)
        {
            node = root;
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return node;
}

/**
 * @brief Get the kth node in the tree
 * 
 * @param root 
 * @param k 
 * @return int 
 */
int kth(Node *root, const int k)
{
    if (k < 0 || k >= size(root) || !root)
    {
        return -1;
    }
    int s = size(root->left);
    if (k == s)
    {
        return root->key;
    }
    if (k < s)
    {
        return kth(root->left, k);
    }
    return kth(root->right, k - s - 1);
}

/**
 * @brief Find the case of the operation
 * 
 * @param op 
 * @return int 
 */
int FindCase(char *op)
{
    if (strcmp(op, "insert") == 0)
    {
        return 1;
    }
    else if (strcmp(op, "delete") == 0)
    {
        return 2;
    }
    else if (strcmp(op, "exists") == 0)
    {
        return 3;
    }
    else if (strcmp(op, "next") == 0)
    {
        return 4;
    }
    else if (strcmp(op, "prev") == 0)
    {
        return 5;
    }
    else if (strcmp(op, "kth") == 0)
    {
        return 6;
    }
    return 0;
}

/**
 * @brief Main function
 * 
 */
void Solution()
{
    Node *root = NULL;
    char *op = malloc(25 * sizeof(char));
    int operand_number;
    int CaseNumber = -1;

    while (scanf("%s %d", op, &operand_number) != EOF)
    {
        switch (CaseNumber = FindCase(op))
        {
        case 1:
            if (!exists(root, operand_number))
            {
                int priority = rand();
                root = insert(root, operand_number, priority);
            }
            break;
        case 2:
            if (exists(root, operand_number))
            {
                root = delete (root, operand_number);
            }
            break;
        case 3:
            printf("%s\n", exists(root, operand_number) ? "true" : "false");
            break;
        case 4:
            Node *p = next(root, operand_number);
            if (p)
            {
                printf("%d\n", p->key);
            }
            else
            {
                printf("none\n");
            }
            break;
        case 5:
            Node *pt = prev(root, operand_number);
            if (pt)
            {
                printf("%d\n", pt->key);
            }
            else
            {
                printf("none\n");
            }
            break;
        case 6:
            int kth_value = kth(root, operand_number);
            if (kth_value >= 0)
            {
                printf("%d\n", kth_value);
            }
            else
            {
                printf("none\n");
            }
            break;
        default:
            break;
        }
    }
}

int main()
{

    Solution();
    return 0;
}