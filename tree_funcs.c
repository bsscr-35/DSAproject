#include <stdio.h>

#define MAX 100
#define EMPTY -1

int bst[MAX];

void insert(int value) {
    int index = 0;
    while (index < MAX && bst[index] != EMPTY) {
        index = (value < bst[index]) ? 2 * index + 1 : 2 * index + 2;
    }
    if (index < MAX) bst[index] = value;
}

void inorderTraversal(int index) {
    if (index >= MAX || bst[index] == EMPTY) return;
    inorderTraversal(2 * index + 1);
    printf("%d ", bst[index]);
    inorderTraversal(2 * index + 2);
}

int search(int value) {
    int index = 0;
    while (index < MAX && bst[index] != EMPTY) {
        if (bst[index] == value) return 1;
        index = (value < bst[index]) ? 2 * index + 1 : 2 * index + 2;
    }
    return 0;
}

int findMin() {
    int index = 0;
    while (index < MAX && bst[index] != EMPTY) {
        int left = 2 * index + 1;
        if (left >= MAX || bst[left] == EMPTY) return bst[index];
        index = left;
    }
    return EMPTY;
}

int findHeightHelper(int index) {
    if (index >= MAX || bst[index] == EMPTY) return -1;
    int leftHeight = findHeightHelper(2 * index + 1);
    int rightHeight = findHeightHelper(2 * index + 2);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int findHeight() {
    return findHeightHelper(0);
}

int countNodesHelper(int index) {
    if (index >= MAX || bst[index] == EMPTY) return 0;
    return 1 + countNodesHelper(2 * index + 1) + countNodesHelper(2 * index + 2);
}

int countNodes() {
    return countNodesHelper(0);
}

int findMax() {
    int index = 0;
    while (index < MAX && bst[index] != EMPTY) {
        int right = 2 * index + 2;
        if (right >= MAX || bst[right] == EMPTY) return bst[index];
        index = right;
    }
    return EMPTY;
}

void deleteNodeHelper(int index, int value) {
    if (index >= MAX || bst[index] == EMPTY) return;
    if (value < bst[index]) deleteNodeHelper(2 * index + 1, value);
    else if (value > bst[index]) deleteNodeHelper(2 * index + 2, value);
    else {
        int left = 2 * index + 1, right = 2 * index + 2;
        if ((left >= MAX || bst[left] == EMPTY) && (right >= MAX || bst[right] == EMPTY)) bst[index] = EMPTY;
        else if (left >= MAX || bst[left] == EMPTY) {
            bst[index] = bst[right];
            deleteNodeHelper(right, bst[right]);
        } else if (right >= MAX || bst[right] == EMPTY) {
            bst[index] = bst[left];
            deleteNodeHelper(left, bst[left]);
        } else {
            int successor = right;
            while (2 * successor + 1 < MAX && bst[2 * successor + 1] != EMPTY)
                successor = 2 * successor + 1;
            bst[index] = bst[successor];
            deleteNodeHelper(successor, bst[successor]);
        }
    }
}

void deleteNode(int value) {
    deleteNodeHelper(0, value);
}

int main() {
    printf("--- Array-Based BST ---\n\n");
    for (int i = 0; i < MAX; i++) bst[i] = EMPTY;

    printf("--- Insert ---\n");
    insert(50); insert(30); insert(70); insert(20); insert(40); insert(60); insert(80);
    printf("Inserted 50, 30, 70, 20, 40, 60, 80.\n\n");

    printf("Inorder: \n");
    inorderTraversal(0); printf("\n");

    printf("--- Search ---\n");
    int s1 = 40, s2 = 90;
    printf("Searching %d: %s\n", s1, search(s1) ? "FOUND" : "NOT FOUND");
    printf("Searching %d: %s\n\n", s2, search(s2) ? "FOUND" : "NOT FOUND");

    printf("--- Min ---\n");
    int min = findMin();
    if (min != EMPTY) printf("Min: %d\n", min);
    else printf("Empty tree.\n");
    printf("\n");

    printf("--- Height ---\n");
    printf("Height: %d\n\n", findHeight());

    printf("--- Count ---\n");
    printf("Count: %d\n\n", countNodes());

    printf("--- Max ---\n");
    printf("Max: %d\n\n", findMax());

    printf("--- Delete 40 ---\n");
    deleteNode(40);
    printf("Inorder: \n");
    inorderTraversal(0); printf("\n");

    return 0;
}