// Binary Search Tree ADT interface ... 

#include <stdbool.h>

typedef char *Item;      // Item is just a key

typedef struct Node *Tree;

Tree newTree();        // create an empty Tree
bool TreeSearch(Tree, Item *);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item *);   // insert a new item into a Tree
void freeTree(Tree);   // free memory associated with Tree
