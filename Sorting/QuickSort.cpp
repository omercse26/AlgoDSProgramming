#include <stdio.h>
int a[] = {6,5,3,2};
void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}	

int partition(int left, int right)
{
	int pivot = left;
	while (left < right)
	{
		while ( a[left] <= a[pivot])
			left++;
		while ( a[pivot] < a[right])
			right--;		
		if (left < right) swap(a+left, a+right);
	}
		// This last phase is important.
		// Since pivot should be in the middle, we have to swap it with the middle
		
		int temp = a[right];		
		a[right] = a[pivot];
		a[pivot] = temp;
        return right;
}
		
void sort(int left, int right)
{
	if (left <= right) {            
            int pivot = partition(left,right);           
            sort(left,pivot-1);
            sort(pivot+1,right);
	}
}		

int main()
{
	sort(0,3);
        for (int i=0; i<4; i++)
            printf("%d ",a[i]);
	return 0;
}	
		
	   