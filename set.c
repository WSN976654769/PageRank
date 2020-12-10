// set.c ... simple, inefficient Set of Strings
// Written by John Shepherd, September 2015
//from wk 8 lab
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "graph.h"
#include "set.h"
#include "list.h"

#define strEQ(s,t) (strcmp((s),(t)) == 0)
#define strLT(s,t) (strcmp((s),(t)) < 0)

extern char * strdup(const char *__s);

typedef struct Node *List;
typedef struct GraphRep *Graph;

typedef struct node *Link;
typedef struct SetRep *Set;

//Function signatures
Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
void dropFrom(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
static Link newNode(char *);
void insertPg(Set s, double *pg);
static void disposeNode(Link);
static Link indexNode(char *str,int it);

static int findNode(Link,char *,Link *,Link *);
int whereIsElem(Set s, char *str);
void LookThrough(Set L,Graph in , Graph out);
void insertDegree(Set s, int in[], int out[],double pgRank[]);
Set descending(Set L);
void sorted (Set L, Link curr);
void Print(FILE *outf, Set L);
Set ListP(Set L);
// newSet()
// - create an initially empty Set
Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	new->first = NULL;
	new->last = NULL;
	return new;
}

// disposeSet(Set)
// - clean up memory associated with Set
void disposeSet(Set s)
{
	if (s == NULL) return;
	Link next, curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);
		curr = next;
	}
}

// insertInto(Set,Str)
// - ensure that Str is in Set
void insertInto(Set s, char *str)
{
	assert(s != NULL);
	Link new = newNode(str);

	if(s->first==NULL)
			s->elems = s->first = s->last=new;
	else
	{
			s->last->next=new;
			s->last=new;
	}
	s->nelems++;
}

void insertIndex(Set s, char *str,int index)
{
	//assert(s != NULL);
	Link new = indexNode(str,index);

	if(s->first==NULL)
			s->elems = s->first = s->last=new;
	else
	{
			s->last->next=new;
			s->last=new;
	}
	s->nelems++;
}


void process(Set s, int num){
	Link curr = s->first;
	while(curr!=NULL)
	{
		curr->index=curr->index/num;
		curr= curr->next;
	}
}

int check(Set s,char * str){
	Link curr = s->first;
	while(curr!=NULL)
	{
			if(strcmp(str,curr->url)==0)
			{
					return 1;

			}
			curr=curr->next;
	}
			return 0;
}

void Duplicate(Set s)
{
    Link pCurrent=NULL;
    Link pRuner=pCurrent=s->first;
    Link temp=NULL;
    while(pCurrent!=NULL)
    {
        while( pRuner->next!=NULL)
        {
            if(strcmp(pRuner->next->url,pCurrent->url)==0)
            {
                temp=pRuner->next;
                pRuner->next=temp->next;
                free(temp);
								s->nelems--;
            }
						else
						{
                pRuner=pRuner->next;
            }
        }
        pCurrent=pCurrent->next;
        pRuner=pCurrent;
    }
}
// dropFrom(Set,Str)
// - ensure that Str is not in Set
void dropFrom(Set s, char *str)
{
	assert(s != NULL);
	Link curr, prev;
	int found = findNode(s->elems,str,&curr,&prev);
	if (!found) return;
	s->nelems--;
	if (prev == NULL)
		s->elems = curr->next;
	else
		prev->next = curr->next;
	disposeNode(curr);
}

// isElem(Set,Str)
// - check whether Str is contained in Set
int isElem(Set s, char *str)
{
	assert(s != NULL);
	Link curr, prev;
	return findNode(s->elems,str,&curr,&prev);
}

// isElem(Set,Str)
// - check whether Str is contained in Set
int whereIsElem(Set s, char *str)
{
	assert(s != NULL);
  int index=0;
  Link curr = s->first, prev = NULL;
  while (curr != NULL && (strcmp(curr->url,str)!=0) ) {
    prev = curr;
    curr = curr->next;
    index++;
  }
  return index;
}

float compare(Set L,Set s,int index)
{
		int i;
		Link curr = L->first;
		for(i=0;i<index;i++)
		{
			curr=curr->next;
		}
		
		while(curr!=NULL)
		{
				Link check = s->first;
				while(check!=NULL)
				{
					if(strcmp(curr->url,check->url)==0)
					{
							return check->index;
					}
					check=check->next;
				}



				curr=curr->next;
		}

		return 0;
}


