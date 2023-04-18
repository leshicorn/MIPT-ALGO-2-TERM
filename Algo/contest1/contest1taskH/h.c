#include <stdio.h>
#include <stdlib.h>


#define MODULO (10000000LL + 4321LL)

/**
 * @brief Generates the sequence A of length n, where A[0] = A0 and A[1] = A1.
 * 
 * @param A 
 * @param n 
 * @param A0 
 * @param A1 
 * @return empty return
 */
void generate_sequence(long long int *A, int n, long long int A0, long long int A1) {
    A[0] = A0;
    A[1] = A1;
    for (int i = 2; i < n; i++) {
        A[i] = (A[i - 1] * 123LL + A[i - 2] * 45LL) % MODULO;
    }
}

/**
 * @brief Partitions the array A[left..right] around the pivot A[right].
 * 
 * @param A 
 * @param left 
 * @param right 
 * @return * Function 
 */
int partition(long long int *A, int left, int right) {
    long long int pivot = A[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            i++;
            long long int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    long long int temp = A[i + 1];
    A[i + 1] = A[right];
    A[right] = temp;
    return i + 1;
}

/**
 * @brief Finds the k-th order statistic in the array A of length n.
 * 
 */
long long int kth_order_statistic(long long int *A, int n, int k) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int pivot_index = partition(A, left, right);
        if (pivot_index == k - 1) {
            return A[pivot_index];
        } else if (pivot_index < k - 1) {
            left = pivot_index + 1;
        } else {
            right = pivot_index - 1;
        }
    }
    return -1;
}

int main() {
    int n = 0, k = 0;
    long long int A0 = 0, A1 = 0;

    if (scanf("%d %d %lld %lld", &n, &k, &A0, &A1) != 4) {
        printf("Invalid input format\n");
        return -1;
    }

    long long int* A = calloc(n, sizeof(long long int));
    generate_sequence(A, n, A0, A1);

    long long int kth = kth_order_statistic(A, n, k);
    printf("%lld\n", kth);

    free(A);
    return 0;
}
