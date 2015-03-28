#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

constexpr uint32_t MOD = 100003;
constexpr uint32_t R = 171793;

uint32_t f[MOD], inv[MOD];

uint32_t fast_mod(uint64_t x) {
    uint32_t t = x - ((x * R) >> 34) * MOD;
    return t < MOD ? t : t - MOD;
}

uint32_t nCk(uint32_t n, uint32_t k) {
    return fast_mod(uint64_t(f[n]) * inv[fast_mod(uint64_t(f[n - k]) * f[k])]);
}

uint32_t calc(uint64_t n, uint64_t m) {
    uint32_t result = 1;
    for (uint32_t i = 0; i < 4; ++i) {
        uint32_t x = n % MOD; n /= MOD;
        uint32_t y = m % MOD; m /= MOD;
        if (x < y) return 0;
        result = fast_mod(uint64_t(result) * nCk(x, y));
    }
    return result;
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    f[0] = 1;
    for (uint32_t i = 1; i < MOD; ++i) {
        f[i] = fast_mod(uint64_t(f[i - 1]) * i);
    }
    inv[1] = 1;
    for (uint32_t i = 2; i < MOD; ++i) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }
    uint32_t tt;
    cin >> tt;
    while (tt--) {
        uint64_t m, n;
        cin >> m >> n;
        if (m < (n - 1) * 2 + 1) {
            cout << 0 << '\n';
        } else {
            m -= (n - 1) * 2 + 1;
            uint32_t answer = calc(n + m, n);
            cout << answer << '\n';
        }
    }
}
