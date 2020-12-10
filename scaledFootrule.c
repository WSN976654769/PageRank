#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "graph.h"
#include "set.h"
#include "list.h"

int times=0;

void swap(int arr[], int x,int y);
void resove(int arr[],int n,int num,float*,float data[],int *times);
void resove_findP(int arr[],int n,int num,int *k,int p[],int stop);
float findMin(float arr[],int sum);

int main(int argc, char *argv[]){
    int i;
    Set c = newSet();

    for(i=1;i<argc;i++)
    {
        char *ch =(char *) malloc(sizeof(char) * 100);
        char *temp =(char *) malloc(sizeof(char) * 100);

        FILE *f = fopen(argv[i],"r");

        if(f==NULL)
        {
            fprintf(stderr, "Error! cannot open the file.\n");
            exit(0);
        }

        while(fscanf(f,"%s",temp)==1)
        {
            //printf("%s\n",temp);
            urlsorted(c, temp);
            //insertInto(urlL,temp);
        }
        fclose(f);
    }

  //  printf("==============================================\n");

  //  showSet(c);

    int num = nElems(c);
  //  printf("--%d\n",num);

    int *arr = (int *)malloc(sizeof(int)*num);
    for(i=0;i<num;i++)
    {
      arr[i]=i+1;
    //  printf("%d\n",arr[i]);
    }
    int s=1;
    for(i=1;i<=num;i++)
    {
      s=s*i;
      //printf("%d\n",s);
    }
    //int sum = s*(argc-1);
    int sum = s;
  //  printf("%d\n",sum);

  //  printf("==============================================\n");

    float *data = (float *)malloc(sizeof(float)*sum);
    int *p = (int *)malloc(sizeof(int)*num);
  //  printf("##%d\n",num);



    Set loopList;
    for(i=1;i<argc;i++)
    {
        char *ch =(char *) malloc(sizeof(char) * 100);
        char *temp =(char *) malloc(sizeof(char) * 100);

        FILE *f = fopen(argv[i],"r");

        if(f==NULL)
        {
            fprintf(stderr, "Error! cannot open the file.\n");
            exit(0);
        }
        float k=0;



        Set t = newSet();
        while(fscanf(f,"%s",temp)==1)
        {
            k++;

            //printf("%s\n",temp);
            insertIndex(t,temp,k);
        }

        process(t,k);
      //  showSet(t);
      //  printf(".....\n");
         int times=0;
         float *posVal = malloc(num*sizeof(float));
         int j;
         for (j=0; j < num; j++) {
           posVal[j] = compare(c, t, j);
         }
         resove(arr,0,num,posVal,data,&times);
         free(posVal);
         fclose(f);
    }

    // for(i=0;i<sum;i++)
    // printf("[%d] %f\n",i,data[i]);

//    printf("%d\n",times);

    //float v = findMin(data,sum);

    float min=data[0];
    int find;
    for(i=0;i<sum;i++)
    {
      if(min>data[i])
      {
          min=data[i];
          find=i;
      }
    }
  //  printf("====%f====%d\n",min,find);

    int times=0;
    resove_findP(arr,0,num,&times,p,find);

    // for(i=0;i<num;i++)
    // {
    //   printf("%d\n",p[i]);
    // }

    matchingP(c,p,num);
  //  showOrder(c);
    Set P = ListP(c);
    printf("%.6f\n",min);
    showSet(P);


  return 0;
}

void swap(int arr[], int x,int y)
{
    int temp=arr[x];
    arr[x]=arr[y];
    arr[y]=temp;
}
void resove(int arr[],int n,int num, float *posVal,float data[],int *times )
{

        int i;
        for(i=n;i<num;i++)
        {
            swap(arr,n,i);
            resove(arr,n+1,num,posVal,data,times);
            swap(arr,n,i);
        }

        if(n==num)
        {
            float total=0;
            for(i=0;i<num;i++)
            {

                float base = num;
                float value2 = arr[i]/base;
              //  printf("%d/%d==",arr[i],num);

              //  printf(".%f ",value2);

                float value1 = posVal[i];
              //  printf("==%f\n",value1);

                float sf;
                if(value2==0 || value1==0)
                      sf=0;
                else
                  sf = fabs(value1-value2);

            //   printf("--%f\n",sf);
                total+=sf;

            }
          // printf("****%f****\n",total);

            data[*times]+=total;  //7
          // printf("%d\n",*times);
            (*times)++;   //8

          //  printf("ok\n");
        }

}
void resove_findP(int arr[],int n,int num,int *k,int p[],int stop)
{

        int i;
        for(i=n;i<num;i++)
        {
            swap(arr,n,i);
            resove_findP(arr,n+1,num,k,p,stop);
            times++;
            swap(arr,n,i);
        }
        if(n==num)
        {
            for(i=0;i<num;i++)
            {
                //printf("%d ",arr[i]);
                if(*k==22)
                {
                  p[i]=arr[i];
                }
            }
            //printf("\n");
            //printf("%d\n",*k);
            (*k)++;
        }
}


float findMin(float arr[],int sum){
  int i;
  float min=arr[0];
  int x;
  for(i=0;i<sum;i++)
  {
    if(min>arr[i])
    {
        min=arr[i];
    }
  }


return min;

}
