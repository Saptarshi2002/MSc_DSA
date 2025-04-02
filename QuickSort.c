#include <stdio.h>

int count =0;

void printArray(int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int partition(int A[], int low, int high)
{
    int pivot = A[high]; // Choosing the last element as pivot
    int i = low - 1;
    int temp;

    int j;
    for (j = low; j < high; j++) 
    {
        if (A[j] <= pivot) 
        {
            i++;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            count++;
        }
    }

    // Swap pivot element A[high] with A[i+1]
    temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;
    count++;


    return i + 1; // New pivot index
}

void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(A, low, high);
        quickSort(A, low, partitionIndex - 1);  // sort left subarray 
        quickSort(A, partitionIndex + 1, high); // sort right subarray
    }
}

int main()
{
    int A[] = {9, 4, 4, 8, 7, 5, 6};
    int n = 7;
    
    printArray(A, n);
    quickSort(A, 0, n - 1);
    printArray(A, n);
    printf("%d",count);
    return 0;
}
