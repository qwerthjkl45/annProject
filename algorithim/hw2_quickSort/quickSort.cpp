#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

void quickSort(int *array, int length)
{
    int *leftData ;
    int *rightData;
    int rightIndex = 0 ;
	int leftIndex = 0;
    printf("%d length", length);
    if(length <= 1)
        return ;
    else
    {
        int pivot = array[0];
        printf("pivlot %d\n", pivot );		
		for(int z = 0; z < length; z++)
			printf("%d ", array[z]);
		printf("\n\n");
        for(int i = 1; i < length ; i++)
        {
            if(array[i] > pivot)
            {
                if(rightIndex == 0)
                    rightData = (int*)malloc(sizeof(int));
                else
                    rightData = (int*)realloc(rightData, sizeof(int)* (rightIndex +1));   
                rightData[rightIndex] = array[i];
                rightIndex++;
            }
            else
            {
                if(leftIndex == 0)
                    leftData = (int*)malloc(sizeof(int));
                else 
                    leftData = (int*)realloc(leftData, sizeof(int)*(leftIndex +1));
                leftData[leftIndex] = array[i];
                leftIndex++;                            
            }
            
        }
        quickSort(leftData, leftIndex);
        quickSort(rightData, rightIndex);

	for(int j = 0; j < length; j++)
        {   
            if(j < leftIndex)
                array[j] = leftData[j];
            else if(j == (leftIndex))
                array[j] = pivot;
            else
                array[j] = rightData[j - (leftIndex +1)];
        }
                
        return ;
    }
        
}

int main()
{
    int data[10] = {5,4,4,3,1,7,8,9,10,11}; 
    int length = sizeof(data)/sizeof(int);
    quickSort(data, length);
    for(int i = 0 ;i < length; i++)
        printf("%d ", data[i]);
    
}
