#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <unordered_map>

#define uint32_t uint64_t

namespace eratos {

const uint32_t N_MAX = 100000000;
const uint32_t P_MAX = 6000000;
const uint32_t N_SQRT = 10000;
const uint32_t P_SQRT = 1300;
const uint32_t B_SIZE = 10000;

uint32_t pn, primes[P_MAX];
uint32_t pos[P_SQRT], mark[(B_SIZE >> 1) + 1];
std::bitset<(N_SQRT >> 1) + 1> sieve;

void process() {
    primes[pn++] = 2;
    for (uint32_t i = 3; i <= N_SQRT; i += 2)
        if (!sieve[i >> 1]) {
            primes[pn] = i;
            pos[pn++] = i * i;            
            for (uint32_t j = i * i; j <= N_SQRT; j += i << 1)
                sieve[j >> 1] = 1;
        }
    uint32_t cnt = pn, shift = 0, loop = 0;
    pn = 1;
    for (uint32_t l = 3, r = std::min(B_SIZE, N_MAX); l <= N_MAX; r = std::min(r + B_SIZE, N_MAX)) {
        ++loop;
        for (uint32_t i = 1; i < cnt; ++i)
            while (pos[i] <= r) {
                mark[(pos[i] - shift) >> 1] = loop;
                pos[i] = pos[i] + (primes[i] << 1);
            }
        while (l <= r) {
            if (mark[(l - shift) >> 1] != loop) {
                primes[pn++] = l;
            }
            l += 2;
        }
        shift = shift + B_SIZE;
    }
    std::cerr << "pn = " << pn << '\n';
}

}

namespace lehmer {

const uint32_t N_MAX = 10000000;
const uint32_t A_MAX = 1234;

uint32_t cnt[N_MAX + 1];
std::unordered_map<uint64_t, uint64_t> phi_cache[A_MAX + 1];

uint32_t root2(uint64_t x) {
    uint32_t r = pow(x, 1.0 / 2); // sqrt(double(x));
    while (1ULL * r * r < x) ++r;
    while (1ULL * r * r > x) --r;
    return r;
}

uint32_t root3(uint64_t x) {
    uint32_t r = pow(x, 1.0 / 3);
    while (1ULL * r * r * r < x) ++r;
    while (1ULL * r * r * r > x) --r;
    return r;
}

uint32_t root4(uint64_t x) {
    uint32_t r = pow(x, 1.0 / 4);
    while (1ULL * (r * r) * (r * r) < x) ++r;
    while (1ULL * (r * r) * (r * r) > x) --r;
    return r;
}

uint64_t phi(uint64_t x, uint32_t a) {
    if (a == 1) return (x + 1) >> 1;
    assert(a <= A_MAX);
    auto ite = phi_cache[a].find(x);
    if (ite != phi_cache[a].end())
        return ite->second;
    return phi_cache[a][x] = phi(x, a - 1) - phi(x / eratos::primes[a - 1], a - 1);
}

uint64_t pi(uint64_t x) {
    if (x <= N_MAX) return cnt[x];
    uint32_t a = pi(root4(x));
    uint32_t b = pi(root2(x));
    uint32_t c = pi(root3(x));
    uint64_t res = phi(x, a) + ((1ULL * (b + a - 2) * (b - a + 1)) >> 1);
    for (uint32_t i = a + 1; i <= b; ++i) {
        uint64_t w = x / eratos::primes[i - 1];        
        res = res - pi(w);
        if (i <= c) {
            uint32_t lim = pi(root2(w));
            for (uint32_t j = i; j <= lim; ++j)
                res = res - pi(w / eratos::primes[j - 1]) + (j - 1);
        }
    }
    return res;
}

void process() {
    for (uint32_t i = 1, j = 0; i <= N_MAX; ++i) {
        while (eratos::primes[j] <= i) ++j;
        cnt[i] = j;
    }
}

}

inline
uint64_t add(uint64_t a, uint64_t b, uint64_t m) {
    return a + b >= m ? a + b - m : a + b;
}

uint64_t mul(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t r = 0;
    while (b) {
        if (b & 1) {
            r = add(r, a, m);
        }
        b >>= 1;
        a = add(a, a, m);
    }
    return r;
}

uint64_t pow_mod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t r = 1;
    while (b) {
        if (b & 1) {
            r = mul(r, a, m);
        }
        b >>= 1;
        a = mul(a, a, m);
    }
    return r;
}

void solve() {
    uint32_t tt;
    std::cin >> tt;
    for (uint32_t i = 0; i < tt; ++i) {
        uint64_t n, m;
        std::cin >> n >> m;
        uint32_t s = lehmer::root2(n);
        uint64_t result = 1;
        uint64_t last = n, last_pi = lehmer::pi(last);
        for (uint32_t i = 1; i < s; ++i) {
            uint64_t v = n / (i + 1);
            uint64_t p = lehmer::pi(v);
            uint64_t c = last_pi - p;
            result = mul(result, pow_mod(i + 1, c, m), m);
            last = v;
            last_pi = p;
        }
        for (uint32_t i = 0; eratos::primes[i] <= last; ++i) {
            uint32_t p = eratos::primes[i];
            uint64_t sum = 0, tmp = 1;
            while (tmp * p <= n) {
                tmp = tmp * p;
                sum = sum + n / tmp;
            }
            result = mul(result, sum + 1, m);
        }
        std::cout << result % m << '\n';
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    eratos::process();
    lehmer::process();
    solve();
}