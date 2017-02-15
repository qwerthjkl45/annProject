#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>
#define SIZE 875714
#define SIZE_NODE 875714
#define FILENAME "SCC.txt"
#define OUTPUTFILE "123.txt"
using namespace std;

struct edge
{
       long head;
       edge* next;
};



edge* g[SIZE+1];
long f[SIZE+1] = {0};
bool visited[SIZE+1];
long t =0;
bool secondLoop = false;
static long sccs[6]= {0};
long leader[SIZE+1] = {0};
int SCC_index = 0;
int SCC_min_index = 0;
int test[5]= {1, 2, 5,3, 4};
bool second_run = false;

void rankSCC(long count)
{	
	 for(int i=1; i<6; i++)
         if(sccs[i]<count)
         {
                 for(int j=5; j>i; j--)sccs[j]=sccs[j-1];
                 sccs[i]=count;
                 break;
         }
}

long DFS(long i, long size)
{
    //printf("%d", i);
    size++;
	visited[i] = true;
	edge* temp = g[i];
	while(temp!= NULL)
	{
		if(!visited[temp->head])
			size =DFS(temp->head, size);
		temp = temp->next;
	}
	/*if(!second_run)
	{	f[SIZE_NODE-t] = i;
		t++;
	}*/
	t++;
	f[i] = t;
		//f[i] = t;
    return size;
}

void DFSloop()
{
	long size=0;
	for(long i = SIZE_NODE; i>0; i--)
	{
		size = 0;
		if(!visited[i]) {
			size = DFS(i, 0);
		}
        rankSCC(size);
		size = 0;
	}
	
}

void DFSsecondlOOP()
{
	for(int k=1; k<=5; sccs[k++]=0);
    long size=0;
	for(long i = 1; i <= SIZE_NODE; i++)
	{
		size = 0;
		if(!visited[f[i]]) {
			size =DFS(f[i], 0);
		}
        rankSCC(size);
	}
	
}




int main()
{
	second_run = false; 
	FILE* fin = fopen(FILENAME, "r");
	for(int i = 1; i <=SIZE; i++)
	{
		visited[i] = false;
		g[i] = NULL;
	}
	char *a = new char[20];
	while(fgets(a, 20, fin))
	{
		long n1, n2;
		n2= atol(a);
		edge *newedge = new edge;
		while(a[0]!=' ') a++;
            	n1=atol(++a);
		newedge->head = n2;
		newedge->next = g[n1];
		
		g[n1] = newedge;
		a = new char[20];
				
	}
	
	DFSloop();
	cout<<"finifsh loop"<<f[4]<<endl;
	FILE* fout = fopen(OUTPUTFILE, "r");
	
	for(long i = SIZE_NODE; i >0; i--)
	{
		edge* temp = new edge;
		temp = g[i];	
		while(temp!= NULL) {
			//long index = temp->head;
			//sprintf(a,"%lu %lu\n",f[index] , f[i]);
			//a = new char[20];
			temp = temp->next;
		}
	}
	fclose(fout);
	/*
    fin = fopen("f2.txt", "r");
	for(int i = 1; i <=SIZE; i++)
	{
		visited[i] = false;
		g[i] = NULL;
	}
	
	while(fgets(a,20,fin))
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

	fclose(fin);
	cout<<"test"<<endl;
    second_run = true;
    //DFSsecondlOOP();
	DFSloop();
    cout<<"finish secone loop"<<endl;
	
	for(int i = 1; i < 6; i++)
		printf("%lu ", sccs[i]);
	*/	
	return 0;
}

