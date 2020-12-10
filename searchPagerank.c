#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "tree.h"


static char *trim(char *s);
int main (int argc, char *argv[]){

    //printf("=================================================================\n");

    FILE *f1 = fopen("Part2.txt","r");

    if(f1==NULL)
    {
        fprintf(stderr, "Error! cannot open the file.\n");
        exit(0);
    }
    char *str =(char *) malloc(sizeof(char) * 100);
    char *temp =(char *) malloc(sizeof(char) * 100);
    //char *q =(char *) malloc(sizeof(char) * 100);


    int k=1;
    int count=0;

    Set urlList = newSet();
    Set compare = newSet();

    //printf("++++++%d\n",argc);

    while(fgets(str,10000,f1)!=NULL)
    {
        sscanf(str,"%s",temp);
        for(k=1;k<argc;k++)
        {

            if(strcmp(temp,argv[k])==0)
            {
                //printf("%s",str);
                if(count!=0)
                {
                    char *copy =trim(str);
                    char *web;
                     for(web=strsep(&copy," ");copy!=NULL;web=strsep(&copy," "))
                     {
                          if(strstr(web,"url"))
                          {
                                //printf("--%s\n",web);
                                if(check(compare,web))
                                {
                                    //printf("ok\n");
                                   insertInto(urlList,web);
                                }
                          }
                      }
                }
                if(count==0)
                {
                    char *copy =trim(str);
                    char *web;
                     for(web=strsep(&copy," ");copy!=NULL;web=strsep(&copy," "))
                     {
                          if(strstr(web,"url"))
                          {
                                //printf("==%s\n",web);
                                if(argc==2)
                                insertInto(urlList,web);
                                else
                                insertInto(compare,web);
                          }
                      }
                }
                 count++;
            }
        }
    }

    //printf("find it %d\n",count);
    fclose(f1);
  //  printf("====================================================\n");
    disposeSet(compare);
    Duplicate(urlList);
  //  showSet(urlList);
  //  printf("====================================================\n");
    FILE *f2 = fopen("Part1.txt","r");

    char *url =(char *) malloc(sizeof(char) * 100);
    char *ch =(char *) malloc(sizeof(char) * 100);
    double *pg =(double *) malloc(sizeof(double) * 100);

    if(f2==NULL)
    {
        fprintf(stderr, "Error! cannot open the file.\n");
        exit(0);
    }

    while(fgets(ch,10000,f2)!=NULL )
    {
          ch = trim(ch);
          //printf("%s\n",ch);
          url=strsep(&ch,",");
        //  printf("%s\n",url);

          strsep(&ch,",");
          *pg= atof(ch);
        //  printf("%.7lf\n",*pg);

      //    printf("\n");
          Link curr=urlList->first;
          while(curr!=NULL)
          {

            // printf("####%.7lf\n",*pg);
            // printf("---%s\n",url);
            // printf("===%s\n",curr->url);
            if(strcmp(curr->url,url)==0)
            {
              curr->pg=*pg;
              break;
            }
            curr=curr->next;
          }
    }
      fclose(f2);
    //  printf("====================================================\n");
     //showSet(urlList);
    Set ordered_List =descending(urlList);
    disposeSet(urlList);

    showSet(ordered_List);

return 0;
}


static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n')
      s[end] = '\0';
	return s;
}
