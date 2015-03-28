#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

const unsigned SQRT = 1e4;
const unsigned MAX_SQRT_P = 1300;
const unsigned MAX_Q = 5555;
const unsigned MAX_P = 6e6;
const unsigned BLOCK = 16000;

std::bitset<(SQRT >> 1)> sieve;
unsigned pos[MAX_SQRT_P], mark[BLOCK >> 1], primes[MAX_P], ans[MAX_Q], cnt[MAX_SQRT_P], pmax[SQRT];
unsigned *sqrt_pos = primes, *n_pos = primes, *prev[SQRT];
std::vector<std::pair<unsigned, unsigned> > fact[SQRT];
std::pair<unsigned, std::pair<unsigned, unsigned> > queries[MAX_Q];

inline
unsigned xmod(unsigned a, unsigned b, unsigned m) {    
    return 1ULL * a * b >= m ? 1ULL * a * b % m : a * b;
}

inline
unsigned pmod(unsigned a, unsigned b, unsigned m) {
    unsigned r = 1;
    while (b) {
        if (b & 1) {
            r = xmod(r, a, m);
        }
        b >>= 1;
        a = xmod(a, a, m);
    }
    return r;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    unsigned tt;
    std::cin >> tt;
    for (unsigned i = 0; i < tt; ++i) {
        unsigned n, m;
        std::cin >> n >> m;
        queries[i] = std::make_pair(n, std::make_pair(m, i));
    }
    std::sort(queries, queries + tt);    
    unsigned pn = 0;
    primes[pn++] = 2;
    for (unsigned i = 3; i < SQRT; i += 2)
        if (!sieve[i >> 1]) {
            primes[pn] = i;
            for (pos[pn] = i * i; pos[pn] < SQRT; pos[pn] += i << 1) {
                sieve[pos[pn] >> 1] = 1;
            }
            ++pn;
        }
    unsigned max_n = queries[tt - 1].first + 50;
    unsigned loop = 0, shift = SQRT;
    unsigned pz = pn;
    std::cerr << "cnt = " << pz << '\n';
    for (unsigned l = SQRT + 1, r = std::min(max_n, SQRT + BLOCK - 1); l <= max_n; r = std::min(r + BLOCK, max_n)) {
        ++loop;
        for (unsigned i = 1; i < pz; ++i) {
            while (pos[i] <= r) {
                mark[(pos[i] - shift) >> 1] = loop;
                pos[i] += primes[i] << 1;
            }
        }
        while (l <= r) {
            if (mark[(l - shift) >> 1] != loop) {
                primes[pn++] = l;
            }
            l += 2;
        }
        shift += BLOCK;        
    }
    std::cerr << "pn = " << pn << '\n';
    for (unsigned i = 0; i < pz; ++i) {
        unsigned p = primes[i];
        unsigned v = 1;
        while (v * p < SQRT) {
            v = v * p;
            for (unsigned j = v; j < SQRT; j += v) {
                if (fact[j].empty() || fact[j].back().first != i) {
                    fact[j].push_back(std::make_pair(i, 1));
                } else {
                    ++fact[j].back().second;
                }
                pmax[j] = i;
            }
        }
    }
    for (unsigned i = 1; i < SQRT; ++i)
        if (pmax[i] < pmax[i - 1]) {
            pmax[i] = pmax[i - 1];
        }
    std::fill(prev, prev + SQRT, &primes[0]);
    unsigned z = 0;
    for (unsigned tn = 0; tn < tt; ++tn) {
        unsigned n = queries[tn].first;
        unsigned m = queries[tn].second.first;
        unsigned Lm = unsigned(2e9) / m * m;
        unsigned r = 1;
        while (z * z <= n) ++z;
        unsigned s = std::min(5 * z, n);
        sqrt_pos = std::upper_bound(sqrt_pos, primes + pn, s);
        if (n_pos < sqrt_pos) n_pos = sqrt_pos;
        n_pos = std::upper_bound(n_pos, primes + pn, n);
        unsigned* last = n_pos;
        unsigned zmax = 0;
        for (unsigned i = 1; last > sqrt_pos; ++i) {
            if (prev[i] < sqrt_pos) prev[i] = sqrt_pos;
            prev[i] = std::upper_bound(prev[i], last, n / (i + 1));
            if (last > prev[i]) {
                zmax = i + 1;
                for (unsigned j = 0; j < fact[i + 1].size(); ++j) {
                    cnt[fact[i + 1][j].first] += fact[i + 1][j].second * (last - prev[i]);
                }
            }
            last = prev[i];
        }
        zmax = pmax[zmax];
        for (unsigned i = 0; i <= zmax; ++i)
            if (cnt[i] > 0) {
                r = xmod(r, pmod(primes[i], cnt[i], Lm), Lm);
                cnt[i] = 0;
            }        
        for (unsigned* i = primes; i < sqrt_pos; ++i) {
            unsigned p = *i;
            unsigned sum = 0, tmp = 1;
            while (1ULL * tmp * p <= n) {
                tmp *= p;
                sum += n / tmp;
            }
            r = xmod(r, sum + 1, Lm);
        }
        ans[queries[tn].second.second] = r % m;
    }
    for (unsigned i = 0; i < tt; ++i) {
        std::cout << ans[i] << '\n';
    }
}
