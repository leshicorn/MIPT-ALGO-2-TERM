#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int start;
    int end;
} Interval;

int cmpfunc(const void* first, const void* second) {
    Interval* interval1 = (Interval*)first;
    Interval* interval2 = (Interval*)second;
    if (interval1->start == interval2->start) {
        return interval1->end - interval2->end;
    }
    return interval1->start - interval2->start;
}

void mergeIntervals(Interval* intervals, int n) {
    qsort(intervals, n, sizeof(Interval), cmpfunc);

    int index = 0;
    for (int i = 1; i < n; i++) {
        if (intervals[index].end >= intervals[i].start) {
            if (intervals[index].end < intervals[i].end) {
                intervals[index].end = intervals[i].end;
            }
        } else {
            index++;
            intervals[index] = intervals[i];
        }
    }

    printf("%d\n", index + 1);
    for (int i = 0; i <= index; i++) {
        printf("%d %d\n", intervals[i].start, intervals[i].end);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Invalid input format");
        return -1;
    }

    Interval* intervals = malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &intervals[i].start, &intervals[i].end) != 2) {
            printf("Invalid input format");
            return -1;
        }
    }

    mergeIntervals(intervals, n);

    free(intervals);
    return 0;
}
