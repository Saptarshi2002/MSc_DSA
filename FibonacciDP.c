#include <stdio.h>

// Function to calculate the n-th Fibonacci number using Dynamic Programming
long long Fibonacci(int n) {
    if (n <= 1)
        return n;
    
    long long fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    return fib[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    printf("Fibonacci(%d) = %lld\n", n, Fibonacci(n));
    
    return 0;
}
