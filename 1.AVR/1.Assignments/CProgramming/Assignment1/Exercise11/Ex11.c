#include <stdio.h>

int main() 
{
    int N = 0;

    printf("Enter a positive integer (expected: 100): ");

    // 1. Check if the user entered a valid integer
    if (scanf("%d", &N) != 1) {
        printf("Error: Invalid input! Please enter an integer.\n");
        return 1;
    }

    // 2. Validate that the integer is positive
    if (N <= 0) {
        printf("Error: Input must be a positive integer.\n");
        return 1;
    }

    // 3. Validate target scope (specifically checking for 100)
    if (N != 100) {
        printf("Warning: Calculating sum for N = %d instead of 100.\n", N);
    }

    // Calculate sum using the formula
    long long sum = (long long)N * (N + 1) / 2;

    printf("Sum of the first %d integers is: %lld\n", N, sum);

    return 0;
}
   