#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j, temp;
    for (j = low; j < high; j++) {
        // Move elements smaller than the pivot to the left subarray
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Move the pivot element to its correct position
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pivot_idx = partition(arr, low, high);
        // Recursively sort the left and right subarrays
        quick_sort(arr, low, pivot_idx - 1);
        quick_sort(arr, pivot_idx + 1, high);
    }
}

void fill_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

int main() {
    for (int i = 1000; i <= 1000000; i += 10000) {
        // int i = 1000000;
        double time_spent = 0.0;
        int* arr = calloc(i, sizeof(int));
        fill_array(arr, i);
        clock_t begin = clock();
        quick_sort(arr, 0, i);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        free(arr);
    }
}