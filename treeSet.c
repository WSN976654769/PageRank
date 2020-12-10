// Linked treeSet implementation ... COMP2521
//from wk 5 exercie 5a
#include "treeSet.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char * strdup(const char *__s);

treeSet creatNode(char *n) {
  treeSet new = malloc(sizeof(set));
  assert(new != NULL);
  new->url = strdup(n);
  new->next = NULL;
  return new;
}


treeTable makeTable(){
    treeTable new= malloc(sizeof(setRep));
    assert(new != NULL);
  	new->nelems = 0;
  	new->elems = NULL;
  	new->first = NULL;
  	new->last = NULL;
  	return new;
}

void insertSorted (treeTable L, char *str){

  treeSet  new = creatNode(str);
	if (L->first==NULL)
	{
		L->elems = L->first=L->last=new;
    L->nelems++;
	}
	else
	{
			treeSet curr = L->first;
			treeSet prev = NULL;
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

void show(treeTable s)
{
	treeSet curr;
	if (s->nelems == 0)
		printf("Set is empty\n");
	else
  {
		//printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->first;
		while (curr != NULL)
    {
  			printf("%s ",curr->url);
  			id++;
  			curr = curr->next;
		}
    printf("\n");
	}
}
void showP(FILE * outf,treeTable s)
{
	treeSet curr;
	if (s->nelems == 0)
		fprintf(outf,"Set is empty\n");
	else
  {
		//printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->first;
		while (curr != NULL)
    {
  			//printf("%s ",curr->url);
        fprintf(outf,"%s ",curr->url);
  			id++;
  			curr = curr->next;
		}
    printf("\n");
	}
}
