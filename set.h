// set.h ... interface to simple Set of Strings
// Written by John Shepherd, September 2015

#ifndef SET_H
#define SET_H

typedef struct Node *List;
typedef struct GraphRep *Graph;

typedef struct node *Link;
typedef struct SetRep *Set;


typedef struct node {
	char *url;
	double pg;
	double tfidf;
	float index; //part3 value1
	int order;   //part3 matching
	int num_in;
	int num_out;
	Link  next;
} node;

typedef struct SetRep {
	int   nelems;
	Link  elems;
  Link 	first;
	Link 	last;
} SetRep;

// Function signatures

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
void dropFrom(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
void showSet(Set);
void showTfidf(Set s);

void tfidf_sorted (Set L, Link curr);
Set descending_tfidf(Set L);

int whereIsElem(Set s, char *str);
void insertDegree(Set s, int in[], int out[], double pgRank[]);
Set descending(Set L);
void sorted (Set L, Link curr);
void Print(FILE *outf, Set L);

void insertPg(Set s, double *pg);
void Duplicate(Set s);
int check(Set s,char * str);


void insertIndex(Set s, char *str,int index);
void process(Set s, int num);
float compare(Set L,Set s,int index);
void urlsorted(Set L, char *str);
void matchingP(Set s, int arr[],int num);
Set ListP(Set L);
void showOrder(Set s);
#endif
