// Linked list interface ... COMP2521
#include <stdbool.h>

typedef struct Node *List;
typedef struct Node {
   int         v;
   struct Node *next;
} Node;

List insertLL(List, int);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);

int getNextNode(List L);
//int index(List L);
