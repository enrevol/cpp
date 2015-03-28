#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 1e5;
const int MAX = 1e7;

std::bitset<(MAX >> 1) + 1> sieve;
long long a, b, phi[N], val[N];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    long long a, b;
    std::cin >> a >> b;
    for (int i = 0; i <= b - a; ++i) {
        val[i] = phi[i] = a + i;
    }
    int z = a & 1;
    while (z <= b - a) {
        phi[z] >>= 1;
        while ((val[z] & 1) == 0) {
            val[z] >>= 1;
        }
        z = z + 2;
    }
    for (int i = 3; i * i <= MAX; i += 2)
        if (!sieve[i >> 1])
            for (int j = i * i; j <= MAX; j += i << 1)
                sieve[j >> 1] = 1;
    for (int i = 3; i <= MAX; i += 2)
        if (!sieve[i >> 1]) {
            int z = ((a - 1) / i + 1) * i - a;
            while (z <= b - a) {
                phi[z] = phi[z] / i * (i - 1);
                while (val[z] % i == 0) {
                    val[z] = val[z] / i;
                }
                z = z + i;
            }
        }
    for (int i = 0; i <= b - a; ++i) {
        long long ans = phi[i];
        if (val[i] > 1) {
            ans = ans / val[i] * (val[i] - 1);
        }
        std::cout << ans << '\n';
    }
}