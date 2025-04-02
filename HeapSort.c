#include<stdio.h>

void heapify(int arr[],int n,int i){
    int temp,max,left,right;

    max = i;
    left = 2*i+1;
    right = 2*i+2;


    if(left<n && arr[left]>arr[max]){
        max = left;
    }
    if(right<n && arr[right]>arr[max]){
        max = right;
    }

    if(max != i){
        temp = arr[i];
        arr[i]=arr[max];
        arr[max]=temp;
        heapify(arr,n,max);
    }
}



void heapsort(int arr[],int n){
    int i,temp;

    for(i=n/2;i>=0;i--){
        heapify(arr,n,i);
    }    

    for(i=n-01;i>0;i--){
        temp = arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        heapify(arr,i,0);
    }

}


int main()
{
    // initializing the array
    int arr[] = { 20, 18, 5, 15, 3, 2 };
    int n = 6;

    // Displaying original array
    printf("Original Array : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    heapsort(arr, n);

    // Displaying sorted array
    printf("Array after performing heap sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}


