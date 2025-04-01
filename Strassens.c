#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 32  // Maximum size for static arrays (power of 2 for Strassen's)

// Function to add two matrices
void addMatrix(int n, int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int n, int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen's algorithm
void strassenMultiply(int n, int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE]) {
    // Base case: if matrix size is 1x1
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    
    // Create submatrices
    int A11[MAX_SIZE][MAX_SIZE], A12[MAX_SIZE][MAX_SIZE], A21[MAX_SIZE][MAX_SIZE], A22[MAX_SIZE][MAX_SIZE];
    int B11[MAX_SIZE][MAX_SIZE], B12[MAX_SIZE][MAX_SIZE], B21[MAX_SIZE][MAX_SIZE], B22[MAX_SIZE][MAX_SIZE];
    int C11[MAX_SIZE][MAX_SIZE], C12[MAX_SIZE][MAX_SIZE], C21[MAX_SIZE][MAX_SIZE], C22[MAX_SIZE][MAX_SIZE];
    
    int M1[MAX_SIZE][MAX_SIZE], M2[MAX_SIZE][MAX_SIZE], M3[MAX_SIZE][MAX_SIZE], M4[MAX_SIZE][MAX_SIZE];
    int M5[MAX_SIZE][MAX_SIZE], M6[MAX_SIZE][MAX_SIZE], M7[MAX_SIZE][MAX_SIZE];
    
    int tempA[MAX_SIZE][MAX_SIZE], tempB[MAX_SIZE][MAX_SIZE];
    
    // Divide matrices into 4 submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    // Calculate M1 to M7
    // M1 = (A11 + A22) * (B11 + B22)
    addMatrix(newSize, A11, A22, tempA);
    addMatrix(newSize, B11, B22, tempB);
    strassenMultiply(newSize, tempA, tempB, M1);
    
    // M2 = (A21 + A22) * B11
    addMatrix(newSize, A21, A22, tempA);
    strassenMultiply(newSize, tempA, B11, M2);
    
    // M3 = A11 * (B12 - B22)
    subtractMatrix(newSize, B12, B22, tempB);
    strassenMultiply(newSize, A11, tempB, M3);
    
    // M4 = A22 * (B21 - B11)
    subtractMatrix(newSize, B21, B11, tempB);
    strassenMultiply(newSize, A22, tempB, M4);
    
    // M5 = (A11 + A12) * B22
    addMatrix(newSize, A11, A12, tempA);
    strassenMultiply(newSize, tempA, B22, M5);
    
    // M6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(newSize, A21, A11, tempA);
    addMatrix(newSize, B11, B12, tempB);
    strassenMultiply(newSize, tempA, tempB, M6);
    
    // M7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(newSize, A12, A22, tempA);
    addMatrix(newSize, B21, B22, tempB);
    strassenMultiply(newSize, tempA, tempB, M7);
    
    // Calculate C submatrices
    // C11 = M1 + M4 - M5 + M7
    addMatrix(newSize, M1, M4, tempA);
    subtractMatrix(newSize, tempA, M5, tempB);
    addMatrix(newSize, tempB, M7, C11);
    
    // C12 = M3 + M5
    addMatrix(newSize, M3, M5, C12);
    
    // C21 = M2 + M4
    addMatrix(newSize, M2, M4, C21);
    
    // C22 = M1 - M2 + M3 + M6
    subtractMatrix(newSize, M1, M2, tempA);
    addMatrix(newSize, tempA, M3, tempB);
    addMatrix(newSize, tempB, M6, C22);
    
    // Combine C submatrices into C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];
    
    printf("Enter the size of the matrices (must be power of 2 and <= %d): ", MAX_SIZE);
    scanf("%d", &n);
    
    if (n > MAX_SIZE || (n & (n - 1)) != 0) {
        printf("Invalid matrix size. Size must be a power of 2 and <= %d.\n", MAX_SIZE);
        return 1;
    }
    
    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    
    printf("Enter elements of matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    
    // Initialize result matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }
    
    // Perform matrix multiplication using Strassen's algorithm
    strassenMultiply(n, A, B, C);
    
    printf("\nResultant matrix C (%d x %d):\n", n, n);
    printMatrix(n, C);
    
    return 0;
}