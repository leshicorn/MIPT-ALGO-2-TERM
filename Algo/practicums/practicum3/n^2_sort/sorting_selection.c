#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int* arr, int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted part of the array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the minimum element with the first element of the unsorted part of the array
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}


void fill_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void print_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    for (int i = 100; i < 10000; i += 100) {
        double time_spent = 0.0;
        int* arr = calloc(i, sizeof(int));
        fill_array(arr, i);
        clock_t begin = clock();
        selection_sort(arr, i);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        free(arr);
    }
}