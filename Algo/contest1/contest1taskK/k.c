#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>


#define MIN_SIZE_TO_USE_INSERTION_SORT 10

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int ChoosePivot(const int low, const int high) {
    // Choose a random pivot between low and high
    return low + rand() % (high - low + 1);
}

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

int* MakeSorted(int* arr, const int n) {
    QuickSort(arr, 0, n - 1);
    return arr;
}

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