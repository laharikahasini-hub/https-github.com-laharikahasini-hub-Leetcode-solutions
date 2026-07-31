#include <stdlib.h>
#include <string.h>

#define MOD 1000000007LL

static int n, M, K, MAXCARRY;
static long long nums_[55];
static long long fact[35], invFact[35];
static long long ****memo;
static char ****visited;

long long qpow(long long base, long long e) {
    long long result = 1;
    base %= MOD;
    while (e > 0) {
        if (e & 1) result = result * base % MOD;
        base = base * base % MOD;
        e >>= 1;
    }
    return result;
}

long long comb(int a, int b) {
    if (b < 0 || b > a) return 0;
    return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
}

long long dfs(int i, int j, int k, int st) {
    if (k < 0) return 0;
    if (i == n) {
        if (j > 0) return 0;
        int kk = k, s = st;
        while (s > 0) { kk -= (s & 1); s >>= 1; }
        return kk == 0 ? 1 : 0;
    }
    if (st >= MAXCARRY) return 0; // safety bound
    if (visited[i][j][k][st]) return memo[i][j][k][st];
    visited[i][j][k][st] = 1;

    long long res = 0;
    for (int t = 0; t <= j; t++) {
        int nt = t + st;
        int nk = k - (nt & 1);
        long long p = qpow(nums_[i], t);
        long long sub = dfs(i + 1, j - t, nk, nt >> 1);
        long long term = comb(j, t) * p % MOD * sub % MOD;
        res = (res + term) % MOD;
    }

    memo[i][j][k][st] = res;
    return res;
}

int magicalSum(int m, int k, int* nums, int numsSize) {
    n = numsSize;
    M = m;
    K = k;

    for (int i = 0; i < n; i++) nums_[i] = nums[i];

    fact[0] = 1;
    for (int x = 1; x <= m; x++) fact[x] = fact[x - 1] * x % MOD;
    invFact[m] = qpow(fact[m], MOD - 2);
    for (int x = m; x > 0; x--) invFact[x - 1] = invFact[x] * x % MOD;

    MAXCARRY = m / 2 + 2; // carry can't exceed roughly m/2

    memo = (long long****)malloc(sizeof(long long***) * (n + 1));
    visited = (char****)malloc(sizeof(char***) * (n + 1));
    for (int a = 0; a <= n; a++) {
        memo[a] = (long long***)malloc(sizeof(long long**) * (m + 1));
        visited[a] = (char***)malloc(sizeof(char**) * (m + 1));
        for (int b = 0; b <= m; b++) {
            memo[a][b] = (long long**)malloc(sizeof(long long*) * (k + 1));
            visited[a][b] = (char**)malloc(sizeof(char*) * (k + 1));
            for (int c = 0; c <= k; c++) {
                memo[a][b][c] = (long long*)calloc(MAXCARRY, sizeof(long long));
                visited[a][b][c] = (char*)calloc(MAXCARRY, sizeof(char));
            }
        }
    }

    long long ans = dfs(0, m, k, 0);

    for (int a = 0; a <= n; a++) {
        for (int b = 0; b <= m; b++) {
            for (int c = 0; c <= k; c++) {
                free(memo[a][b][c]);
                free(visited[a][b][c]);
            }
            free(memo[a][b]);
            free(visited[a][b]);
        }
        free(memo[a]);
        free(visited[a]);
    }
    free(memo);
    free(visited);

    return (int)ans;
}
