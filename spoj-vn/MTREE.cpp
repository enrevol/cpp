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

const int N = 100010;
const int MOD = 1e9 + 7;

struct edge {
  int v, w;
  edge(int v, int w) : v(v), w(w) { }
};

std::vector<edge> ed[N];

int dfs(int u, int p, int& ans) {
  int r = 0;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].v;
    if (v == p) continue;
    int w = ed[u][i].w;
    int x = dfs(v, u, ans);
    x = 1ll * (x + 1) * w % MOD;
    ans = (ans + 1ll * (r + 1) * x) % MOD;
    r = (r + x) % MOD;
  }
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    ed[u].push_back(edge(v, w));
    ed[v].push_back(edge(u, w));
  }
  int ans = 0;
  dfs(1, 0, ans);
  printf("%d\n", ans);
}
