#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int* arr, int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already sorted
        for (j = 0; j < n - i - 1; j++) {
            // Swap adjacent elements if they are in the wrong order
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void fill_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

int main() {
    for (int i = 100; i <= 10000; i += 100) {
        double time_spent = 0.0;
        int* arr = calloc(i, sizeof(int));
        fill_array(arr, i);
        clock_t begin = clock();
        bubble_sort(arr, i);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d %lf\n", i, time_spent);
        free(arr);
    }
}
