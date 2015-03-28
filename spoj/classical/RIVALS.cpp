#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 2000010;
const int MOD = 1e9 + 7;

int f[N];

int pow_mod(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) r = 1LL * r * a % MOD;
        b >>= 1;
        a = 1LL * a * a % MOD;
    }
    return r;
}

int main() {
    f[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = 1LL * f[i - 1] * i % MOD;
    }
    int tt;
    std::cin >> tt;
    while (tt--) {
        int x, y;
        std::cin >> x >> y;
        int r = 1LL * f[x + y] * pow_mod(1LL * f[x] * f[y] % MOD, MOD - 2) % MOD;
        std::cout << r << '\n';
    }
}