#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, k, i;
    scanf("%d%d", &n, &k);
    int x[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    qsort(x, n, sizeof(int), cmpfunc); // Sort the array of coordinates
    int left = 1, right = x[n-1] - x[0]; // Set the search range
    while (left <= right) {
        int mid = (left + right) / 2; // Calculate the mid-point
        int count = 1; // Initialize count to 1 (first segment)
        int start = x[0]; // Initialize the start of the current segment
        for (i = 1; i < n; i++) {
            if (x[i] - start > mid) { // If the current segment is too long
                count++; // Increment count
                start = x[i]; // Start a new segment
            }
        }
        if (count <= k) { // If k or fewer segments are needed
            right = mid - 1; // Decrease the search range
        } else { // If more than k segments are needed
            left = mid + 1; // Increase the search range
        }
    }
    printf("%d\n", left); // Output the minimum segment length
    return 0;
}
