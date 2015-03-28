#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int N = 510;
const int MOD = 1e9 + 7;
 
int a[N], fact[N], deg[N], parent[N], subsz[N], dp[N], bi[N][N];
std::vector<int> ed[N], ev[N];
 
int pmod(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1) r = 1LL * r * a % MOD;
    a = 1LL * a * a % MOD;
    b >>= 1;
  }
  return r;
}
 
int nCk(int n, int k) {
  if (bi[n][k]) return bi[n][k];
  assert(n < N && k < N && k <= n);
  return bi[n][k] = 1LL * fact[n] * pmod(1LL * fact[k] * fact[n - k] % MOD, MOD - 2) % MOD;
}
 
int dfs_tree(int u, int p) {
  int cost = a[u];
  subsz[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p || ed[v].size() == 1) continue;
    cost += dfs_tree(v, u);
    subsz[u] += subsz[v];
  }
  dp[u] = 1;
  int cnt = subsz[u] - 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p || ed[v].size() == 1) continue;
    dp[u] = 1LL * dp[u] * nCk(cnt, subsz[v]) % MOD * dp[v] % MOD;
    cnt -= subsz[v];
  }
  return cost;
}
 
int dfs(int u) {
  int cost = a[u];
  subsz[u] = 1;
  for (int i = 0; i < int(ev[u].size()); ++i) {
    int v = ev[u][i];
    if (ev[v].empty()) continue;
    cost += dfs(v);
    subsz[u] += subsz[v];
  }
  dp[u] = 1;
  int cnt = subsz[u] - 1;
  for (int i = 0; i < int(ev[u].size()); ++i) {
    int v = ev[u][i];
    if (ev[v].empty()) continue;
    dp[u] = 1LL * dp[u] * nCk(cnt, subsz[v]) % MOD * dp[v] % MOD;
    cnt -= subsz[v];
  }
  return cost;
}
 
struct cmp {
  bool operator()(int u, int v) {
    if (deg[u] != deg[v]) return deg[u] < deg[v];
    return u < v;
  }
};
 
std::set<int, cmp> myset;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  fact[0] = 1;
  for (int i = 1; i < N; ++i) {
    fact[i] = 1LL * fact[i - 1] * i % MOD;
  }
  int tt;
  scanf("%d", &tt);
  for (int tn = 1; tn <= tt; ++tn) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      ed[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      ed[u].push_back(v);
      ed[v].push_back(u);
    }
    int building = 0;
    int cost = 0;
    int ways = 0;
    if (m > n - 1) {
      memset(parent, 0, sizeof(parent));
      myset.clear();
      for (int u = 1; u <= n; ++u) {
        deg[u] = ed[u].size();
        ev[u].clear();
        myset.insert(u);
      }
      while (!myset.empty()) {
        int u = *myset.begin();        
        if (deg[u] > 1) break;
        myset.erase(u);
        int z = 0;
        for (int i = 0; i < int(ed[u].size()); ++i) {
          int v = ed[u][i];
          if (!parent[v]) {
            z = v;
          }
        }
        assert(z > 0);
        ev[z].push_back(u);
        parent[u] = z;
        myset.erase(z);
        --deg[z];
        myset.insert(z);
      }
      int cnt = 0;
      ways = 1;
      for (int u = 1; u <= n; ++u)
        if (!parent[u]) {
          if (!ev[u].empty()) {
            cost += dfs(u);
            cnt += subsz[u];
          }
          ++building;
        }
      assert(building == int(myset.size()));
      for (int u = 1; u <= n; ++u)
        if (!parent[u] && !ev[u].empty()) {
          ways = 1LL * ways * nCk(cnt, subsz[u]) % MOD * dp[u] % MOD;
          cnt -= subsz[u];
        }
    } else {
      building = 1;
      for (int root = 1; root <= n; ++root) {
        int ncost = 0;
        ncost += dfs_tree(root, 0);
        int nways = 1;
        int sz = subsz[root] - 1;
        for (int i = 0; i < int(ed[root].size()); ++i) {
          int u = ed[root][i];
          if (ed[u].size() == 1) continue;
          nways = 1LL * nways * nCk(sz, subsz[u]) % MOD * dp[u] % MOD;
          sz -= subsz[u];
        }
        assert(sz == 0);
        if (ncost == cost) {
          ways = (ways + nways) % MOD;
        } else if (cost == 0 || ncost < cost) {
          cost = ncost;
          ways = nways;
        }
      }
    }
    printf("Case #%d: %d %d %d\n", tn, building, cost, ways);
  }
} 