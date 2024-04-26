#include <stdio.h>
#include <stdlib.h>

typedef struct sTree Tree;

struct sTree {
    int value;                  // Value stored in the tree node
    unsigned int height;        // Height of the node in the tree
    Tree* left;                 // Pointer to the left child node
    Tree* right;                // Pointer to the right child node
};

Tree* create_tree(int x) {
    Tree* now_tree = (Tree*)malloc(sizeof(Tree));  // Allocate memory for a new tree node
    now_tree->height = 1;                         // Set the height of the new node to 1
    now_tree->value = x;                          // Set the value of the new node
    now_tree->left = NULL;                        // Initialize left child as NULL
    now_tree->right = NULL;                       // Initialize right child as NULL
    return now_tree;                              // Return the pointer to the new node
}

void correct_height(Tree* myTree) {
    unsigned int height_left = 0;     // Initialize left child height to 0
    unsigned int height_right = 0;    // Initialize right child height to 0
    if (myTree->left != NULL) {
        height_left = myTree->left->height;   // Update left child height if exists
    }
    if (myTree->right != NULL) {
        height_right = myTree->right->height; // Update right child height if exists
    }
    if (height_left > height_right) {
        myTree->height = height_left + 1;     // Set node height as left child height + 1
    }
    else {
        myTree->height = height_right + 1;    // Set node height as right child height + 1
    }
}

Tree* rotate_right(Tree* myTree) {
    Tree* temp = myTree->left;         // Store the left child of the node in a temporary variable
    myTree->left = temp->right;        // Set the left child of the node to the right child of its left child
    temp->right = myTree;              // Set the right child of the temporary node to the current node
    correct_height(myTree);            // Update heights of current node and its left child
    correct_height(temp);               // Update heights of temporary node and its children
    return temp;                        // Return the new root of the subtree
}

Tree* rotate_left(Tree* myTree) {
    Tree* temp = myTree->right;        // Store the right child of the node in a temporary variable
    myTree->right = temp->left;        // Set the right child of the node to the left child of its right child
    temp->left = myTree;               // Set the left child of the temporary node to the current node
    correct_height(myTree);            // Update heights of current node and its right child
    correct_height(temp);               // Update heights of temporary node and its children
    return temp;                        // Return the new root of the subtree
}

int delta_height(Tree* myTree) {
    unsigned int height_left = 0;       // Initialize left child height to 0
    unsigned int height_right = 0;      // Initialize right child height to 0
    if (myTree->left != NULL) {
        height_left = myTree->left->height;   // Update left child height if exists
    }
    if (myTree->right != NULL) {
        height_right = myTree->right->height; // Update right child height if exists
    }
    return height_right - height_left;        // Return the difference in heights
}

Tree* balance(Tree* myTree) {
    correct_height(myTree);           // Update the height of the current node

    if (delta_height(myTree) == 2) { // Check if the balance factor is 2 (right heavy)
        if (delta_height(myTree->right) < 0) {
            myTree->right = rotate_right(myTree->right);  // Rotate the right child to the right
        }
        return rotate_left(myTree);    // Rotate the current node to the left
    }
    else if (delta_height(myTree) == -2) { // Check if the balance factor is -2 (left heavy)
        if (delta_height(myTree->left) > 0) {
            myTree->left = rotate_left(myTree->left);     // Rotate the left child to the left
        }
        return rotate_right(myTree);   // Rotate the current node to the right
    }

    return myTree;                     // Return the current node if balanced
}

Tree* insert(Tree* myTree, int x) {
    if (myTree == NULL) {
        return create_tree(x);          // Create a new node if tree is empty
    }
    if (x < myTree->value) {
        myTree->left = insert(myTree->left, x);   // Insert into left subtree if value is less
    }
    else {
        myTree->right = insert(myTree->right, x); // Insert into right subtree if value is greater
    }
    return balance(myTree);            // Balance the tree after insertion
}

void show_line(char* c, int p, int s) {
    int t = s, i;
    for (i = 0; i < p; i++) {
        printf(t & 1 ? "|  " : "   ");    // Print appropriate indentation based on position
        t /= 2;
    }
    printf(c);                            // Print the character or string
}


// not my
void show_tree(Tree* myTree, int p, int s) {
    if (myTree == NULL) return;          // Base case: return if node is NULL
    printf("%d", myTree->value);         // Print the value of the current node
    printf("\n");

    if (myTree->left != NULL) {
        show_line("|\n", p, s);           // Print vertical line if left child exists
        show_line("L: ", p, s);           // Print label for left child
        show_tree(myTree->left, p + 1, s + ((myTree->right == NULL ? 0 : 1) << p));  // Recursively print left subtree
    }
    if (myTree->right != NULL) {
        show_line("|\n", p, s);           // Print vertical line if right child exists
        show_line("R: ", p, s);           // Print label for right child
        show_tree(myTree->right, p + 1, s);  // Recursively print right subtree
    }
}
// end of not my


int arr_len(int arr[]) {

    int len = 0;
    while (arr[len] != '\0') {
        len++;
    }
    return len;
}

Tree* myTree = NULL;
int arr[] = { 5, 6, 4, 12, 15, 1, 11, 17, 18, 2 }; // Array of values to insert into the tree

int main() {
    for (int i = 0; i < arr_len(arr); i++) {
        myTree = insert(myTree, arr[i]);   // Insert each value from the array into the tree
    }

    show_tree(myTree, 0, 0);                // Display the tree starting from the root

    return 0;
}
