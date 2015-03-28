#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N = 2510;
const int MAX = 1000010;

int a[N], dp[N][N], _idx[MAX << 1], *idx = _idx + MAX;

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                int val = a[i] - a[j];
                dp[i][j] = 2;
                if (-MAX < val && val < MAX && idx[val] > 0) {
                    dp[i][j] = dp[j][idx[val]] + 1;
                }
                ans = max(ans, dp[i][j]);
                idx[a[j]] = j;
            }
            for (int j = 1; j < i; ++j) {
                idx[a[j]] = 0;
            }
        }
        cout << ans << '\n';
    }
}