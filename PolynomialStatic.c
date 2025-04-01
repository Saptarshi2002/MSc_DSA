#include<stdio.h>

#define MAX 100

typedef struct Polynomial {
    int coeff;
    int power;
} Polynomial;


int add(Polynomial A[],int degA, Polynomial B[],int degB, Polynomial C[]){
    int i=0,j=0,k=0;

    while (i < degA && j < degB) {
        if (A[i].power > B[j].power) {
            C[k++] = A[i++];
        } else if (A[i].power < B[j].power) {
            C[k++] = B[j++];
        } else {
            C[k].power = A[i].power;
            C[k].coeff = A[i].coeff + B[j].coeff;
            i++; j++; k++;
        }
    }

    while (i < degA) 
        C[k++] = A[i++];
    while (j < degB) 
        C[k++] = B[j++];
    
    return k;
}

int substract(Polynomial A[],int degA, Polynomial B[],int degB, Polynomial C[]){
    int i=0,j=0,k=0;

    while (i < degA && j < degB) {
        if (A[i].power > B[j].power) {
            C[k++] = A[i++];
        } else if (A[i].power < B[j].power) {
            C[k++] = B[j++];
        } else {
            C[k].power = A[i].power;
            C[k].coeff = A[i].coeff - B[j].coeff;
            i++; j++; k++;
        }
    }

    while (i < degA) 
        C[k++] = A[i++];
    while (j < degB) {
        C[k] = B[j++];
        C[k].coeff=-C[k].coeff;
        k++;
    }
    return k;
}


int multliply(Polynomial A[], int degA, Polynomial B[], int degB, Polynomial C[]) {
    int k = 0;
    for (int i = 0; i < degA; i++) {
        for (int j = 0; j < degB; j++) {
            int power = A[i].power + B[j].power;
            int coeff = A[i].coeff * B[j].coeff;
            int found = 0;
            for (int m = 0; m < k; m++) {
                if (C[m].power == power) {
                    C[m].coeff += coeff;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                C[k].power = power;
                C[k++].coeff = coeff;
            }
        }
    }
    return k;
}


int differentiate(Polynomial A[], int degA, Polynomial C[]) {
    int k = 0;
    for (int i = 0; i < degA; i++) {
        if (A[i].power > 0) {
            C[k].coeff = A[i].coeff * A[i].power;
            C[k++].power = A[i].power - 1;
        }
    }
    return k;
}


void display(Polynomial A[], int degree) {
    for (int i = 0; i < degree; i++) {
        if (A[i].coeff != 0) {
            if (i > 0 && A[i].coeff > 0) {
                printf(" + ");
            }
            printf("%dx^%d", A[i].coeff, A[i].power);
        }
    }
    if (degree == 0) {
        printf("0");
    }
    printf("\n");
}


int main() {
    Polynomial A[MAX], B[MAX], C[MAX];
    int degA, degB, degC;
    
    // Input first polynomial
    printf("Enter the number of terms in polynomial A: ");
    scanf("%d", &degA);
    printf("Enter the coefficients and powers: ");
    for (int i = 0; i < degA; i++) {
        scanf("%d %d", &A[i].coeff, &A[i].power);
    }
    
    // Input second polynomial
    printf("Enter the number of terms in polynomial B: ");
    scanf("%d", &degB);
    printf("Enter the coefficients and powers: ");
    for (int i = 0; i < degB; i++) {
        scanf("%d %d", &B[i].coeff, &B[i].power);
    }
    
    // Addition
    degC = add(A, degA, B, degB, C);
    printf("A + B: ");
    display(C, degC);
    
    // Subtraction
    degC = substract(A, degA, B, degB, C);
    printf("A - B: ");
    display(C, degC);
    
    // Multiplication
    degC = multliply(A, degA, B, degB, C);
    printf("A * B: ");
    display(C, degC);
    
    // Differentiation of A
    degC = differentiate(A, degA, C);
    printf("d(A)/dx: ");
    display(C, degC);
    
    return 0;
}






