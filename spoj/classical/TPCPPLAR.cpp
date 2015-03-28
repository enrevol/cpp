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

const int N = 150010;

std::vector<int> ed[N], ev[N], scc[N], sed[N], ans;
int vis[N], stack[N], id[N], pos[N], mark[N], deg[N], next[N], prev[N];

void dfs(int u, int& st_sz) {
  if (vis[u]) return;
  vis[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    dfs(ed[u][i], st_sz);
  }
  stack[++st_sz] = u;
}

void dfs_rev(int u, int k) {
  if (vis[u]) return;
  scc[k].push_back(u);
  id[u] = k;
  vis[u] = 1;
  for (int i = 0; i < int(ev[u].size()); ++i) {
    dfs_rev(ev[u][i], k);
  }
}

void dfs_topo(int u, int& st_sz) {
  if (vis[u]) return;
  vis[u] = 1;
  for (int i = 0; i < int(sed[u].size()); ++i) {
    dfs_topo(sed[u][i], st_sz);
  }
  pos[u] = st_sz;
  stack[st_sz--] = u;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    ed[u].push_back(v);
    ev[v].push_back(u);
  }
  int st_sz = 0;
  for (int i = 1; i <= n; ++i) {
    dfs(i, st_sz);
  }
  memset(vis, 0, sizeof(vis));
  int scc_cnt = 0;
  for (int i = st_sz; i >= 1; --i) {
    int u = stack[i];
    if (!vis[u]) {
      dfs_rev(u, ++scc_cnt);
    }
  }
  for (int u = 1; u <= n; ++u) {
    int uid = id[u];
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i];      
      int vid = id[v];
      if (vid != uid) {
        sed[uid].push_back(vid);
      }
    }
  }
  for (int i = 1; i <= scc_cnt; ++i) {
    std::sort(sed[i].begin(), sed[i].end());
    sed[i].erase(std::unique(sed[i].begin(), sed[i].end()), sed[i].end());
    for (int j = 0; j < int(sed[i].size()); ++j) {
      ++deg[sed[i][j]];
    }
  }  
  st_sz = scc_cnt;
  memset(vis, 0, sizeof(vis));  
  for (int i = 1; i <= scc_cnt; ++i) {
    dfs_topo(i, st_sz);
  }
  int src = 0, dst = scc_cnt + 1;
  pos[dst] = dst;
  for (int i = 1; i <= scc_cnt; ++i) {
    if (!deg[i]) {
      sed[src].push_back(i);
      ++deg[i];
    }
    if (sed[i].empty()) {
      sed[i].push_back(dst);
      ++deg[dst];
    }
  }
  std::fill(next, next + dst + 1, dst);
  for (int i = 0; i <= scc_cnt + 1; ++i) {
    int u = stack[i];
    for (int j = 0; j < int(sed[u].size()); ++j) {
      int v = sed[u][j];
      if (pos[v] < pos[next[u]]) {
        next[u] = v;
      }
      if (pos[u] > pos[prev[v]]) {
        prev[v] = u;
      }
    }    
  }
  for (int i = 0; i <= scc_cnt + 1; ++i) {
    int u = stack[i];
    for (int j = 0; j < int(sed[u].size()); ++j) {
      int v = sed[u][j];
      if (next[u] != v && prev[v] != u) {
        std::swap(sed[u][j], sed[u].back());
        sed[u].pop_back();
        --j;
        --deg[v];
      }
    }
  }
  for (int i = 0; i <= scc_cnt + 1; ++i) {
    int u = stack[i];
    for (int j = 0; j < int(sed[u].size()); ++j) {
      int v = sed[u][j];
      assert(pos[u] < pos[v]);
      if (deg[v] == 1 || sed[u].size() == 1) {
        if (pos[u] + 1 <= pos[v] - 1) {
          ++mark[pos[u] + 1];
          --mark[pos[v]];
        }
      }
    }
  }
  for (int i = 1; i <= scc_cnt; ++i) {
    mark[i] += mark[i - 1];
    if (!mark[i]) {
      int u = stack[i];
      ans.insert(ans.end(), scc[u].begin(), scc[u].end());
    }
  }
  std::sort(ans.begin(), ans.end());
  printf("%d\n", int(ans.size()));
  for (int i = 0; i < int(ans.size()); ++i) {
    printf("%d ", ans[i]);
  }
  fprintf(stderr, "\n%d\n", int(ans.size()));
}