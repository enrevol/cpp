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

const int N = 11;

int g[N][N], vis[N];
std::vector<int> cc[N];

void dfs(int u, int id, int n) {
  if (vis[u]) return;
  vis[u] = 1;
  cc[id].push_back(u);
  for (int v = 1; v <= n; ++v)
    if (g[u][v]) dfs(v, id, n);
}

long long memo[] = { 0, 1, 3, 54, 3834, 1027080, 1067308488, 4390480193904LL };

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);  
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", g[i] + j);
  int cc_cnt = 0;
  long long ans = 1;
  for (int u = 1; u <= n; ++u)
    if (!vis[u]) dfs(u, ++cc_cnt, n);
  fprintf(stderr, "cc_cnt = %d\n", cc_cnt);
  for (int i = 1; i <= cc_cnt; ++i) {
    int sz = cc[i].size();
    if (sz == 1) continue;
    ans = ans * memo[sz];
  }
  printf("%lld", ans);
}
