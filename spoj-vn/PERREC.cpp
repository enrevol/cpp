#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N = 2345;

bool s[N][N];
int dp[N][N], st[15][N], sum[N];

int solve(int i, int f, int t, int l) {
    if (f > t) return 0;
    int k = __lg(t - f + 1);
    int x = st[k][f];
    int y = st[k][t - (1 << k) + 1];
    int m = dp[i][x] < dp[i][y] ? x : y;
    return solve(i, f, m - 1, dp[i][m]) + solve(i, m + 1, t, dp[i][m]) + (dp[i][m] > l && sum[t] - sum[f - 1] > 0);
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int n, m, x, a, b, y, c, d;
    cin >> n >> m >> x >> a >> b >> y >> c >> d;
    x %= n;
    y %= n;
    for (int i = 0; i < m; ++i) {
        s[x + 1][y + 1] = true;
        x = (x * a + b) % n;
        y = (y * c + d) % n;
    }
    for (int j = 1; j <= n; ++j)
        for (int i = n; i >= 1; --i) 
            if (!s[i][j]) {
                dp[i][j] = dp[i + 1][j] + 1;
            }
    for (int i = 1; i <= n; ++i) {
        s[0][i] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            st[0][j] = j;
            sum[j] = sum[j - 1] + s[i - 1][j];
        }
        for (int k = 1; 1 << k <= n; ++k)   
            for (int j = 1; j + (1 << k) - 1 <= n; ++j) {
                int x = st[k - 1][j];
                int y = st[k - 1][j + (1 << (k - 1))];
                st[k][j] = dp[i][x] < dp[i][y] ? x : y;
            }
        ans += solve(i, 1, n, 0);
    }
    cout << ans;
}
