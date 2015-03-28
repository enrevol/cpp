#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 123456;

int a[N], L[20], len[1 << 20], st_min[17][N], st_max[17][N];
long long dp[1 << 20];

inline
int query(int f, int t) {
    int k = std::__lg(t - f + 1);
    int x = std::max(st_max[k][f], st_max[k][t - (1 << k) + 1]);
    int y = std::min(st_min[k][f], st_min[k][t - (1 << k) + 1]);
    return x - y;
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        st_min[0][i] = st_max[0][i] = a[i];
    }
    for (int j = 1; 1 << j <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st_min[j][i] = std::min(st_min[j - 1][i], st_min[j - 1][i + (1 << (j - 1))]);
            st_max[j][i] = std::max(st_max[j - 1][i], st_max[j - 1][i + (1 << (j - 1))]);
        }
    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> L[i];
    }
    std::sort(L, L + k, std::greater<int>());
    while (k > 0 && L[k - 1] == 0) --k;
    for (int mask = 1; mask < 1 << k; ++mask) {
        for (int i = 0; i < k; ++i)
            if ((mask >> i) & 1) {
                len[mask] = len[mask] + L[i];
                int n_mask = mask ^ (1 << i);
                long long x = dp[n_mask] + 1LL * L[i] * query(len[n_mask] + 1, len[n_mask] + L[i]);
                if (x > dp[mask]) {
                    dp[mask] = x;
                }
            }
    }
    std::cout << dp[(1 << k) - 1];
}