// nElems(Set)
// - return # elements in Set
int  nElems(Set s)
{
	assert(s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSet(Set s)
{
	Link curr;
	if (s->nelems == 0)
	{
		printf("Set is empty\n");
		abort();
	}
	else
	{
		int id = 0;
		curr = s->first;
		while (curr != NULL&&id<30) {
			printf("%s\n",curr->url);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions
static Link newNode(char *str)
{
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->url = strdup(str);
	new->pg=0;
	new->tfidf=0;
	new->index=0;
	new->order=0;
	new->num_in=0;
	new->num_out=0;
	new->next = NULL;

	return new;
}

static Link indexNode(char *str,int it)
{
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->url = strdup(str);
	new->index=it;
	new->next = NULL;

	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr->url);
	free(curr);
}

// findNode(L,Str)
// - finds where Str could be added into L
// - if already in L, curr->url == Str
// - if not already in L, curr and prev indicate where to insert
// - return urlue indicates whether Str found or not
static int findNode(Link list, char *str, Link *cur, Link *pre)
{
	Link curr = list, prev = NULL;
	while (curr != NULL && strLT(curr->url,str)) {
		prev = curr;
		curr = curr->next;
	}
	*cur = curr; *pre = prev;
	return (curr != NULL && strEQ(str,curr->url));
}

void insertDegree(Set s, int in[], int out[], double pageRank[]){
	Link curr = s->elems;
	int i=0;
	while(curr!=NULL )
	{
		curr->num_in=in[i];
		curr->num_out=out[i];
		curr->pg = pageRank[i];
		curr=curr->next;
		i++;
	}
}
void insertPg(Set s, double *pg){
	Link curr = s->elems;
	while(curr->next!=NULL )
	{
		curr=curr->next;
	}
		curr->pg= *pg;
}


void sorted (Set L, Link curr){
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->url = strdup(curr->url);
	new->pg=curr->pg;
	new->num_in=curr->num_in;
	new->num_out=curr->num_out;
	new->next = NULL;

	if (L->first==NULL)
	{
		L->elems = L->first=L->last=new;
	}
	else
	{
			Link curr = L->first;
			Link prev = NULL;
			while((new->pg <= curr->pg) && (curr->next!=NULL) )
			{
				prev = curr;
				curr = curr->next;
			}
			if(new->pg > curr->pg)
			{
					if(curr==L->first)
					{
							L->elems = L->first = new;
							new->next = curr;
					}
					else
					{
						prev->next = new;
						 new->next = curr;
					}
			}
			else
			{
				L->last->next = new;
				L->last = new;
			}

	}
			 L->nelems++;
}

Set descending(Set L){
  Set  newL =  newSet();
	Link curr;
	for (curr =L->first ; curr != NULL; curr = curr->next)
	{
		sorted(newL, curr);
	}
	return newL;
}
void tfidf_sorted (Set L, Link curr){
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->url = strdup(curr->url);
	new->tfidf=curr->tfidf;
	new->next = NULL;

	if (L->first==NULL)
	{
		L->elems = L->first=L->last=new;
	}
	else
	{
			Link curr = L->first;
			Link prev = NULL;
			while((new->tfidf <= curr->tfidf) && (curr->next!=NULL) )
			{
				prev = curr;
				curr = curr->next;
			}
			if(new->tfidf > curr->tfidf)
			{
					if(curr==L->first)
					{
							L->elems = L->first = new;
							new->next = curr;
					}
					else
					{
						prev->next = new;
						 new->next = curr;
					}
			}
			else
			{
				L->last->next = new;
				L->last = new;
			}
	}
			 L->nelems++;
}

Set descending_tfidf(Set L){
  Set  newL =  newSet();
	Link curr;
	for (curr =L->first ; curr != NULL; curr = curr->next)
	{
		tfidf_sorted(newL, curr);
	}
	return newL;
}
void urlsorted(Set L, char *str){

  Link new = newNode(str);
	if (L->first==NULL)
	{
		L->elems = L->first=L->last=new;
    L->nelems++;
	}
	else
	{
			Link curr = L->first;
			Link prev = NULL;
			while((strcmp(new->url,curr->url)>0)&& (curr->next!=NULL) )
			{
				prev = curr;
				curr = curr->next;
			}
      if(strcmp(new->url,curr->url)==0)
      {
          free(new);
          return ;
      }
			 if(strcmp(new->url,curr->url)<0)
			{
					if(curr==L->first)
					{
							L->elems = L->first = new;
							new->next = curr;
              L->nelems++;
					}
					else
					{
						 prev->next = new;
						 new->next = curr;
             L->nelems++;

					}
			}
			else
			{
  				L->last->next = new;
  				L->last = new;
         L->nelems++;
			}
	}
}



void matchingP(Set s, int arr[],int num)
{
	Link curr = s->first;
	int i=0;
	while(curr!=NULL && i<num)
	{
		curr->order=arr[i];
		i++;
		curr=curr->next;
	}

}

void orderListP(Set L,Link curr){
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->url = strdup(curr->url);
	new->order=curr->order;
	new->next = NULL;

	if (L->first==NULL)
	{
		L->elems = L->first=L->last=new;
	}
	else
	{
			Link curr = L->first;
			Link prev = NULL;
			while((new->order >= curr->order) && (curr->next!=NULL) )
			{
				prev = curr;
				curr = curr->next;
			}
			if(new->order < curr->order)
			{
					if(curr==L->first)
					{
							L->elems = L->first = new;
							new->next = curr;
					}
					else
					{
						prev->next = new;
						 new->next = curr;
					}
			}
			else
			{
				L->last->next = new;
				L->last = new;
			}
	}
			 L->nelems++;
}


Set ListP(Set L){
  Set  newL =  newSet();
	Link curr;
	for (curr =L->first ; curr != NULL; curr = curr->next)
	{
		orderListP(newL, curr);
	}
	return newL;
}

void showOrder(Set s)
{
	Link curr;
	if (s->nelems == 0)
	{
		printf("Set is empty\n");
		abort();
	}
	else
	{
		int id = 0;
		curr = s->first;
		while (curr != NULL&&id<30) {
			printf("%s %d\n",curr->url,curr->order);
			id++;
			curr = curr->next;
		}
	}
}

void showTfidf(Set s)
{
	Link curr;
	if (s->nelems == 0)
	{
		printf("Set is empty\n");
		abort();
	}
	else
	{
		int id = 0;
		curr = s->first;
		while (curr != NULL&&id<30) {
			printf("%s %.6lf\n",curr->url,curr->tfidf);
			id++;
			curr = curr->next;
		}
	}
}

void Print(FILE *outf, Set L)
{
	Link curr;
	assert(L != NULL);
	for (curr = L->first; curr != NULL; curr = curr->next)
	fprintf(outf,"%s, %d, %.7lf\n", curr->url, curr->num_out, curr->pg);
	fclose(outf);
}
