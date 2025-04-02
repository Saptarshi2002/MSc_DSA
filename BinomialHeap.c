#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a Binomial Heap Node
struct Node {
    int key;
    int degree;
    struct Node *parent;
    struct Node *child;
    struct Node *sibling;
};

// Structure for Binomial Heap
struct BinomialHeap {
    struct Node *head;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to create an empty binomial heap
struct BinomialHeap* makeBinomialHeap() {
    struct BinomialHeap *heap = (struct BinomialHeap*)malloc(sizeof(struct BinomialHeap));
    heap->head = NULL;
    return heap;
}

// Function to merge two binomial trees of same degree
struct Node* binomialLink(struct Node *y, struct Node *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return z;
}

// Function to merge two binomial heaps
struct Node* binomialHeapMerge(struct Node *h1, struct Node *h2) {
    struct Node *heap = NULL;
    struct Node **pos = &heap;
    
    while (h1 != NULL && h2 != NULL) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }
    
    if (h1 != NULL) {
        *pos = h1;
    } else {
        *pos = h2;
    }
    
    return heap;
}

// Function to union two binomial heaps
struct Node* binomialHeapUnion(struct Node *h1, struct Node *h2) {
    struct Node *heap = binomialHeapMerge(h1, h2);
    if (heap == NULL) {
        return NULL;
    }
    
    struct Node *prev_x = NULL;
    struct Node *x = heap;
    struct Node *next_x = x->sibling;
    
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || 
            (next_x->sibling != NULL && next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else if (x->key <= next_x->key) {
            x->sibling = next_x->sibling;
            binomialLink(next_x, x);
        } else {
            if (prev_x == NULL) {
                heap = next_x;
            } else {
                prev_x->sibling = next_x;
            }
            binomialLink(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    
    return heap;
}

// Function to insert a node into binomial heap
void binomialHeapInsert(struct BinomialHeap *heap, struct Node *x) {
    struct BinomialHeap *tempHeap = makeBinomialHeap();
    tempHeap->head = x;
    heap->head = binomialHeapUnion(heap->head, tempHeap->head);
    free(tempHeap);
}

// Function to reverse a list of binomial trees
struct Node* reverseBinomialTrees(struct Node *heap) {
    struct Node *prev = NULL;
    struct Node *current = heap;
    struct Node *next;
    
    while (current != NULL) {
        next = current->sibling;
        current->sibling = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

// Function to extract the node with minimum key from binomial heap
struct Node* binomialHeapExtractMin(struct BinomialHeap *heap) {
    if (heap->head == NULL) {
        return NULL;
    }
    
    // Find the root with minimum key
    struct Node *min_node_prev = NULL;
    struct Node *min_node = heap->head;
    struct Node *prev = NULL;
    struct Node *current = heap->head;
    int min = INT_MAX;
    
    while (current != NULL) {
        if (current->key < min) {
            min = current->key;
            min_node = current;
            min_node_prev = prev;
        }
        prev = current;
        current = current->sibling;
    }
    
    // Remove the min node from the root list
    if (min_node_prev == NULL) {
        heap->head = min_node->sibling;
    } else {
        min_node_prev->sibling = min_node->sibling;
    }
    
    // Reverse the order of min node's children
    struct Node *new_heap = reverseBinomialTrees(min_node->child);
    
    // Union the original heap with the new heap formed by min node's children
    struct BinomialHeap *tempHeap = makeBinomialHeap();
    tempHeap->head = new_heap;
    heap->head = binomialHeapUnion(heap->head, tempHeap->head);
    free(tempHeap);
    
    return min_node;
}

// Function to print binomial trees
void printBinomialTree(struct Node *node, int level) {
    while (node != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("%d (degree: %d)\n", node->key, node->degree);
        if (node->child != NULL) {
            printBinomialTree(node->child, level + 1);
        }
        node = node->sibling;
    }
}

// Function to print binomial heap
void printBinomialHeap(struct BinomialHeap *heap) {
    struct Node *current = heap->head;
    printf("Binomial Heap:\n");
    while (current != NULL) {
        printBinomialTree(current, 0);
        current = current->sibling;
        printf("\n");
    }
    printf("\n");
}

// Main function to demonstrate the extract-min operation
int main() {
    // Create a binomial heap with at least 6 binomial trees
    struct BinomialHeap *heap = makeBinomialHeap();
    
    // Insert nodes to create binomial trees of different degrees
    // We'll create trees of degrees 0, 1, 2, 3, 4, 5 (6 trees total)
    // The minimum will be placed in the largest (degree 5) or next-to-largest (degree 4) tree
    
    // Insert nodes to build the binomial heap
    // Tree B0 (degree 0)
    struct Node *node1 = createNode(5);
    binomialHeapInsert(heap, node1);
    
    // Tree B1 (degree 1)
    struct Node *node2 = createNode(3);
    struct Node *node3 = createNode(8);
    node2->child = node3;
    node2->degree = 1;
    node3->parent = node2;
    binomialHeapInsert(heap, node2);
    
    // Tree B2 (degree 2)
    struct Node *node4 = createNode(1);  // This will be our minimum in largest tree
    struct Node *node5 = createNode(7);
    struct Node *node6 = createNode(9);
    struct Node *node7 = createNode(10);
    node4->child = node5;
    node4->degree = 2;
    node5->parent = node4;
    node5->sibling = node6;
    node6->parent = node4;
    node5->child = node7;
    node5->degree = 1;
    node7->parent = node5;
    binomialHeapInsert(heap, node4);
    
    // Tree B3 (degree 3)
    struct Node *node8 = createNode(2);
    struct Node *node9 = createNode(6);
    struct Node *node10 = createNode(11);
    struct Node *node11 = createNode(12);
    struct Node *node12 = createNode(13);
    struct Node *node13 = createNode(14);
    struct Node *node14 = createNode(15);
    node8->child = node9;
    node8->degree = 3;
    node9->parent = node8;
    node9->sibling = node10;
    node10->parent = node8;
    node9->child = node11;
    node9->degree = 2;
    node11->parent = node9;
    node11->sibling = node12;
    node12->parent = node9;
    node11->child = node13;
    node11->degree = 1;
    node13->parent = node11;
    node10->child = node14;
    node10->degree = 1;
    node14->parent = node10;
    binomialHeapInsert(heap, node8);
    
    // Print the heap before extraction
    printf("Heap before Extract-Min:\n");
    printBinomialHeap(heap);
    
    // Perform Extract-Min operation
    struct Node *minNode = binomialHeapExtractMin(heap);
    if (minNode != NULL) {
        printf("Extracted minimum node with key: %d\n", minNode->key);
        free(minNode);
    }
    
    // Print the heap after extraction
    printf("Heap after Extract-Min:\n");
    printBinomialHeap(heap);

    
    return 0;
}