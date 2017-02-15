#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>
#include <unistd.h>
#define SIZE 200

using namespace std;

struct edge
{
       std::string n2;
       edge *next;
};

struct node
{
       std::string n1;
       node* down;
       edge* first;
}*head;

void getCompEdge(int m, std::string *n1, std::string *n2)
{
     int r=rand()%m;
     if(r==0) r=1;
     node *th=head;//1
     edge *te=th->first;//192
     while(th!=NULL && r>1)
     {
            //cout<<r+"   "+th->n1<<"  "<<te->n2<<endl;
            //usleep(200000);
            while(r>1 && te!=NULL)
               {
                         //cout<<"while "<<te->n2+"  "+te->next->n2<<endl;
                         r--;
                         te=te->next;

               }
               if(te==NULL) {th=th->down; te=th->first;}
     }
	*n1=th->n1; *n2=te->n2; 
}

int kargers(int m)
{
	for(int l=1; l<=SIZE-2; l++)
    {
            std::string comp_node1, comp_node2;
            getCompEdge(m, &comp_node1, &comp_node2);
            //cout<<comp_node1+"  "+comp_node2+" "+head->n1<<endl;
            //usleep(2000000);
            node *newnode=new node;
            newnode->down=head;
            newnode->first=NULL;
            newnode->n1=comp_node1+","+comp_node2;
            head=newnode;
            /*remove first node*/
            node *b4first=head, *fnode=head;
            while(fnode->n1!=comp_node1) {b4first=fnode; fnode=fnode->down;}
            b4first->down=fnode->down;
            /*remove second node*/
            node *b4second=head, *snode=head;
            while(snode->n1!=comp_node2) {b4second=snode; snode=snode->down;}
            b4second->down=snode->down;
            /*merge edges of the two nodes*/
            edge *tedge=fnode->first;
            while(tedge!=NULL)
            {
                 if(tedge->n2==comp_node2) { m--; tedge=tedge->next;}
                 else
                 {
                      edge *newedge=new edge;
                 newedge->n2=tedge->n2;
                 newedge->next=newnode->first;
                 newnode->first=newedge;
                 node *tnode=head;
                 while(tnode->n1!=tedge->n2) tnode=tnode->down;
                 edge *ttedge1=tnode->first;
                 while(ttedge1->n2!=comp_node1) ttedge1=ttedge1->next;
                 ttedge1->n2=newnode->n1;
                 tedge=tedge->next;
                 }
            }
            tedge=snode->first;
            while(tedge!=NULL)
            {
                 if(tedge->n2==comp_node1) { m--; tedge=tedge->next; }
                 else
                 {
                      edge *newedge=new edge;
                 newedge->n2=tedge->n2;
                 newedge->next=newnode->first;
                 newnode->first=newedge;
                 node *tnode=head;
                 while(tnode->n1!=tedge->n2) tnode=tnode->down;
                 edge *ttedge1=tnode->first;
                 while(ttedge1->n2!=comp_node2) ttedge1=ttedge1->next;
                 ttedge1->n2=newnode->n1;
                 tedge=tedge->next;
                 }
            }
    }
    int min_cut=0;
    edge *hd=head->first;
    while(hd!=NULL)
    {
                            min_cut++;
                            hd=hd->next;
    }
    return min_cut;
}

int main(int argc, char *argv[])
{
    int min=200;
	for(long h=1; h<=280000; h++)
    {
    srand(h);
    FILE *f=fopen("input.txt","r");
    int m=0;
	for(int i=1; i<=SIZE; i++)
    {
            char *a=new char[200];
            fgets(a,200,f);
            node *newnode=new node;
            std::stringstream sout;
            sout << i;
            newnode->n1=sout.str();
            newnode->down=NULL;
            newnode->first=NULL;
            if(head==NULL) head=newnode;
            else
            {
                node *temp=head;
                while(temp->down!=NULL) temp=temp->down;
                temp->down=newnode;
                //if(head->down!= NULL)
                    //cout<<"head"<<head->down->n1<<endl;
            }
            while(*a!='\t') a++;
            a++;
            while(true)
            {

                    int tn=atoi(a);
                    //printf("%d ", tn);
                    if(tn<1) break;
                    m++;
                    std::stringstream sout;
                    sout << tn;
                    edge *newedge=new edge;
                    newedge->n2=sout.str();
                    edge *temp=newnode->first;
                    newnode->first=newedge;
                    newedge->next=temp;
                    //if(m>60)
                        //cout<<" "+head->down->down->n1<<endl;
                        //cout<<"after "+newnode->n1+","+newnode->first->n2+","+newedge->next->next->n2<<endl;

                    for(; (a[0]!='\t' && a[0]!='\n'); a=a+1);
                    a=a+1;
            }
            //printf("\n");
            //usleep(2000000);
    }
    fclose(f);
    int thistime=kargers(m);
    if(thistime<min)
    {
        min=thistime;
        cout<<"\nMin-Cut: "<<thistime<<endl;
    }
    head=NULL;
    }
    cout<<"\n\nFinal min: "<<min;
    system("PAUSE");
    return EXIT_SUCCESS;
}
