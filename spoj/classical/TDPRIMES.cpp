#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

const int N_MAX = 100000000;
const int N_SQRT = 10000;
const int P_SQRT = 1300;
const int B_SIZE = 10000;

std::bitset<(N_SQRT >> 1) + 1> sieve;
int primes[P_SQRT], pos[P_SQRT], mark[(B_SIZE >> 1) + 1];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int pn = 0;
    for (int i = 3; i <= N_SQRT; i += 2)
        if (!sieve[i >> 1]) {
            primes[pn] = i;
            pos[pn++] = i * i;
            for (int j = i * i; j <= N_SQRT; j += i << 1)
                sieve[j >> 1] = 1;
        }
    int shift = 0, cnt = 0, loop = 0;
    std::cout << 2 << '\n';
    for (int l = 3, r = B_SIZE; l <= N_MAX; r = std::min(r + B_SIZE, N_MAX)) {
        ++loop;
        for (int i = 0; i < pn; ++i)
            while (pos[i] <= r) {
                mark[(pos[i] - shift) >> 1] = loop;
                pos[i] = pos[i] + (primes[i] << 1);
            }
        while (l <= r) {
            if (mark[(l - shift) >> 1] != loop) {
                if (++cnt == 100) {
                    std::cout << l << '\n';
                    cnt = 0;
                }
            }
            l = l + 2;
        }
        shift = shift + B_SIZE;
    }
}