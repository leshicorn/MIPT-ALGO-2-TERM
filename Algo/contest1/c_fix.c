#include <limits.h>

#include <stdio.h>

#include <stdlib.h>


#define SUCCESS 0
#define MIN_SIZE_TO_USE_InsertionSort 10
#define MISTAKE -1
#define ll long long int


void Merge(ll* arr, ll* left, ll* right, ll left_size, ll right_size) {
    ll i = 0, j = 0, k = 0;
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

void MergeSort(ll* arr, ll size) {
    if (size < 2) {
        return;
    }
    ll mid = size / 2;
    ll* left = calloc(mid, sizeof(ll));
    ll* right = calloc(size - mid, sizeof(ll));
    for (ll i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (ll i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }
    MergeSort(left, mid);
    MergeSort(right, size - mid);
    Merge(arr, left, right, mid, size - mid);
}

ll CmpFunction(const void *a, const void *b) {
    return (*(ll*)a - *(ll*)b);
}

void Swap(ll* a, ll* b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

ll ChoosePivot(ll low, ll high) {
    // Choose a random pivot between low and high
    return low + rand() % (high - low + 1);
}

ll Partition(ll* arr, ll low, ll high) {
    ll pivot_idx = ChoosePivot(low, high);
    ll pivot = arr[pivot_idx];

    // Move pivot to end of array
    Swap(&arr[pivot_idx], &arr[high]);

    ll i = low - 1;
    ll j = high;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (j >= low && arr[j] > pivot);

        if (i >= j) {
            break;
        }

        Swap(&arr[i], &arr[j]);
    }

    // Move pivot to its final position
    Swap(&arr[i], &arr[high]);

    return i;
}

void InsertionSort(ll* arr, ll low, ll high) {
    for (ll i = low + 1; i <= high; i++) {
        ll key = arr[i];
        ll j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void QuickSort(ll* arr, ll low, ll high) {
    while (high - low + 1 > MIN_SIZE_TO_USE_InsertionSort) {
        ll pivot_idx = Partition(arr, low, high);

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

ll Points(ll* arr, ll mid, ll size, ll k)
{
    ll count = 0;
    ll start = arr[0];
    ll mid_point = start + mid;
    ll i = 1;
    while (i < size) {
        while (i < size && mid_point >= arr[i]) {
            i++;
        }
        count++;
        if (i >= size) {
            break;
        }
        mid_point = arr[i] + mid;
        // if (i < size) {
        //     mid_point = arr[i] + mid;
        // }
        // else {
        //     break;
        // }
    }

    return (count <= k);
}

ll GetAnswer(ll* arr, ll left, ll right, ll mid, ll n, ll k) {
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (Points(arr, mid, n, k)) {
            right = mid;
        } else {
            left = mid; 
            }
    }
    ll result = 0;
    if (Points(arr, left, n, k)) {
        result = left;
        return result;
    } else if (Points(arr, right, n, k)) {
        result = right;
        return result;
    } else if (Points(arr, mid, n, k)) {
        result = mid;
        return result;
    }
    return MISTAKE;
}

int Solution() {
    ll n = 0, k = 0;
    if (scanf("%lld %lld", &n, &k) != 2) {
        printf("Error: input is not valid\n");
        return -1;
    
    }
    ll* arr = malloc(n * sizeof(ll));
    for (ll i = 0; i < n; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            printf("Error: input is not valid\n");
            return -1;
        }
    }

    ll left = 0, right = INT_MAX, mid = 0;
    MergeSort(arr, n);

    printf("%lld\n", GetAnswer(arr, left, right, mid, n, k));

    return SUCCESS;
}

int main() {
    if (Solution() == MISTAKE) {
        printf("Error: input is not valid\n");
        return -1;
    }
}