#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int* arr, int* left, int* right, int left_size, int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void merge_sort(int* arr, int size) {
    if (size < 2) {
        return;
    }
    int mid = size / 2;
    int* left = calloc(mid, sizeof(int));
    int* right = calloc(size - mid, sizeof(int));
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }
    merge_sort(left, mid);
    merge_sort(right, size - mid);
    merge(arr, left, right, mid, size - mid);
}

void fill_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

int main() {
    for (int i = 1000; i <= 1000000; i += 10000) {
        double time_spent = 0.0;
        int* arr = calloc(i, sizeof(int));
        fill_array(arr, i);
        clock_t begin = clock();
        merge_sort(arr, i);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        free(arr);
    }
}