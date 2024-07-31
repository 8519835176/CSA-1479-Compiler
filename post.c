#include <stdio.h>

int main() {
    int num, countPositive = 0, countNegative = 0, n;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        if (num > 0) {
            countPositive++;
        } else if (num < 0) {
            countNegative++;
        }
    }
    
    printf("Number of positive numbers: %d\n", countPositive);
    printf("Number of negative numbers: %d\n", countNegative);
    
    return 0;
}