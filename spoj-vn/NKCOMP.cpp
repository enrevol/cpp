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

int tm;

std::vector<int> ed[N], line[N], fw[N];
int depth[N], tin[N], tout[N], vps[N];

void dfs(int u) {
  tin[u] = ++tm;  
  line[depth[u]].push_back(tm);
  vps[u] = line[depth[u]].size();
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    depth[v] = depth[u] + 1;
    dfs(v);
  }
  tout[u] = ++tm;
}

inline void add(int id, int p, int v) {
  while (p <= int(fw[id].size())) {
    fw[id][p - 1] += v;
    p += p & -p;
  }
}

inline void add(int id, int f, int t, int v) {
  add(id, f, v);
  add(id, t + 1, -v);
}

inline int get(int id, int p) {
  int r = 0;
  while (p > 0) {
    r += fw[id][p - 1];
    p &= p - 1;
  }
  return r;
}

inline int find_right(int id, int t) {
  return std::upper_bound(line[id].begin(), line[id].end(), t) - line[id].begin() - 1;
}

inline int find_left(int id, int t) {
  return std::upper_bound(line[id].begin(), line[id].end(), t) - line[id].begin();
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    ed[u].push_back(v);
  }
  dfs(1);
  for (int i = 0; i < n; ++i) {
    if (line[i].empty()) break;
    fw[i].resize(line[i].size());
  }
  int m;
  std::cin >> m;
  while (m--) {
    int type, u;
    std::cin >> type >> u;
    if (type == 1) {
      int k, v;
      std::cin >> k >> v;
      k += depth[u];
      if (k < n) {
        int left = find_left(k, tin[u]);
        int right = find_right(k, tout[u]);
        if (left <= right) add(k, left + 1, right + 1, v);
      }
    } else {
      int ans = get(depth[u], vps[u]);
      std::cout << ans << '\n';
    }
  }
}
