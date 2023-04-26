#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>


#define MIN_SIZE_TO_USE_INSERTION_SORT 10

/**
 * @brief Swap two integers
 * 
 * @param a 
 * @param b 
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Choose pivot in range [low, high]
 * 
 * @param low 
 * @param high 
 * @return int 
 */
int ChoosePivot(const int low, const int high) {
    return low + rand() % (high - low + 1);
}

/**
 * @brief Partition array in range [low, high] around pivot
 * 
 * @param arr 
 * @param low 
 * @param high 
 * @return int 
 */
int partition(int* arr, const int low, const int high) {
    int pivot_idx = ChoosePivot(low, high);
    int pivot = arr[pivot_idx];

    // Move pivot to end of array
    swap(&arr[pivot_idx], &arr[high]);

    int i = low - 1;
    int j = high;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (j >= low && arr[j] > pivot);

        if (i >= j) {
            break;
        }

        swap(&arr[i], &arr[j]);
    }

    // Move pivot to its final position
    swap(&arr[i], &arr[high]);

    return i;
}

/**
 * @brief Insertion sort in range [low, high]
 * 
 * @param arr 
 * @param low 
 * @param high 
 */
void InsertionSort(int* arr, const int low, const int high) {
    for (size_t i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/**
 * @brief Quick sort in range [low, high]
 * 
 * @param arr 
 * @param low 
 * @param high 
 */
void QuickSort(int* arr, int low, int high) {
    while (high - low + 1 > MIN_SIZE_TO_USE_INSERTION_SORT) {
        int pivot_idx = partition(arr, low, high);

        if (pivot_idx - low < high - pivot_idx) {
            QuickSort(arr, low, pivot_idx - 1);
            low = pivot_idx + 1;
        } else {
            QuickSort(arr, pivot_idx + 1, high);
            high = pivot_idx - 1;
        }
    }

    InsertionSort(arr, low, high);
}

/**
 * @brief Input array of size n
 * 
 * @param n 
 * @return int* 
 */
int* Input(const int n) {
    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error: invalid input\n");
            return NULL;
        }
    }

    return arr;
}

/**
 * @brief Make sorted array
 * 
 * @param arr 
 * @param n 
 * @return int* 
 */
int* MakeSorted(int* arr, const int n) {
    QuickSort(arr, 0, n - 1);
    return arr;
}

/**
 * @brief Output array of size n
 * 
 * @param arr 
 * @param n 
 */
void Output(int* arr, const int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input");
        return 1;
    }
    
    int* arr = Input(n);

    arr = MakeSorted(arr, n);

    Output(arr, n);

    return 0;
}