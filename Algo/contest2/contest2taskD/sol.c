#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 200000

typedef struct {
    int x, y1, y2;
} GasStation;

GasStation stations[MAX_N];
int n, y, x;

bool can_reach(int tank, int i)
{
    int queue[2 * MAX_N];
    int head = 0, tail = 0;
    bool visited[y + 1][x + 1];

    for (int j = 0; j <= y; j++) {
        for (int k = 0; k <= x; k++) {
            visited[j][k] = false;
        }
    }

    // add starting point
    visited[i][0] = true;
    queue[tail++] = i;
    queue[tail++] = 0;

    while (head != tail) {
        int y = queue[head++];
        int x = queue[head++];

        if (x == stations[n - 1].x && y == i) {
            return true;
        }

        // add reachable gas stations
        for (int j = 0; j < n; j++) {
            if (stations[j].y1 <= y && y <= stations[j].y2) {
                int x_station = stations[j].x;
                int y_station = y;

                if (x_station >= x && x_station - x <= tank) {
                    if (!visited[y_station][x_station]) {
                        visited[y_station][x_station] = true;
                        queue[tail++] = y_station;
                        queue[tail++] = x_station;
                    }
                }
            }
        }

        // add next point on the road
        int x_next = x + tank;
        if (x_next <= stations[n - 1].x && !visited[y][x_next]) {
            visited[y][x_next] = true;
            queue[tail++] = y;
            queue[tail++] = x_next;
        }
    }

    return false;
}

int main()
{
    scanf("%d %d %d", &n, &y, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &stations[i].x, &stations[i].y1, &stations[i].y2);
    }

    // binary search for minimum tank size for each road
    for (int i = 0; i <= y; i++) {
        int low = 1, high = x;
        while (low < high) {
            int mid = (low + high) / 2;
            if (can_reach(mid, i)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        printf("%d\n", low);
    }

    return 0;
}
