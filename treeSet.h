#include <stdbool.h>

typedef struct set *treeSet;
typedef struct setRep *treeTable;


typedef struct set {
   char   * url;
   treeSet next;
} set;

typedef struct setRep {
	int   nelems;
	treeSet  elems;
  treeSet 	first;
	treeSet 	last;
} setRep;


//treeTable *makeTable();
void insert(treeTable s, char *str);
void show(treeTable s);
void insertSorted (treeTable s, char *str);


treeTable makeTable();

//void showP(FILE *,treeTable s);
//charindex(treeSet L);
