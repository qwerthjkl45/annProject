#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <iostream>

long long running_count = 0;
using namespace std;
int *merge(int*leftData, int* rightData, int leftLength, int rightLength)
{
	int *combineData = new int[leftLength+ rightLength];
	int rightIndex = 0 ;
	int leftIndex = 0;
	for(int i = 0 ;i < (leftLength+ rightLength); i++)
	{
		if((rightIndex == rightLength ) &&(leftIndex != leftLength))
		{
			combineData[i] = leftData[leftIndex];
			leftIndex++;
		}
		else if((leftIndex == leftLength) && ((rightIndex != rightLength )))
		{
			combineData[i] = rightData[rightIndex];
			rightIndex++;
			running_count = running_count+ (leftLength - leftIndex);
		}
		else 
		{
			if(rightData[rightIndex] > leftData[leftIndex])
			{
				combineData[i] = leftData[leftIndex];
				leftIndex++;
			}
			else
			{
				combineData[i] = rightData[rightIndex];
				rightIndex++;
				running_count = running_count+ (leftLength - leftIndex);
			}
						
		}
	}
	return combineData; 
}

int* spilt(int* data, int length)
{
	
	int middle = length/2;
	if(length > 1)
	{
		int *leftData = new int[middle];
		int *rightData = new int[length - middle];
		for(int i = 0; i < middle; i++)
		{
			leftData[i] = data[i];
		}		
		for(int j = 0; j < length- middle; j ++)
		{
			rightData[j] = data[middle + j];
		}
		data = merge(spilt(leftData, middle), spilt(rightData, length - middle), middle, length - middle );
		return data; 
		return merge(spilt(leftData, middle), spilt(rightData, length - middle), middle, length - middle );
	}	
		return data;// data;		
}

int *test(int* data)
{
	int *array = new int[8];
	//array = &data[0];
	array = data;	
	return array;	
}


int main()
{
	int data[100010];
	int i = 0;

	char ch[256];
	FILE* f = fopen("input1.txt", "r");
	if(f == NULL)
		printf("file didnt open\n");
	else{	
		while(fgets(ch, 256, f) != NULL)
		{
			data[i] = atoi(ch);
			i++;
			
		}
		fclose(f);
	}
	int length = i;
	printf("before spilt data lenftht %d", length);
	int *array = spilt(data, length);
	printf("\n\n");
	
	printf("running count %lld", running_count);
	return 0;
}
