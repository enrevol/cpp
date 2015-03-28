#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

const int N = 1234;

int dp[N][N], best[N];

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        std::memset(dp, -1, sizeof(dp));
        std::memset(best, 0, sizeof(best));
        std::map<int, int> idx;
        int cnt = 0, ans = 0;
        for (int i = 1; i <= n; ++i) {
            int a;
            std::cin >> a;
            if (!idx[a]) {
                idx[a] = ++cnt;
                dp[cnt][0] = 0;
            }
            int k = idx[a];
            for (int j = i - 1; j >= 0; --j) {
                if (dp[k][j] == -1) continue;
                dp[k][j + 1] = std::max(dp[k][j + 1], dp[k][j] + j + 1);
                best[k] = std::max(best[k], dp[k][j + 1]);
            }
            for (int j = 1; j <= cnt; ++j)
                if (j != k) {
                    dp[k][1] = std::max(dp[k][1], best[j] + 1);
                    best[k] = std::max(best[k], dp[k][1]);
                }
            ans = std::max(ans, best[k]);
        }
        std::cout << ans << '\n';
    }
}
