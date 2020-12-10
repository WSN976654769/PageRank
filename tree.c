// Binary Search Tree ADT implementation ...

//from exercise7
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "treeSet.h"
// #include "set.h"
#define strLT(it,word)  (strcmp((it),(word(t)))<0)
#define strBT(it,word)  (strcmp((it),(word(t)))>0)


extern char * strdup(const char *__s);

typedef struct set *treeSet;
typedef struct setRep *treeTable;

typedef struct node *Link;
typedef struct SetRep *Set;



// make a new node containing word
Tree newNode(char *it){
   Tree new = malloc(sizeof(treeNode));
   assert(new != NULL);
   word(new) = strdup(it);
   left(new) = right(new) = NULL;
   new->urlList=makeTable();
   return new;
}


// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(left(t), depth+1);
      printf("%s ", word(t));
      show(t->urlList);
      showTreeR(right(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}



// count #treeNodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, char *it) {
   if (t == NULL)
      return false;
   else if (strLT(it,word))
      return TreeSearch(left(t), it);
   else if (strBT(it,word))
      return TreeSearch(right(t), it);
   else                                 // it == word(t)
      return true;
}

// insert a new char into a Tree
Tree TreeInsert(Tree t, char *it, char *url) {
   if (t == NULL)
   {
      t = newNode(it);
      insertSorted(t->urlList, url);
   }
   else if (strLT(it,word))
   {
      left(t) = TreeInsert(left(t), it,url);
  }
   else if (strBT(it,word))
   {
      right(t) = TreeInsert(right(t), it,url);
   }
   else
      insertSorted(t->urlList, url);
   return t;
}


void pshowTreeR(Tree t, int depth,FILE *outf) {
   if (t != NULL) {
      pshowTreeR(left(t), depth+1,outf);
      fprintf(outf,"%s ", word(t));
      //showp(outf,t->urlList);
      treeSet curr;
      int count=0;
      curr = t->urlList->first;
  		while (curr != NULL)
      {
          fprintf(outf,"%s ",curr->url);
    			count++;
    			curr = curr->next;
  		}
       fprintf(outf,"\n");
      pshowTreeR(right(t), depth+1,outf);
   }

}

void printTree(FILE *outf, Tree t)
{
  pshowTreeR(t, 0, outf);
	fclose(outf);
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
    	 left(parent) = right(curr);  // unlink min element from parent
    	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an char from a Tree
Tree TreeDelete(Tree t, char *it) {
   if (t != NULL) {
      if (strLT(it,word))
	 left(t) = TreeDelete(left(t), it);
      else if (strBT(it,word))
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL)
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, char *it) {

   printf("Not yet implemented.\n");

   return t;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
	 left(t) = partition(left(t), i);
	 t = rotateRight(t);
      } else if (i > m) {
	 right(t) = partition(right(t), i-m-1);
	 t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}
