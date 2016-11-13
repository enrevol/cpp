#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MOD = 1e9 + 7;

int f[46];

int bin_exp(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1)
            r = 1LL * a * r % MOD;
        b >>= 1;
        a = 1LL * a * a % MOD;
    }
    return r;
}

int fib(int n) {
    int k = std::__lg(n) + 1;
    int a = 0, b = 1;
    while (k--) {
        int d = 1LL * a * (2LL * b - a + MOD) % MOD;
        int e = (1LL * a * a + 1LL * b * b) % MOD;
        a = d;
        b = e;
        if ((n >> k) & 1) {
            int c = (a + b) % MOD;
            a = b;
            b = c;
        }
    }
    return a;
}

int main() {
    //    freopen("in", "r", stdin);
    f[1] = f[2] = 1;
    for (int i = 3; i < 46; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    int tn;
    scanf("%d", &tn);
    while (tn--) {
        int n;
        scanf("%d", &n);
        int a = n;
        int b = fib(n);
        for (int i = 1; i < 45 && f[i] <= a; ++i) {
            while (f[i + 1] <= a) {
                ++i;
            }
            while (a - (i - 1) < n) {
                ++a;
            }
        }
        int r = bin_exp(a, b);
        printf("%d\n", r);
    }
}
