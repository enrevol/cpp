#include <algorithm>
#include <cassert>
#include <bitset>
#include <iostream>

const int N = 1e4 + 10;
const int L = 1e4;
const int Q = 1e5 + 10;

std::bitset<N> sieve;
std::pair<int, int> queries[Q];
int ans[Q], partial[Q], primes[N], pos[N], mark[L >> 1];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tt, mod;
    std::cin >> tt >> mod;
    for (int i = 0; i < tt; ++i) {
        int n;
        std::cin >> n;
        queries[i] = { n, i };
    }
    auto xmod = [=] (int a, int b) {
        return 1LL * a * b >= mod ? 1LL * a * b % mod : a * b;
    };
    std::sort(queries, queries + tt);
    std::fill(partial, partial + tt, 1);
    int max_n = queries[tt - 1].first;
    auto process = [max_n, tt, &xmod] (int d) {
        int prod = 1;
        int pos = 0;
        while (1LL * prod * d <= max_n) {            
            prod = prod * d;
            for (int l = pos, r = tt - 1; l <= r; ) {
                int m = (l + r) >> 1;
                if (prod <= queries[m].first) {
                    pos = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            partial[pos] = xmod(partial[pos], d);
        }
    };
    int pn = 0;
    for (int i = 2; i < N; ++i)
        if (!sieve[i]) {
            primes[pn] = i;
            pos[pn++] = i * i;
            for (int j = i * i; j < N; j += i)
                sieve[j] = 1;
        }
    std::cerr << "pn = " << pn << '\n';
    process(2);
    int shift = 2, loop = 0;
    for (int l = 3, r = std::min(max_n, L + 1); l <= max_n; r = std::min(r + L, max_n)) {        
        ++loop;
        for (int i = 1; i < pn; ++i) {
            while (pos[i] < l) {
                pos[i] += primes[i] << 1;
            }
            while (pos[i] <= r) {
                mark[(pos[i] - shift) >> 1] = loop;
                pos[i] += primes[i] << 1;
            }
        }
        while (l <= r) {
            if (mark[(l - shift) >> 1] != loop) {
                process(l);
            }
            l += 2;
        }
        shift += L;
    }
    for (int i = 0, val = 1; i < tt; ++i) {
        ans[queries[i].second] = val = xmod(val, partial[i]);
    }
    for (int i = 0; i < tt; ++i) {
        std::cout << ans[i] << '\n';
    }
}