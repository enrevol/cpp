#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 100010;
const int MOD = 1e9 + 7;

int dp[N];
vector<int> adj[N];

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            if (u > v) {
                continue;
            }
            adj[v].push_back(u);
        }
        memset(dp, 0, sizeof(dp));
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int v : adj[i]) {
                dp[i] = (dp[i] + dp[v]) % MOD;
            }
        }
        cout << "Case " << tn << ": " << dp[n] << '\n';
    }
}