#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>


using namespace std;	
#define TOTAL_NUM 27
#define ROOT 1
int test[27] = {6399, 2597, 2909, 2437, 8700, 7896, 2367, 4612, 46647, 508, 1724, 7420, 9146, 2183, 9047, 7905, 6461, 1913, 546, 4122, 647, 2069, 8021, 648, 2620, 8164, 982};
int *q;


void swap(int child, int parent, int* tree)
{
	int temp = tree[child];
	tree[child] = tree[parent];
	tree[parent] = temp;
}

void heapify(int* tree, int root_index, int leave_index) {

	int parent = 1;
	int key = 0;
	for(int i = root_index; i <= leave_index; i++) {
		key = tree[i];
		parent = tree[i/2];
		int j = i;
		while(key <= parent) {
			swap(j, j/2, tree);
			j = j/2;
			key = tree[j];
			parent = tree[j/2];
		}
		
	}
}

int total_size = 0;
void insert_array(int* queue, int size) {
		
	q = (int*)malloc(sizeof(int)*(size));
	memcpy(q, queue, size*(sizeof(int)));
	total_size = size;
	heapify(q, 1, size-1);
}

void insert_index(int num) {
	q = (int*)realloc(q, (sizeof(int))*(total_size+1));
	q[total_size] = num;
	
	heapify(q, 1, total_size);
	total_size += 1;

}

void extract_min(int* queue, int root, int length)
{
	int minNode = -1;
	int left_child_index = root*2;
	int right_child_index = root*2 +1;

	if((left_child_index < length) && q[left_child_index]< q[root] )
		minNode = left_child_index;
	else minNode = root;
	if((right_child_index < length) && (q[right_child_index] < q[root]) && (q[right_child_index] < q[left_child_index]))
		minNode = right_child_index;
	
	if(minNode != root) {
		swap(minNode, root, q);
		extract_min(q, minNode, length);	
	}
	
	
}

int main()
{
	//heapify(test, 1, TOTAL_NUM);
	//printf("end123sizeof(test): %lu", sizeof(test)/sizeof(int));
	
	/*int queue[5] = {0, 7, 3, 7,5};
	
	insert_index(23);
	insert_index(1);
	insert_index(2);
	for(int i = 1; i< total_size; i++)
		printf(" %d ", q[i]);
	//insert(test, 10);
	printf("\n");	
	for(int i = 1; i<10; i++)
		printf(" %d ", q[i]);
	free(q);
	printf("\n");*/
	/*insert_array(test, 27);
	cout<<"total size"<<total_size<<endl;
	insert_array(test, TOTAL_NUM);
	for(int i = TOTAL_NUM ; i>0; i--) {
		cout<<"q[min]"<<q[1]<<endl;
		q[ROOT] = q[i];
		q[i] = NULL;
		extract_min(q, 1, i);			
	}	
	
*/
	int testt[8] = {0, 7,8,9,1,2,3,4};
	heapify(testt, 1, 7);
	for(int i = 1; i< 8; i++)
		printf("%d ", testt[i]);		
	//insert_index(1);
	
	cout<<"end"<<endl;
}
