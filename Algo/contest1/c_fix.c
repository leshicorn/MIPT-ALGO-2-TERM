#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, k, i;
    if (scanf("%d%d", &n, &k) != 2) {
        printf("Error");
        return -1;
    }
    int x[n];
    for (i = 0; i < n; i++) {
        if (scanf("%d", &x[i]) != 1) {
            printf("Error");
            return -1;
        }
    }
    qsort(x, n, sizeof(int), cmpfunc);
    int left = 1, right = x[n-1] - x[0];
    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 1;
        int start = x[0];
        for (i = 1; i < n; i++) {
            if (x[i] - start > mid) {
                count++;
                start = x[i];
            }
        }
        if (count <= k) { 
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    printf("%d\n", left);
    return 0;
}
