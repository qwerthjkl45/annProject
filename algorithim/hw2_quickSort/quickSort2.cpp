#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
long long running_count = 0;
void quick_sort(int* data, int length, int iNum, int jNum, int pivotNum)
{
	
	
	if(length <= 1)
		return;
	else
	{
		int i = iNum;
		int j = jNum;
		int pivot = data[pivotNum];
	
		//printf("pivot %d %d %d %d\n", pivot, i ,j, length);
		for( j ; j < (jNum +length -1 ); j++){
			if(data[j] < pivot){	
				int temp = data[j];
				data[j] = data[i];
				data[i] = temp;
				i = i+1;
			}
		}
		
		data[pivotNum] = data[i -1];
		data[i -1] = pivot;
		if(j>= i)
			quick_sort(data, j -i , i, i, j);//i
		running_count = running_count + length -1;
		quick_sort(data, i -1- pivotNum, pivotNum, pivotNum, i-1);//pivotNum
	}
	return;
}

int main()
{
	
	int data[10] = {5,4,8,2,1,7,8,6,11,10}; 
	/*int i = 0;
	int data[100010];
	int i = 0;
	char ch[256];
	FILE* f = fopen("input.txt", "r");
	if(f == NULL)
		printf("file didnt open\n");
	else{	
		while(fgets(ch, 256, f) != NULL) {
			data[i] = atoi(ch);
			i++;			
		}
		fclose(f);
	}*/
	int length = 10;//i;
	//printf("legnth %d", i);
	quick_sort(data, length,0, 0, length-1);
	//printf("running count %lld", running_count);
	for(int x =0; x < length ; x++)
		printf("%d ", data[x]);
	return 0;
}
