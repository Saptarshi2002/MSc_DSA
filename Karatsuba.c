#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to get the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Karatsuba algorithm for multiplication
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Calculate the size of the numbers
    int n = max((int)log10(x) + 1, (int)log10(y) + 1);
    int m = n / 2;

    long long high1 = x / (long long)pow(10, m);
    long long low1 = x % (long long)pow(10, m);
    long long high2 = y / (long long)pow(10, m);
    long long low2 = y % (long long)pow(10, m);

    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);

    return (z2 * (long long)pow(10, 2 * m)) + ((z1 - z2 - z0) * (long long)pow(10, m)) + z0;
}

int main() {
    long long x, y;
    printf("Enter two numbers: ");
    scanf("%lld %lld", &x, &y);
    
    long long result = karatsuba(x, y);
    printf("Product: %lld\n", result);
    
    return 0;
}
