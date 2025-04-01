#include <stdio.h>
#include <stdlib.h>

typedef struct Polynomial {
    int coeff;
    int power;
    struct Polynomial* next;
} Polynomial;

// Function to create a new polynomial term
Polynomial* createTerm(int coeff, int power) {
    Polynomial* newTerm = (Polynomial*)malloc(sizeof(Polynomial));
    newTerm->coeff = coeff;
    newTerm->power = power;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term into a polynomial
void insertTerm(Polynomial** poly, int coeff, int power) {
    if (coeff == 0) return; // Skip zero coefficient terms
    Polynomial* newTerm = createTerm(coeff, power);
    if (*poly == NULL) {
        *poly = newTerm;
        return;
    }
    
    // Insert in sorted order (descending powers)
    Polynomial *curr = *poly, *prev = NULL;
    while (curr && curr->power > power) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr && curr->power == power) {
        curr->coeff += coeff; // Combine like terms
        free(newTerm);
        if (curr->coeff == 0) { // Remove zero coefficient terms
            if (prev) prev->next = curr->next;
            else *poly = curr->next;
            free(curr);
        }
    } else {
        newTerm->next = curr;
        if (prev) prev->next = newTerm;
        else *poly = newTerm;
    }
}

// Function to display a polynomial
void displayPolynomial(Polynomial* poly) {
    if (!poly) {
        printf("0\n");
        return;
    }
    while (poly) {
        printf("%dx^%d", poly->coeff, poly->power);
        if (poly->next && poly->next->coeff >= 0) printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

// Function to add two polynomials
Polynomial* addPolynomials(Polynomial* A, Polynomial* B) {
    Polynomial* result = NULL;
    while (A || B) {
        int coeff, power;
        if (A && (!B || A->power > B->power)) {
            coeff = A->coeff;
            power = A->power;
            A = A->next;
        } else if (B && (!A || A->power < B->power)) {
            coeff = B->coeff;
            power = B->power;
            B = B->next;
        } else {
            coeff = A->coeff + B->coeff;
            power = A->power;
            A = A->next;
            B = B->next;
        }
        insertTerm(&result, coeff, power);
    }
    return result;
}

// Function to subtract polynomial B from A
Polynomial* subtractPolynomials(Polynomial* A, Polynomial* B) {
    Polynomial* result = NULL;
    while (A || B) {
        int coeff, power;
        if (A && (!B || A->power > B->power)) {
            coeff = A->coeff;
            power = A->power;
            A = A->next;
        } else if (B && (!A || A->power < B->power)) {
            coeff = -B->coeff;
            power = B->power;
            B = B->next;
        } else {
            coeff = A->coeff - B->coeff;
            power = A->power;
            A = A->next;
            B = B->next;
        }
        insertTerm(&result, coeff, power);
    }
    return result;
}

// Function to multiply two polynomials
Polynomial* multiplyPolynomials(Polynomial* A, Polynomial* B) {
    Polynomial* result = NULL;
    Polynomial* a;
    Polynomial* b;
    for (a = A; a; a = a->next) {
        for (b = B; b; b = b->next) {
            insertTerm(&result, a->coeff * b->coeff, a->power + b->power);
        }
    }
    return result;
}

// Function to differentiate a polynomial
Polynomial* differentiatePolynomial(Polynomial* poly) {
    Polynomial* result = NULL;
    while (poly) {
        if (poly->power > 0)
            insertTerm(&result, poly->coeff * poly->power, poly->power - 1);
        poly = poly->next;
    }
    return result;
}

// Function to free a polynomial
void freePolynomial(Polynomial* poly) {
    while (poly) {
        Polynomial* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Polynomial *A = NULL, *B = NULL, *C;
    int degA, degB, coeff, power, i;
    
    // Input first polynomial
    printf("Enter the number of terms in polynomial A: ");
    scanf("%d", &degA);
    printf("Enter the coefficients and powers: ");
    for (i = 0; i < degA; i++) {
        scanf("%d %d", &coeff, &power);
        insertTerm(&A, coeff, power);
    }
    
    // Input second polynomial
    printf("Enter the number of terms in polynomial B: ");
    scanf("%d", &degB);
    printf("Enter the coefficients and powers: ");
    for (i = 0; i < degB; i++) {
        scanf("%d %d", &coeff, &power);
        insertTerm(&B, coeff, power);
    }
    
    // Addition
    C = addPolynomials(A, B);
    printf("A + B: ");
    displayPolynomial(C);
    freePolynomial(C);
    
    // Subtraction
    C = subtractPolynomials(A, B);
    printf("A - B: ");
    displayPolynomial(C);
    freePolynomial(C);
    
    // Multiplication
    C = multiplyPolynomials(A, B);
    printf("A * B: ");
    displayPolynomial(C);
    freePolynomial(C);
    
    // Differentiation of A
    C = differentiatePolynomial(A);
    printf("d(A)/dx: ");
    displayPolynomial(C);
    freePolynomial(C);
    
    freePolynomial(A);
    freePolynomial(B);
    return 0;
}
