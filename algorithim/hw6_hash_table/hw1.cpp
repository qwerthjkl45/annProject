#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define SIZE 500000
#define DATA_SIZE 1000000
#define FILENAME "Data.txt"

using namespace std;

struct bucket {
	long val;
	bucket *next;
};


bucket **hashTable = new bucket*[SIZE];
bool search(long add) {
    long hashIndex = 0;
    if(add< 0)
        hashIndex = add%(SIZE/2)+250000;     
    else
        hashIndex = add%(SIZE/2);
    bucket* temp = new bucket();
    temp = hashTable[hashIndex];
    while((temp!= NULL)) {
        if((temp->val) == add) {cout<<temp->val<<endl;
            return true;}
        temp = temp->next;            
    }
    return false;
}

int main() {
    char *a = new char[20];
    for(int i = 0;i < SIZE; i++) 
        hashTable[i] = NULL;
    
    FILE *f=fopen(FILENAME,"r");
    for(long i = 1; i <= DATA_SIZE; i++) {
        a = new char[20];
        fgets(a, 20, f);
        long no = atol(a);
        long hashIndex = no%(SIZE/2);   
        if(no< 0 )
            hashIndex = (no%(SIZE/2))+250000;                  
        if(hashTable[hashIndex]== NULL) {
            hashTable[hashIndex] = new bucket();
            hashTable[hashIndex]->val = no;
        }        
        else {
            bucket* temp = new bucket();
            temp = hashTable[hashIndex]->next;
            while(temp != NULL && (temp->val!= no))
                    temp = temp->next;
	        if(temp == NULL) {
                bucket* templ = new bucket();
                templ->val = no;
                templ->next = hashTable[hashIndex];
                hashTable[hashIndex] = templ;
		    }    
            
        }
        
    }
    long ans = 0;
    
    for(long t = -10000; t<= 10000; t++) {
        for(int i = 0; i< SIZE; i++) {
            bucket* temp = new bucket();
            temp = hashTable[i];
            while(temp!= NULL) {cout<<"t "<<t<<endl;
                long add = t - (temp->val);
                if(search(add)) 
                    ans++;
                temp = temp->next;
            }  	    	    
	    
        }
    }
    cout<<"ans: "<<ans<<endl;
    return 0;

}
