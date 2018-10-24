// Binary Search Tree ADT implementation ... 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"

typedef struct ListNodeRep {
    struct ListNode *head;
} ListNodeRep;

typedef struct ListNode {   // linked list struture that will repressent a list of urls
    char *link;
    struct ListNode *next;  
} ListNode;


typedef struct Node {   // represents each node in the tree
    char *word;  // key
    ListNodeRep *url;
    Tree *left;
    Tree *right;
} Node;

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// make a new ListNodeRep
ListNodeRep newListNodeRep() {
    struct ListNodeRep *L;
    
    L = malloc(sizeof(ListNodeRep));
    assert(L != NULL);
    L->head = NULL;
}


// make a new ListNode (local)
 static ListNode *newListNode(Item *url) {
    ListNode *new = malloc(sizeof(ListNode));
    assert(new != NULL);
    new->link = strdup(url);
    new->next = NULL;

    return new;
}

// make a new node containing data
Tree newNode(Item *it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    new->word = strdup(it);
    new->url = newListNodeRep();
    new->left = new->right = NULL;
    
    return new;
}


// check whether a word is in a Tree
bool TreeSearch(Tree t, Item *it) {
   if (t == NULL) {
      return false;
   } else if (strcmp(it, t->word) < 0) {
      return TreeSearch(t->left, it);
   } else if (strcmp(it, t->word) > 0) {
      return TreeSearch(t->right, it);
   } else {                          // it == data(t)
      return true;
   }

}


// insert a new item into a Tree
Tree TreeInsert(Tree t, Item *it, Item *url) {
   if (t == NULL) {
      t = newNode(it);
      ListNode *newURL = newListNode(url);
      t->url->head = newURL;
   } else if (strcmp(it, t->word) < 0) {
      t->left = TreeInsert(t->left, it, url);
   } else if (strcmp(it, t->word) > 0) {
      t->right = TreeInsert(t->right, it, url);
   } else if (strcmp(it , t->word) == 0) {
       insertOrder(t, url);
   }

return t;
}

// insert new links into the correct position in ListNode
void insertOrder (Tree t, Item *url)
    ListNode *newURL = newListNode(url);
    ListNode *firstURL = t->url->head;
    
    // insert at before the first url
    if (strcmp(newURL->link , firstURL->link) < 0) {
            newURL->next = firstURL;
            firstURL = newURL;
            return;
    } else if (strcmp(newURL->link , firsURL->link) > 0) {
            ListNode *currURL = firstURL->next;

            while(currURL != NULL) {
                if (strcmp(newURL->link, currURL->link) > 0 && strcmp(newURL->link, currURL->next->link) < 0) {
                    newURL->next = currURL->next;
                    currURL->next = newURL;
                    return;
                } else {
                    currURL = currURL->next;
                }
            }
    }


// free memory associated with Tree
void freeTree(Tree t) {
    
    ListNode *curr, *prev;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev->link);
        free(prev)
    }
    free(t->url);

    free(t->word);

    if (t != NULL) {
        freeTree(t->left)
        freeTree(t->right);
        free(t);
   }
}
