#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int n, k;
static int pos[55];
static long long prefix[55];
static long long memo[55][12][55];
static char visited[55][12][55];

long long dp(int i, int skips, int last) {
    if (i == n - 1) {
        return skips == 0 ? 0 : LLONG_MAX / 2;
    }
    if (visited[i][skips][last]) return memo[i][skips][last];
    visited[i][skips][last] = 1;

    long long rate = prefix[i] - (last > 0 ? prefix[last - 1] : 0);
    int end = i + skips + 1;
    if (end > n - 1) end = n - 1;

    long long res = LLONG_MAX / 2;
    for (int j = i + 1; j <= end; j++) {
        long long distance = pos[j] - pos[i];
        long long sub = dp(j, skips - (j - i - 1), i + 1);
        long long cost = distance * rate + sub;
        if (cost < res) res = cost;
    }

    memo[i][skips][last] = res;
    return res;
}

int minTravelTime(int l, int nSize, int kVal, int* position, int positionSize, int* time, int timeSize) {
    n = nSize;
    k = kVal;
    for (int i = 0; i < n; i++) pos[i] = position[i];

    prefix[0] = time[0];
    for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + time[i];

    memset(visited, 0, sizeof(visited));

    return (int) dp(0, k, 0);
}