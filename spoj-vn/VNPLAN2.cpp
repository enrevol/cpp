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

const int N = 85;
const int MOD = 1e9 + 7;

int g[N][N], vis[N], bi[N][N], fact[N], d[N], c[N];
std::vector<int> cc[N];

void dfs(int u, int id, int n) {
  if (vis[u]) return;
  vis[u] = 1;
  cc[id].push_back(u);
  for (int v = 1; v <= n; ++v)
    if (g[u][v]) dfs(v, id, n);
}

inline int pmod(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1) r = 1LL * a * r % MOD;    
    a = 1LL * a * a % MOD;
    b >>= 1;
  }
  return r;
}

inline int nCk(int n, int k) {
  if (bi[n][k]) return bi[n][k];
  return bi[n][k] = 1LL * fact[n] * pmod(1LL * fact[n - k] * fact[k] % MOD, MOD - 2) % MOD;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  fact[0] = 1;
  for (int i = 1; i < N; ++i) {
    fact[i] = 1LL * fact[i - 1] * i % MOD;
    d[i] = pmod(2, i * (i - 1));
    int v = 0;
    for (int j = 1; j < i; ++j) {
      v = (v + 1LL * j * nCk(i, j) % MOD * c[j] % MOD * d[i - j] % MOD) % MOD;
    }
    v = 1LL * v * pmod(i, MOD - 2) % MOD;
    c[i] = (d[i] - v) % MOD;
  }
  int n;
  scanf("%d", &n);  
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", g[i] + j);
  int cc_cnt = 0;
  int ans = 1;
  for (int u = 1; u <= n; ++u)
    if (!vis[u]) dfs(u, ++cc_cnt, n);
  fprintf(stderr, "cc_cnt = %d\n", cc_cnt);
  for (int i = 1; i <= cc_cnt; ++i) {
    int sz = cc[i].size();
    if (sz == 1) continue;
    ans = 1LL * ans * c[sz] % MOD;
  }
  if (ans < 0) ans += MOD;
  printf("%d", ans);
}
