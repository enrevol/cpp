#include <algorithm>
#include <cassert>
#include <iostream>

const int N = 2e5;

int a[N], b[N], f[N];

int main() {
//    assert(freopen("input.txt", "r", stdin));
//    assert(freopen("output.txt", "w", stdout));
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            b[i] = a[i];
        }
        std::sort(b, b + N);
        int m = std::unique(b, b + N) - b;
        long long ans = 0;
        std::fill(f, f + m, 0);
        for (int i = 0; i < n; ++i) {
            a[i] = std::lower_bound(b, b + m, a[i]) - b;            
            for (int j = a[i] + 1; j <= m; j += j & -j) {
                ans += f[j - 1];
            }
            for (int j = a[i] + 1; j > 0; j &= j - 1) {
                ++f[j - 1];
            }
        }
        std::cout << ans << '\n';
    }
}