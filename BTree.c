#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEYS (2 * t - 1)
#define MIN_KEYS (t - 1)

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int num_keys;
    bool is_leaf;
} BTreeNode;

int t; // Minimum degree of the B-tree

// Function prototypes
BTreeNode* create_node(bool is_leaf);
void insert(int key);
void insert_non_full(BTreeNode *node, int key);
void split_child(BTreeNode *parent, int index);
void delete(int key);
void delete_from_node(BTreeNode *node, int key);
void merge_nodes(BTreeNode *parent, int index);
void borrow_from_prev(BTreeNode *node, int index);
void borrow_from_next(BTreeNode *node, int index);
void fill(BTreeNode *node, int index);
int get_predecessor(BTreeNode *node, int index);
int get_successor(BTreeNode *node, int index);
void traverse(BTreeNode *node);
void free_tree(BTreeNode *node);

BTreeNode *root = NULL;

// Create a new B-tree node
BTreeNode* create_node(bool is_leaf) {
    BTreeNode *new_node = (BTreeNode*)malloc(sizeof(BTreeNode));
    new_node->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    new_node->children = (BTreeNode**)malloc(2 * t * sizeof(BTreeNode*));
    new_node->num_keys = 0;
    new_node->is_leaf = is_leaf;
    return new_node;
}

// Insert a key into the B-tree
void insert(int key) {
    if (root == NULL) {
        root = create_node(true);
        root->keys[0] = key;
        root->num_keys = 1;
    } else {
        if (root->num_keys == MAX_KEYS) {
            BTreeNode *new_root = create_node(false);
            new_root->children[0] = root;
            split_child(new_root, 0);
            root = new_root;
        }
        insert_non_full(root, key);
    }
}

// Insert into a non-full node
void insert_non_full(BTreeNode *node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

// Split a full child node
void split_child(BTreeNode *parent, int index) {
    BTreeNode *child = parent->children[index];
    BTreeNode *new_node = create_node(child->is_leaf);
    new_node->num_keys = MIN_KEYS;
    
    // Copy the right half of keys to the new node
    for (int j = 0; j < MIN_KEYS; j++) {
        new_node->keys[j] = child->keys[j + t];
    }
    
    // Copy the right half of children if not a leaf
    if (!child->is_leaf) {
        for (int j = 0; j < t; j++) {
            new_node->children[j] = child->children[j + t];
        }
    }
    
    child->num_keys = MIN_KEYS;
    
    // Shift parent's children to make space for the new node
    for (int j = parent->num_keys; j >= index + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = new_node;
    
    // Shift parent's keys and insert the middle key from child
    for (int j = parent->num_keys - 1; j >= index; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[index] = child->keys[t - 1];
    parent->num_keys++;
}

// Delete a key from the B-tree
void delete(int key) {
    if (root == NULL) {
        printf("The tree is empty\n");
        return;
    }
    
    delete_from_node(root, key);
    
    // If root has 0 keys, make its first child the new root if it exists
    if (root->num_keys == 0) {
        BTreeNode *temp = root;
        if (root->is_leaf) {
            root = NULL;
        } else {
            root = root->children[0];
        }
        free(temp->keys);
        free(temp->children);
        free(temp);
    }
}

// Delete a key from a node
void delete_from_node(BTreeNode *node, int key) {
    int index = 0;
    while (index < node->num_keys && key > node->keys[index]) {
        index++;
    }
    
    if (index < node->num_keys && key == node->keys[index]) {
        // Key found in this node
        if (node->is_leaf) {
            // Case 1: Key is in a leaf node
            for (int i = index + 1; i < node->num_keys; i++) {
                node->keys[i - 1] = node->keys[i];
            }
            node->num_keys--;
        } else {
            // Case 2: Key is in an internal node
            if (node->children[index]->num_keys >= t) {
                // Case 2a: Predecessor has at least t keys
                int pred = get_predecessor(node, index);
                node->keys[index] = pred;
                delete_from_node(node->children[index], pred);
            } else if (node->children[index + 1]->num_keys >= t) {
                // Case 2b: Successor has at least t keys
                int succ = get_successor(node, index);
                node->keys[index] = succ;
                delete_from_node(node->children[index + 1], succ);
            } else {
                // Case 2c: Merge the child and its right sibling
                merge_nodes(node, index);
                delete_from_node(node->children[index], key);
            }
        }
    } else {
        // Key not found in this node
        if (node->is_leaf) {
            printf("Key %d not found in the tree\n", key);
            return;
        }
        
        bool flag = (index == node->num_keys);
        
        if (node->children[index]->num_keys < t) {
            fill(node, index);
        }
        
        if (flag && index > node->num_keys) {
            delete_from_node(node->children[index - 1], key);
        } else {
            delete_from_node(node->children[index], key);
        }
    }
}

// Merge two child nodes
void merge_nodes(BTreeNode *parent, int index) {
    BTreeNode *child = parent->children[index];
    BTreeNode *sibling = parent->children[index + 1];
    
    // Bring the key from the parent down into the child
    child->keys[t - 1] = parent->keys[index];
    
    // Copy keys from the sibling to the child
    for (int i = 0; i < sibling->num_keys; i++) {
        child->keys[i + t] = sibling->keys[i];
    }
    
    // Copy children from the sibling if not a leaf
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; i++) {
            child->children[i + t] = sibling->children[i];
        }
    }
    
    // Shift parent's keys and children to fill the gap
    for (int i = index + 1; i < parent->num_keys; i++) {
        parent->keys[i - 1] = parent->keys[i];
    }
    for (int i = index + 2; i <= parent->num_keys; i++) {
        parent->children[i - 1] = parent->children[i];
    }
    
    child->num_keys += sibling->num_keys + 1;
    parent->num_keys--;
    
    // Free the sibling
    free(sibling->keys);
    free(sibling->children);
    free(sibling);
}

// Borrow a key from the previous sibling
void borrow_from_prev(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index - 1];
    
    // Shift all keys in child right by one
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    
    // Shift all children in child right by one if not a leaf
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }
    
    // Move a key from the parent down to the child
    child->keys[0] = node->keys[index - 1];
    
    // Move a key from the sibling up to the parent
    if (!child->is_leaf) {
        child->children[0] = sibling->children[sibling->num_keys];
    }
    
    node->keys[index - 1] = sibling->keys[sibling->num_keys - 1];
    
    child->num_keys++;
    sibling->num_keys--;
}

