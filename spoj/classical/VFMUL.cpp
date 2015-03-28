#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const uint32_t N = 300000;
const uint32_t MOD = (1U << 20) * 100 + 1;

char sa[N], sb[N], answer[N * 2];
uint32_t rev[1 << 20], x[1 << 20], y[1 << 20];
uint32_t pa[1 << 20], pb[1 << 20];

uint32_t pow_mod(uint32_t a, uint32_t b) {
    uint32_t r = 1;
    while (b) {
        if (b & 1) r = uint64_t(r) * a % MOD;
        b >>= 1;
        a = uint64_t(a) * a % MOD;
    }
    return r;
}

void fft(uint32_t* input, uint32_t n, bool invert) {
    uint32_t dig = 0;
    while ((1U << dig) < n) {
        ++dig;
    }
    for (uint32_t i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (dig - 1));
        if (rev[i] > i) {
            swap(input[i], input[rev[i]]);
        }
    }
    for (uint32_t L = 1; L <= dig; ++L) {
        uint32_t len = 1U << L;
        uint32_t k = (MOD - 1) / len;
        uint32_t w = pow_mod(3, k);
        if (invert) {
            w = pow_mod(w, MOD - 2);
        }
        x[0] = 1;
        y[0] = (uint64_t(x[0]) << 32) / MOD;
        for (uint32_t i = 1; i < len / 2; ++i) {
            x[i] = uint64_t(x[i - 1]) * w % MOD;
            y[i] = (uint64_t(x[i]) << 32) / MOD;
        }
        for (uint32_t i = 0; i < n; i += len) {
            for (uint32_t j = 0; j < len / 2; ++j) {
                uint32_t a = input[i + j];
                uint32_t z = input[i + j + len / 2];
                uint32_t q = (uint64_t(y[j]) * z) >> 32;
                uint32_t b = uint64_t(x[j]) * z - uint64_t(q) * MOD;
                input[i + j] = a + b;
                input[i + j + len / 2] = a + MOD - b;
            }
        }
    }
    if (invert) {
        uint32_t inv = pow_mod(n, MOD - 2);
        for (uint32_t i = 0; i < n; ++i) {
            input[i] = uint64_t(input[i]) * inv % MOD;
        }
    }
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    uint32_t tt;
    scanf("%u", &tt);
    while (tt--) {
        scanf("%s %s", sa, sb);
        uint32_t na = strlen(sa);
        uint32_t nb = strlen(sb);
        uint32_t n = na + nb;
        uint32_t size = 1;
        while (size < n) {
            size <<= 1;
        }
        for (uint32_t i = 0; i < na; ++i) {
            pa[i] = sa[na - 1 - i] - '0';
        }
        for (uint32_t i = 0; i < nb; ++i) {
            pb[i] = sb[nb - 1 - i] - '0';
        }
        std::fill(pa + na, pa + size, 0);
        std::fill(pb + nb, pb + size, 0);
        fft(pa, size, false);
        fft(pb, size, false);
        for (uint32_t i = 0; i < size; ++i) {
            pa[i] = uint64_t(pa[i]) * pb[i] % MOD;
        }
        fft(pa, size, true);
        uint32_t carry = 0;
        for (uint32_t i = 0; i < n; ++i) {
            carry += pa[i];
            answer[n - 1 - i] = carry % 10 + '0';
            carry /= 10;
        }
        answer[n] = 0;
        uint32_t pos = 0;
        while (pos + 1 < n && answer[pos] == '0') {
            ++pos;
        }
        puts(answer + pos);
    }
}