#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Функция для сортировки по i-му байту
 * 
 * @param arr 
 * @param tmp 
 * @param n 
 * @param i 
 */
void radix_sort(uint64_t* arr, uint64_t* tmp, const int n, const int i) {
    // Создаем 256 счетчиков, один для каждого возможного значения байта
    int count[256] = {0};

    // Считаем количество элементов с определенным значением байта
    for (size_t j = 0; j < n; ++j) {
        uint8_t byte = (arr[j] >> (8 * i)) & 0xFF;
        count[byte]++;
    }

    // Вычисляем индексы начала каждой группы в промежуточном массиве
    int accum = 0;
    for (size_t j = 0; j < 256; ++j) {
        int tmp_count = count[j];
        count[j] = accum;
        accum += tmp_count;
    }

    // Распределение элементов по группам в промежуточном массиве
    for (size_t j = 0; j < n; ++j) {
        uint8_t byte = (arr[j] >> (8 * i)) & 0xFF;
        tmp[count[byte]++] = arr[j];
    }

    // Копируем элементы из промежуточного массива в исходный
    memcpy(arr, tmp, n * sizeof(uint64_t));
}

// Функция поразрядной сортировки LSD
void lsd_radix_sort(uint64_t* arr, const int n) {
    uint64_t* tmp = (uint64_t*) malloc(n * sizeof(uint64_t));

    // Сортировка по каждому байту
    for (size_t i = 0; i < 8; ++i) {
        radix_sort(arr, tmp, n, i);
    }

    free(tmp);
}

int Input(uint64_t* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lu", &arr[i]) != 1) {
            printf("Error");
            return -1;
        }
    }
    return 0;
}

void Output(uint64_t* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lu\n", arr[i]);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Error");
        return -1;
    }

    uint64_t* arr = (uint64_t*) malloc(n * sizeof(uint64_t));
    if (Input(arr, n) == -1) {
        return -1;
    }

    lsd_radix_sort(arr, n);

    Output(arr, n);

    free(arr);
    return 0;
}