// Borrow a key from the next sibling
void borrow_from_next(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index + 1];
    
    // Move a key from the parent down to the child
    child->keys[child->num_keys] = node->keys[index];
    
    // Move a key from the sibling up to the parent
    node->keys[index] = sibling->keys[0];
    
    // Shift all keys in the sibling left by one
    for (int i = 1; i < sibling->num_keys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    
    // Shift all children in the sibling left by one if not a leaf
    if (!sibling->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
        for (int i = 1; i <= sibling->num_keys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    
    child->num_keys++;
    sibling->num_keys--;
}

// Fill a child that has less than t-1 keys
void fill(BTreeNode *node, int index) {
    if (index != 0 && node->children[index - 1]->num_keys >= t) {
        borrow_from_prev(node, index);
    } else if (index != node->num_keys && node->children[index + 1]->num_keys >= t) {
        borrow_from_next(node, index);
    } else {
        if (index != node->num_keys) {
            merge_nodes(node, index);
        } else {
            merge_nodes(node, index - 1);
        }
    }
}

// Get the predecessor of a key (rightmost key in the left subtree)
int get_predecessor(BTreeNode *node, int index) {
    BTreeNode *current = node->children[index];
    while (!current->is_leaf) {
        current = current->children[current->num_keys];
    }
    return current->keys[current->num_keys - 1];
}

// Get the successor of a key (leftmost key in the right subtree)
int get_successor(BTreeNode *node, int index) {
    BTreeNode *current = node->children[index + 1];
    while (!current->is_leaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

// Traverse the B-tree (in-order)
void traverse(BTreeNode *node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->num_keys; i++) {
            if (!node->is_leaf) {
                traverse(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->is_leaf) {
            traverse(node->children[i]);
        }
    }
}

// Free the B-tree memory
void free_tree(BTreeNode *node) {
    if (node != NULL) {
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                free_tree(node->children[i]);
            }
        }
        free(node->keys);
        free(node->children);
        free(node);
    }
}

// Insert a sequence of keys
void insert_sequence(int keys[], int n) {
    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }
}

// Delete a sequence of keys
void delete_sequence(int keys[], int n) {
    for (int i = 0; i < n; i++) {
        delete(keys[i]);
    }
}

int main() {
    printf("Enter the minimum degree (t) of the B-tree (t >= 2): ");
    scanf("%d", &t);
    
    if (t < 2) {
        printf("Minimum degree must be at least 2\n");
        return 1;
    }
    
    int choice;
    int key;
    int n;
    
    while (1) {
        printf("\nB-Tree Operations:\n");
        printf("1. Insert a key\n");
        printf("2. Insert a sequence of keys\n");
        printf("3. Delete a key\n");
        printf("4. Delete a sequence of keys\n");
        printf("5. Traverse the tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter number of keys to insert: ");
                scanf("%d", &n);
                int *insert_keys = (int*)malloc(n * sizeof(int));
                printf("Enter %d keys to insert: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &insert_keys[i]);
                }
                insert_sequence(insert_keys, n);
                free(insert_keys);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                printf("Enter number of keys to delete: ");
                scanf("%d", &n);
                int *delete_keys = (int*)malloc(n * sizeof(int));
                printf("Enter %d keys to delete: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &delete_keys[i]);
                }
                delete_sequence(delete_keys, n);
                free(delete_keys);
                break;
            case 5:
                printf("B-Tree traversal: ");
                traverse(root);
                printf("\n");
                break;
            case 6:
                free_tree(root);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}