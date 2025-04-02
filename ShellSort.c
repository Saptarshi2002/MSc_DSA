#include <stdio.h>

void bubbleSortGap(int arr[], int n, int gap) {

    //Bubble sort with gap increment
    for (int i = 0; i < n - gap; i++) {
        for (int j = i; j + gap < n; j += gap) {
            if (arr[j] > arr[j + gap]) {
                int temp = arr[j];
                arr[j] = arr[j + gap];
                arr[j + gap] = temp;
            }
        }
    }
}

void shellSort(int arr[], int n, int gap) {
    while (gap >= 1) {
        bubbleSortGap(arr, n, gap);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        gap -= 2; 
    }
}

int main() {
    int n, gap;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the initial odd gap: ");
    scanf("%d", &gap);
    
    if (gap % 2 == 0 || gap < 1) {
        printf("Gap must be an odd number greater than 0.\n");
        return 1;
    }
    
    shellSort(arr, n, gap);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
