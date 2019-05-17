#include<stdio.h>

int findpivot(int, int);
int partition(int, int, int);
void quick(int, int);
void swap(int, int);


int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
 
struct PartitionInfo
{
    int leftEnd;
    int rightEnd;
};

struct PartitionInfo stack[100];
int top = -1;

int main()
{
    int i;

    quickSort(0, 9);

    for(i = 0; i < 10; i++) 
    {
        printf("%d\n",array[i]);
    }

    return 0;
}

void quickSort(int startIndex, int endIndex)
{
    int pivot, pivotindex, k;

    top++;

    stack[top].leftEnd   = startIndex;
    stack[top].rightEnd  = endIndex;

    //printf("adding: s:%d l:%d r:%d \n",s,i,j);
    while(top >= 0)
    {
        startIndex = stack[top].leftEnd;
        endIndex   = stack[top].rightEnd;

        //printf("deleting: s:%d l:%d r:%d \n",s,i,j);

        --top;

        while(1)
        {
            pivotindex = findPivot(startIndex, endIndex);
            if(pivotindex == -1)
            {
	            break;
            }

            pivot = array[pivotindex];
            k = partition(startIndex, endIndex, pivot);
            ++top;

            stack[top].leftEnd  = k;
            stack[top].rightEnd = endIndex;
            //printf("adding: s:%d l:%d r:%d \n",s,k,j);
            endIndex = k-1;
        }
   }
}

int findPivot(int startIndex, int endIndex)
{
    int k;
    int firstkey = array[startIndex];

    for(k = startIndex + 1; k <= endIndex; k++)
    {
        if(array[k] > firstkey)
        {
            return k;
        }
        else if(array[k] < firstkey)
        {
            return startIndex;
        }
    }

    return -1; // different keys were never found
}

int partition(int startIndex, int endIndex, int pivot)
{
    int left, right;

    left  = startIndex;
    right = endIndex; 

    while(left <= right)  //while(l<r) think of this cos l==r is not possible
    {
        swap(left, right);

        while(array[left] < pivot)      { ++left;  }

        while(array[right] >= pivot)    { --right; }
    }

    return left;
}

void swap(int i, int j)
{
    int temp = array[j];
    array[j] = array[i];
    array[i] = temp;
}
