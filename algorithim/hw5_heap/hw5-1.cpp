#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>
#include <unistd.h>
using namespace std;
#define SIZE 200
#define ROOT 1

struct edge {
	int head;
	long dist;
	edge* next;
	bool visit ;
	long prev_dist;
};

struct Data {
	long distance;
	int index;
	
};
struct Data datas[SIZE+1];
struct Data *q;
edge* g[SIZE+1];

int prev_edge[SIZE+1];


void swap(int child, int parent, Data* tree)
{
	Data temp = tree[child];
	tree[child] = tree[parent];
	tree[parent] = temp;
}

void heapify(Data* tree, int root_index, int leave_index) {

	int parent = 0;
	int key = 0;
	for(int i = root_index; i <= leave_index; i++) {
		key = tree[i].distance;
		parent = tree[i/2].distance;
		int j = i;
		while(key < parent) {
			swap(j, j/2, tree);
			j = j/2;
			key = tree[j].distance;
			parent = tree[j/2].distance;
		}
		
	}
}


int total_size = SIZE+1;
void insert_array(Data* queue, int size) {
		
	q = (Data*)malloc(sizeof(Data)*(size));
	memcpy(q, queue, size*(sizeof(Data)));
	heapify(q, 1, size-1);
}

void insert_array_(Data* queue, int size) {
		
	q = (Data*)realloc(q, (sizeof(Data))*(size));
	memcpy(q, queue, size*(sizeof(Data)));
	heapify(q, 1, size-1);
}

void insert_index(int num) {
	q = (Data*)realloc(q, (sizeof(Data))*(total_size+1));
	q[total_size].distance = num;
	q[total_size].index = total_size;
	
	heapify(q, 1, total_size);
	total_size += 1;
}

void extract_min(int root, int length)
{
	int minNode = -1;
	int left_child_index = root*2;
	int right_child_index = root*2 +1;

	if((left_child_index < length) && q[left_child_index].distance< q[root].distance )
		minNode = left_child_index;
	else minNode =root;
	if((right_child_index < length) && (q[right_child_index].distance < q[root].distance) && 
		(q[right_child_index].distance < q[left_child_index].distance))
		minNode = right_child_index;
	
	if(minNode != root) {
		swap(minNode, root, q);
		extract_min(minNode, length);	
	}
	
	extract_min(left_child_index, length);	
	extract_min(right_child_index, length);
	
}

int main() {
	//length[1]->index = 2;
	for(int i =1; i<= SIZE; i++) {
		g[i] = NULL;
		//g[i]->visit = false;
		datas[i].index = i;
		datas[i].distance = 10000000;
		prev_edge[i] = 0;		
	}
	datas[1].distance = 0;
	

		
	char* a = new char[400];	
	FILE* f = fopen("Data.txt", "r");
	while(fgets(a, 400, f)) {
		int n1 = atoi(a);
		while(a[0]!= '\t') a++;
		a++;
		while(true)	{
			int n2 = atoi(a);
			while(a[0]!= ',') a++;
			a++;
			int n3 = atoi(a);
			edge* newedge = new edge;
			newedge->head = n2;
			newedge->dist =n3;
			newedge->next = g[n1];	
			g[n1] = newedge;
			g[n1]->visit = false;
			g[n1]->prev_dist = 1000000;
			while(a[0]!='\t' && strlen(a)>=3) a++;
            if(strlen(a)<3) break;
            a++;	
		}
		a = new char[400];
	}

	
	

	insert_array(datas, SIZE+1);
	int actual_q_size = SIZE;
	while(actual_q_size > 0) {
		int node_index = q[ROOT].index;		
		edge* temp = g[node_index];				
		g[node_index]->visit = true;
		while(temp!= NULL) {
			long alt_dist = temp->dist + q[ROOT].distance;		  
			if(alt_dist < g[temp->head]->prev_dist) {
				g[temp->head]->prev_dist = alt_dist;
			}	
			temp = temp->next;		
		}
		g[node_index]->dist =  q[ROOT].distance;		
		int i = 1;
		int j = 1;
		while(j <= SIZE ) {
			if(!(g[j]->visit)) {
				q[i].index = j;
				q[i].distance = g[j]->prev_dist;
				i++;			
			}	
			j++;	
		}
		
		actual_q_size--;	
		insert_array_(q, i);
		
	}
		
	printf("%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n\n", g[7]->dist, g[37]->dist, g[59]->dist, g[82]->dist, g[99]->dist, g[115]->dist, g[133]->dist, g[165]->dist, g[188]->dist, g[197]->dist );

	
	
	
}
