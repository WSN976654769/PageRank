#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include <string.h>
#include "treeSet.h" // url list in tree
//#include "set.h" // url list

typedef struct set *treeSet;
typedef struct treeNode *Tree;

void NormalizeWord(char* word);
int main (void){

  char *ch =(char *) malloc(sizeof(char) * 100);
  char *temp = (char *) malloc(sizeof(char) * 100);
  char *text = (char *) malloc(sizeof(char) * 100);
  Tree t = newTree();
  FILE *f = fopen("collection.txt","r");
  if(f==NULL)
  {
      fprintf(stderr, "Error! cannot open the file.\n");
      exit(0);
  }
  int count=0;
  while(fscanf(f,"%s",ch)==1)
  {
      sprintf(temp,"%s.txt",ch);
      printf("---%s\n",ch);
      printf("=======\n");
      FILE *ff= fopen(temp,"r");
      /////ch!!!!!
      int i=0;
      while(fscanf(ff,"%s",temp)==1)
      {
          if(strcmp(temp,"Section-2")==0)
          {
            break;
          }
      }

      while(fscanf(ff,"%s",text)==1)
      {
          if(strcmp(text,"#end")==0) break;
          NormalizeWord(text);
          printf("%d. %s  [%s]\n",i,text,ch);
          t = TreeInsert(t, text,ch);
          i++;
      }
      printf("== The number of words are %d ==\n",i);
      count++;
  }

      printf("== The number of document are %d ==\n",count);
      printf("--------------------------------------\n");

      showTree(t);
      fclose(f);
      FILE *fw = fopen("Part2.txt","w");
      printTree(fw, t);
  //
  // printf("\n");
  //

return 0;
}

void NormalizeWord(char* word)
{
  int i = 0;
  while (word[i])
  {
    if (word[i] < 91 && word[i] > 64)
      word[i] += 32;
    i++;
  }
  if(word[strlen(word)-1]=='.'|| word[strlen(word)-1]=='?'|| word[strlen(word)-1]==';'|| word[strlen(word)-1]==',')
  {
  //  printf("===========ok\n");
    word[strlen(word)-1]='\0';
  }
}
