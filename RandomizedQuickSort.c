#include <stdio.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For seeding random number generator

int count = 0;

void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Function to select a random pivot and place it at the end
int randomizedPartition(int A[], int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1); // Generate random pivot index
    int temp = A[randomIndex]; 
    A[randomIndex] = A[high]; 
    A[high] = temp; // Swap random pivot with the last element
    count++;

    // Normal partitioning (Lomuto's scheme)
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++) 
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

    // Swap pivot to its correct position
    temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;
    count++;

    return i + 1;
}

void randomizedQuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int partitionIndex = randomizedPartition(A, low, high);
        randomizedQuickSort(A, low, partitionIndex - 1);  // Sort left subarray 
        randomizedQuickSort(A, partitionIndex + 1, high); // Sort right subarray
    }
}

int main()
{
    int A[] = {9, 4, 4, 8, 7, 5, 6};
    int n = 7;

    srand(time(0)); // Seed the random number generator for different runs

    printArray(A, n);
    randomizedQuickSort(A, 0, n - 1);
    printArray(A, n);
    printf("%d",count);

    return 0;
}
