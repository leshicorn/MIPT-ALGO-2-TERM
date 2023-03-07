#include <stdio.h>
#include <stdlib.h>

int f(int l, int N, int k, int* receivers) {
    int count = 0;
    int last = 0;
    for (int i = 0; i < N; i++) {
        if (receivers[i] - receivers[last] > l) {
            return 0;
        }
        if (receivers[i] - receivers[last] <= l) {
            continue;
        }
        count++;
        last = i - 1;
        if (count > k) {
            return 0;
        }
    }
    return 1;
}

int minimum_l(int N, int k, int* receivers) {
    int lower_bound = 1;
    int upper_bound = receivers[N-1] - receivers[0];
    while (lower_bound < upper_bound) {
        int mid = (lower_bound + upper_bound) / 2;
        if (f(mid, N, k, receivers)) {
            upper_bound = mid;
        } else {
            lower_bound = mid + 1;
        }
    }
    return lower_bound;
}

// int main() {
//     int n = 0, k = 0, i = 0;
//     if (scanf("%d%d", &n, &k) != 2) {
//         printf("Error");
//         return -1;
//     }
//     int* receivers = calloc(n, sizeof(int));
//     for (i = 0; i < n; i++) {
//         if (scanf("%d", &receivers[i]) != 1) {
//             printf("Error");
//             return -1;
//         }
//     }
//     int min_l = minimum_l(n, k, receivers);

//     printf("%d\n", min_l);

//     free(receivers);

//     return 0;
// }

int main() {
    int N = 6;
    int k = 2;
    int receivers[] = {1, 2, 3, 9, 8, 7};
    int min_l = minimum_l(N, k, receivers);
    printf("Minimum length l = %d\n", min_l);
    return 0;
}
