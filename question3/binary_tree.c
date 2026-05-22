/*
 * Question 3 - binary tree from 68 component IDs
 *
 * INSERTION RULE (Binary Search Tree):
 *   if value < current node  -> insert in left subtree
 *   if value > current node  -> insert in right subtree
 *   if subtree is empty     -> attach new node
 *   (all values in the array are distinct)
 */

#include <stdio.h>
#include <stdlib.h>

#define N 68

typedef struct TNode {
    int data;
    struct TNode *left;
    struct TNode *right;
    struct TNode *parent;
} TNode;

int arr[N] = {
    50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85,
    5, 15, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72, 77, 82,
    87, 92, 3, 8, 12, 18, 28, 33, 38, 43, 48, 53, 58, 63, 68,
    73, 78, 83, 88, 93, 98, 1, 6, 11, 16, 21, 26, 31, 36, 41,
    46, 51, 56, 61, 66, 71, 76, 81
};

TNode *insertBST(TNode *root, int val, TNode *par) {
    if (root == NULL) {
        TNode *n = (TNode *)malloc(sizeof(TNode));
        if (n == NULL) {
            printf("Memory allocation failed.\n");
            return NULL;
        }
        n->data = val;
        n->left = n->right = NULL;
        n->parent = par;
        return n;
    }
    if (val < root->data)
        root->left = insertBST(root->left, val, root);
    else if (val > root->data)
        root->right = insertBST(root->right, val, root);
    return root;
}

TNode *findNode(TNode *root, int val) {
    if (root == NULL)
        return NULL;
    if (val == root->data)
        return root;
    if (val < root->data)
        return findNode(root->left, val);
    return findNode(root->right, val);
}

void freeTree(TNode *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printLeaves(TNode *root) {
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        printf("  Leaf: %d\n", root->data);
    else {
        printLeaves(root->left);
        printLeaves(root->right);
    }
}

void showSiblings(TNode *x) {
    TNode *p = x->parent;
    int found = 0;

    if (p == NULL) {
        printf("Siblings: none (selected node is root)\n");
        return;
    }

    printf("Siblings:\n");
    if (p->left != NULL && p->left != x) {
        printf("  %d\n", p->left->data);
        found = 1;
    }
    if (p->right != NULL && p->right != x) {
        printf("  %d\n", p->right->data);
        found = 1;
    }
    if (!found)
        printf("  none\n");
}

void showGrandchildren(TNode *x) {
    int c = 0;

    printf("Grandchildren:\n");
    if (x->left != NULL) {
        if (x->left->left != NULL) {
            printf("  %d\n", x->left->left->data);
            c++;
        }
        if (x->left->right != NULL) {
            printf("  %d\n", x->left->right->data);
            c++;
        }
    }
    if (x->right != NULL) {
        if (x->right->left != NULL) {
            printf("  %d\n", x->right->left->data);
            c++;
        }
        if (x->right->right != NULL) {
            printf("  %d\n", x->right->right->data);
            c++;
        }
    }
    if (c == 0)
        printf("  none\n");
}

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void) {
    TNode *root = NULL;
    int i, val;
    TNode *node;

    for (i = 0; i < N; i++) {
        root = insertBST(root, arr[i], NULL);
        if (root == NULL)
            return 1;
    }

    printf("Insertion rule: BST (smaller=left, greater=right)\n\n");

    printf("Root node: %d\n\n", root->data);

    printf("Leaf nodes:\n");
    printLeaves(root);

    while (1) {
        printf("\nEnter node value to query (0 to quit): ");
        if (scanf("%d", &val) != 1) {
            clearInput();
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        clearInput();

        if (val == 0)
            break;

        node = findNode(root, val);
        if (node == NULL) {
            printf("Error: %d is not in the tree.\n", val);
            continue;
        }

        printf("\nNode %d:\n", val);
        if (node->parent != NULL)
            printf("Parent: %d\n", node->parent->data);
        else
            printf("Parent: none\n");

        showSiblings(node);
        showGrandchildren(node);
    }

    freeTree(root);
    printf("\nTree deleted. Program ended.\n");
    return 0;
}
