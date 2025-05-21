#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Create a new node
Node* createNode(int data, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

// Build binary tree from array in level-order fashion
Node* insertLevelOrder(int arr[], int i, int n, Node* parent) {
    if (i >= n) return NULL;

    Node* root = createNode(arr[i], parent);
    root->left = insertLevelOrder(arr, 2 * i + 1, n, root);
    root->right = insertLevelOrder(arr, 2 * i + 2, n, root);
    return root;
}

// Return root
Node* getRoot(Node* root) {
    return root;
}

// Print leaf nodes
void printLeafNodes(Node* root) {
    if (!root) return;
    if (!root->left && !root->right)
        printf("%d ", root->data);
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Find a node by value
Node* findNode(Node* root, int value) {
    if (!root) return NULL;
    if (root->data == value) return root;
    Node* left = findNode(root->left, value);
    if (left) return left;
    return findNode(root->right, value);
}

// Print siblings
void printSiblings(Node* node) {
    if (!node || !node->parent) {
        printf("No siblings found (root or invalid).\n");
        return;
    }
    if (node->parent->left == node && node->parent->right)
        printf("Sibling: %d\n", node->parent->right->data);
    else if (node->parent->right == node && node->parent->left)
        printf("Sibling: %d\n", node->parent->left->data);
    else
        printf("No siblings.\n");
}

// Print parent
void printParent(Node* node) {
    if (!node || !node->parent)
        printf("No parent (root or invalid).\n");
    else
        printf("Parent: %d\n", node->parent->data);
}

// Print grandchildren
void printGrandchildren(Node* node) {
    if (!node) return;

    if (node->left) {
        if (node->left->left)
            printf("Grandchild: %d\n", node->left->left->data);
        if (node->left->right)
            printf("Grandchild: %d\n", node->left->right->data);
    }
    if (node->right) {
        if (node->right->left)
            printf("Grandchild: %d\n", node->right->left->data);
        if (node->right->right)
            printf("Grandchild: %d\n", node->right->right->data);
    }
}

int main() {
    int arr[SIZE] = {15, 6, 23, 4, 7, 17, 50, 1, 5, 8, 9, 16, 18, 45, 60, 0, 2, 3, 10, 11};

    Node* root = insertLevelOrder(arr, 0, SIZE, NULL);
    printf("Root Node: %d\n\n", getRoot(root)->data);

    printf("Leaf Nodes: ");
    printLeafNodes(root);
    printf("\n\n");

    int target;
    printf("Enter node value to find its siblings, parent, and grandchildren: ");
    scanf("%d", &target);

    Node* targetNode = findNode(root, target);
    if (!targetNode) {
        printf("Node not found.\n");
    } else {
        printSiblings(targetNode);
        printParent(targetNode);
        printGrandchildren(targetNode);
    }

    return 0;
}
