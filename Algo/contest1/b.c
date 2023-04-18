#include <stdio.h>

#include <stdbool.h>

bool BinarySearch(const int* begin, const int* end, int target) {
    while (begin < end) {
        const int* mid = begin + (end - begin) / 2;
        if (*mid == target) {
            return true;
        } else if (*mid < target) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return false;
}

int Solution() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("error");
        return -1;
    }

    int arr[n];
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("error");
            return -1;
        }
    }

    int q;
    if (scanf("%d", &q) != 1) {
        printf("error");
        return -1;
    }

    while (q--) {
        int i, j, t;
        if (scanf("%d %d %d", &i, &j, &t) != 3) {
            printf("error");
            return -1;
        }

        bool found = BinarySearch(&arr[i], &arr[j], t);
        printf("%s\n", found ? "YES" : "NO");
    }
    return 0;
}

int main() {
    
    int error_check = 0;
    if ((error_check = Solution()) == -1) {
        printf("error");
        return -1;
    }
    return 0;
}
