#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "set.h"
#include "tree.h"

static char *trim(char *s);
void NormalizeWord(char* word);

int main (int argc, char *argv[]){

    FILE *f = fopen("collection.txt","r");

    char *n =(char *) malloc(sizeof(char) * 100);

    if(f==NULL)
    {
        fprintf(stderr, "Error! cannot open the file.\n");
        exit(0);
    }

    double nV=0;
    while(fscanf(f,"%s",n)==1) nV++;
    fclose(f);

  //  printf("=================================================================\n");

    FILE *f1 = fopen("Part2.txt","r");

    if(f1==NULL)
    {
        fprintf(stderr, "Error! cannot open the file.\n");
        exit(0);
    }
    char *str =(char *) malloc(sizeof(char) * 100);
    char *temp =(char *) malloc(sizeof(char) * 100);
    char *text =(char *) malloc(sizeof(char) * 100);
    char *word =(char *) malloc(sizeof(char) * 100);
    int k=1;
    int count=0;

    Set urlList = newSet();
    Set compare = newSet();

    double * idfv = (double *)malloc(sizeof(double)*argc);
    while(fgets(str,10000,f1)!=NULL)
    {
        sscanf(str,"%s",word);

        for(k=1;k<argc;k++)
        {
            if(strcmp(word,argv[k])==0)
            {

                //  printf("\n%s",str);
                //  printf("##%s\n",word);
                  if(count!=0)
                  {
                      char *copy =trim(str);
                      char *web;
                      int hasdoc=0;
                       for(web=strsep(&copy," ");copy!=NULL;web=strsep(&copy," "))
                       {
                            if(strstr(web,"url"))
                            {
                                //  printf("--%s\n",web);
                                  if(check(compare,web))
                                  {
                                     insertInto(urlList,web);
                                  }
                                  hasdoc++;
                            }
                        }
                      //  printf("%d Ddoucments have\n",hasdoc);
                        double x = nV/hasdoc;
                        double idf = log10(x);
                      //  printf("%lf\n",idf);
                        idfv[k]=idf;
                    }
                    if(count==0)
                    {
                        char *copy =trim(str);
                        char *web;
                        int hasdoc=0;
                         for(web=strsep(&copy," ");copy!=NULL;web=strsep(&copy," "))
                         {
                              if(strstr(web,"url"))
                              {
                                      //1s
                                //    printf("--%s\n",web);
                                    if(argc==2)
                                        insertInto(urlList,web);
                                    else
                                        insertInto(compare,web);

                                    hasdoc++;
                              }
                          }
                          //   printf("%d Ddoucments have\n",hasdoc);
                             double x = nV/hasdoc;
                             double idf = log10(x);
                          //   printf("idf is %.6lf\n",idf);
                             idfv[k]=idf;
                     }
                 count++;
            }
        }
    }

    fclose(f1);
  //  printf("====================================================\n");
    disposeSet(compare);
  //  printf("the list should be \n");
    Duplicate(urlList);
  //  showSet(urlList);
  //  printf("====================================================\n");

    Link curr=urlList->first;
    while(curr!=NULL)
    {
      //  printf("\n======%s======\n",curr->url);

        sprintf(text,"%s.txt",curr->url);
        FILE *ff= fopen(text,"r");

           double nword=0;
           while(fscanf(ff,"%s",text)==1 )
           {
             if(strcmp(text,"Section-2")==0) break;
           }

           int frequency=0;
           int *index = (int *)malloc(sizeof(int)*argc);
           memset(index,0,sizeof(int)*argc);
           while(fscanf(ff,"%s",text)==1)
           {
               if(strcmp(text,"#end")==0) break;
               NormalizeWord(text);

               for(k=1;k<argc;k++)
               {
                   if(strcmp(text,argv[k])==0)
                   {
                     frequency++;
                     index[k]+=1;
                //   printf("%s\n",text);
                //     printf("%d %d\n",index[k],k);
                   }
                }
               nword++;
           }

        //   printf("\n+++++++++++++++++++++++++++++++++\n");
        //   printf("[the number of words are %.2lf]\n",nword);

           double total = 0;
           for(k=1;k<argc;k++)
           {

          //   printf("\n");

        //     printf("%s : %d \n",argv[k],index[k]);
        //     printf("idf is %lf \n",idfv[k]);
             double tf = index[k]/nword;
        //     printf("tf is %lf\n",tf);

             double tfidf = tf * idfv[k];
          //   printf("==%s  %.6lf==\n",curr->url,tfidf);

             total += tfidf;
           }

           //printf("%s  %.6lf\n",curr->url,total);
           curr->tfidf = total;

      //      printf("++++++++++++++++++++++++++++++++++\n");

        fclose(ff);
        curr=curr->next;
    }
  //  printf("\n\n");
  //showTfidf(urlList);
  //printf("\n\n");
  Set ordered_List =descending_tfidf(urlList);
  disposeSet(urlList);
  showTfidf(ordered_List);
  //sshowTfidf(urlList);
return 0;
}


static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n')
      s[end] = '\0';
	return s;
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
    word[strlen(word)-1]='\0';
  }
}
