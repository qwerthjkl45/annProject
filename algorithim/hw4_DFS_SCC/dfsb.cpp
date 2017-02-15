#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>
#define SIZE 875714
#define FILENAME "SCC.txt"

using namespace std;

struct edge
{
       long head;
       edge* next;
};

edge* g[SIZE+1];
bool visited[SIZE+1];
long t[SIZE+1];
long curr_time=0;
static long sccs[6];

void insert(long size)
{
     for(int i=1; i<6; i++)
         if(sccs[i]<size)
         {
                 for(int j=5; j>i; j--)sccs[j]=sccs[j-1];
                 sccs[i]=size;
                 break;
         }
}

long DFS(long i, long size)
{
     visited[i]=true;
     size++;
     edge *temp=g[i];
     while(temp!=NULL)
     {
         if(!(visited[temp->head])) size=DFS(temp->head, size);
         temp=temp->next;
     }
     return size;
}

void DFSloop()
{
     for(int k=1; k<=5; sccs[k++]=0);
     long size=0;
     for(long i=1; i<=SIZE; i++)
     {
             size=0;
             if(!(visited[t[i]]))
             {
		if(i == 1)
			cout<<"number"<<t[i]<<"   "<<g[1]->head<<endl;
                 size=DFS(t[i], 0);
                 insert(size);
             }
     }
}

int main(int argc, char *argv[])
{
    FILE *fp=fopen("times1.txt","r");
    char *a=new char[20];
    long p=0;
    while(fgets(a,20,fp)) t[++p]=atol(a);
    fclose(fp);
    FILE *f=fopen(FILENAME,"r");
    for(int i=1; i<=SIZE; i++)
    {
            g[i]=NULL;
            visited[i]=false;
    }
    a=new char[20];
    while(fgets(a,20,f))
    {
            long n1, n2;
            n1=atol(a);
            while(a[0]!=' ') a++;
            n2=atol(++a);
            edge *newedge=new edge;
            newedge->head=n2;
            newedge->next=g[n1];
            g[n1]=newedge;
            a=new char[20];
    }
    fclose(f);
    DFSloop();
    cout<<"SCCs: ";
    for(int k=1; k<6; k++) cout<<sccs[k]<<",";
    cout<<"\n";
    system("PAUSE");
    return EXIT_SUCCESS;
}
