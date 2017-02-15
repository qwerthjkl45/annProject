#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define SIZE 12345

using namespace std;

struct bucket
{
       long n;
       bucket *next;
};

int main(int argc, char *argv[])
{
    char *a=new char[10];
    bucket **hash=new bucket*[SIZE];
    FILE *f=fopen("DataTest.txt","r");
    for(long i=0; i<SIZE; hash[i++]=NULL);
	cout<<"reached here"<<endl;
    for(long i=1; i<=500000; i++)
    {
             a=new char[10];
             fgets(a,10,f);
             long no=atol(a);
             long hash_val=no%SIZE;
             if(hash[hash_val]==NULL)
             {
                 hash[hash_val]=new bucket;
                 hash[hash_val]->n=no;
             }
             else
             {
                 bucket *temp=hash[hash_val];
                 while(temp!=NULL && temp->n!=no) temp=temp->next;
                 if(temp==NULL)
                 {
                     bucket *newhd=new bucket;
                     newhd->n=no;
                     newhd->next=hash[hash_val];
                     hash[hash_val]=newhd;
                 }
             }
    }
    cout<<"Reached here 1"<<endl;;
    fclose(f);
   long ans=0;
    for(int t=2500; t<=4000; t++)
            for(long i=0; i<SIZE; i++)
            {
                     bucket *temp=hash[i];
                     while(temp!=NULL)
                     {
                             long n1=temp->n;
                             if(n1!=i/2)
                             {
                                        long n2=t-n1;
										cout<<"n2 size "<<n2%SIZE<<endl;
                                        bucket *temp2=hash[n2%SIZE];
                                        while(temp2!=NULL && temp2->n!=n2) temp2=temp2->next;
                                        if(temp2!=NULL)
                                        {
                                                ans++;
                                                i=SIZE+1;
                                                break;
                                        }
                             }
							temp = temp->next;
                     }
            }
    cout<<"Total number of target values: "<<ans;
    //system("PAUSE");
    return EXIT_SUCCESS;
}

