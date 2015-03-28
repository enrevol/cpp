#include <algorithm>
#include <cmath>
#include <iostream>

const int MAX_Q = 500;
const int MOD = 1e9 + 7;

std::pair<int, int> queries[MAX_Q];
int ans[MAX_Q];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int tt;    
    std::cin >> tt;
    for (int i = 0; i < tt; ++i) {
        std::cin >> queries[i].first;
        queries[i].second = i;
    }
    std::sort(queries, queries + tt);
    for (int i = 0, s = 0; i < tt; ++i) {
        int n = queries[i].first;
        while ((s + 1) * (s + 1) < n) ++s;
        long long res = 0;
        for (int i = 1; i <= s; ++i) {
            res = res + n / i * i;
        }
        int r = n;
        for (int i = 1; r > s; ++i) {
            int l = n / (i + 1) + 1;
            int c = ((1LL * (r + l) * (r - l + 1)) >> 1) % MOD;
            res = res + 1LL * c * i;
            r = l - 1;
        }
        ans[queries[i].second] = res % MOD;
    }
    for (int i = 0; i < tt; ++i) {
        std::cout << ans[i] << '\n';
    }
}
