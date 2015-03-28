#include <algorithm>
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
 
const int N = 10010;
 
std::vector<int> ed[N];
std::vector<int> ch[N];
 
int tin[N];
int low[N];
int tm;
 
void dfs(int u, int p) {
  tin[u] = low[u] = ++tm;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    if (tin[v] > 0) {
      low[u] = std::min(low[u], tin[v]);
    } else {
      dfs(v, u);
      low[u] = std::min(low[u], low[v]);
      ch[u].push_back(v);
    }
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  while (~scanf("%d %d", &n, &m)) {
    if (n == 0 && m == 0) break;
    for (int i = 1; i <= n; ++i) {
      ed[i].clear();
      ch[i].clear();
    }
    memset(low, 0, sizeof(low));
    memset(tin, 0, sizeof(tin));
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d %d", &u, &v);
      ed[u].push_back(v);
      ed[v].push_back(u);
    }
    tm = 0;
    dfs(1, 0);
    int ans = ch[1].size() >= 2;
    for (int i = 2; i <= n; ++i) {
      bool f = 0;
      for (int j = 0; j < int(ch[i].size()) && !f; ++j)
        f = low[ch[i][j]] >= tin[i];
      ans += f;
    }
    printf("%d\n", ans);
  }
}