#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int N = 5e4 + 10;
const int P = 7000;
const int MOD = 1e9 + 7;

std::bitset<N> sieve;
int primes[P];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (int i = 2; i * i < N; ++i)
        if (!sieve[i])
            for (int j = i * i; j < N; j += i)
                sieve[j] = true;
    int pn = 0;
    for (int i = 2; i < N; ++i)
        if (!sieve[i]) {
            primes[pn++] = i;
        }
    std::cerr << "pn = " << pn << '\n';
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        int ans = 1;
        for (int i = 0; i < pn && primes[i] <= n; ++i) {
            int p = primes[i];
            int sum = 0, tmp = 1;
            while (1LL * tmp * p <= n) {
                tmp *= p;
                sum += n / tmp;
            }
            ans = 1LL * ans * (sum + 1) % MOD;
        }
        std::cout << ans << '\n';
    }
}