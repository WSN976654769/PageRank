#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "set.h"
#include <string.h>


typedef struct Node *List;
typedef struct GraphRep *Graph;

typedef struct node *Link;
typedef struct SetRep *Set;

int main (int argc, char *argv[]){
    if (argc!=4)
    {
        fprintf(stderr, "Please input three arguments\n");
        abort();
    }

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIteration = atoi(argv[3]);
    printf("%lf %lf %d\n",d,diffPR,maxIteration);

    FILE *f = fopen("collection.txt","r");
    char *ch =(char *) malloc(sizeof(char) * 100);

    if(f==NULL)
    {
        fprintf(stderr, "Error! cannot open the file.\n");
        exit(0);
    }

    int nV=0;
    Set urlL = newSet();
    while(fscanf(f,"%s",ch)==1)
    {
        insertInto(urlL, ch);
        nV++;
    }
    fclose(f);

    Graph graphIn = newGraph(nV);
    Graph graphOut = newGraph(nV);

    int *in = (int *)malloc(sizeof(int)*nV);
    memset(in,0,sizeof(int)*nV);
    int *out = (int *)malloc(sizeof(int)*nV);
    memset(out,0,sizeof(int)*nV);

    char *temp = (char *) malloc(sizeof(char) * 100);
    char *url = (char *) malloc(sizeof(char) * 100);
    FILE *f2 = fopen("collection.txt","r");
    nV=0;
    int count;
    while(fscanf(f2,"%s",ch)==1)
    {
        sprintf(temp,"%s.txt",ch);
        FILE *ff= fopen(temp,"r");
        count = 0;
        while(fscanf(ff,"%s",temp)==1)
        {
            if(strstr(temp,"url"))
            {
                url=strstr(temp,"url");
                if(strcmp(url,ch)!=0)
                {
                    int index= whereIsElem(urlL, url);
                    in[index]=in[index]+1;//
                    Edge e1 = mkEdge(graphOut,nV,index);
                    Edge e2 = mkEdge(graphIn,index,nV);
                    insertEdge(graphOut,e1);
                    insertEdge(graphIn,e2);
                    count++;
                    out[nV]=count;
                }
            }
        }
        nV++;
        fclose(ff);
    }
    free(ch);
    free(temp);
    fclose(f2);

    printf("\n");

    //showGraph(graphOut);
    //showGraph(graphIn);
    //double prev_pg;
    double *pg = (double *)malloc(sizeof(double)*nV);
    double *pgRank = (double *)malloc(sizeof(double)*nV);
    double n = nV;

    int order;
    for(order=0;order<nV;order++)
    {
      pg[order]=1/n;
      pgRank[order]=1/n;
    }

    int iteration = 0;
  	   // to enter the following loop
    double diff= diffPR;///
    double diff_sum = 0;
    double diff_each=0;
    int i;
    while(iteration < maxIteration && diff >= diffPR)
    {
        diff_sum=0;
        iteration++;

        for(i=0;i<nV;i++) pg[i]=pgRank[i];

        for(order=0;order<nV;order++)
        {
            printf("==================================================================\n");
            double i = in[order];
            double o= out[order];
            if(o==0) o = 0.5;

            List in_list = connection(graphIn,order);

            //double total=0;
            double sum =  0;

            while(in_list!=NULL)
            {
              //  printf("ok\n");
                int ret=in_list->v;
              //  printf("order %d, ==%f\n",ret,pg[ret]);
                List  small = connection(graphOut,ret);
                double x ,y;
                double count1=0;
                double count2=0;


                while(small!=NULL)
                {
                    int sv = small->v;
                    x = in[sv];
                    count1 = count1 +x;
                    y = out[sv];
                    if(y==0) y=0.5;
                    count2 = count2 + y;

                    small = small->next;
                }
                double Win = i/count1;
                printf("[%d][%d]=====%.7lf\n",ret,order,Win);
                double Wout = o/count2;
                printf("[%d][%d]=====%.7lf\n",ret,order,Wout);
                sum += Win * Wout * pg[ret];
                in_list=in_list->next;
            }
            printf("\n");
            pgRank[order] =(1-d)/n + d * sum; //1
            printf("prev pgRank is %.7lf\n",pg[order]);
            printf("new pgRank for %d is %.7lf\n",order,pgRank[order]);
            diff_each = pgRank[order] - pg[order];
            if(diff_each<0) diff_each = -diff_each;

            printf("--%f\n",diff_each);
            diff_sum += diff_each;
        }
        diff = diff_sum;
        printf("\n[%d]\n",iteration);
        printf("%f\n",diff);
    }
      insertDegree(urlL, in, out, pgRank);
      printf("\n");
      showSet(urlL);

      printf("\n");
      Set ordered_List = descending(urlL);
      printf("ok\n");
      disposeSet(urlL);
      showSet(ordered_List);
      printf("ok\n\n");

      FILE *fw = fopen("Part1.txt","w");
      Print(fw, ordered_List);

     return 0;
}
