// Binary Search Tree ADT interface ...
//
#include <stdbool.h>

typedef struct treeNode *Tree;
typedef struct setRep *treeTable;



typedef struct node *Link;
typedef struct SetRep *Set;
typedef struct treeNode {
   char *word;
   Tree left, right;
   treeTable urlList;
} treeNode;
//
// typedef struct webNode {
//    char *web;
//    Url left, right;
// } webNode;



#define word(tree)  ((tree)->word)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)
#define web(tree)  ((tree)->word)


Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)
void printTree(FILE *outf, Tree t);



bool TreeSearch(Tree, char *);   // check whether an char is in a Tree
int  TreeHeight(Tree);         // compute height of Tree
int  TreeNumNodes(Tree);       // count #nodes in Tree
//Tree TreeInsert(Tree, char *);   // insert a new char into a Tree
Tree TreeInsert(Tree t, char *it,char *);



Tree TreeDelete(Tree, char *);   // delete an char from a Tree

// internal functions made visible for testing
Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertAtRoot(Tree, char *);
Tree partition(Tree, int);
Tree rebalance(Tree);
