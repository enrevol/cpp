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

const int N = 30010;

struct edge {
  int to, dist;
  edge(int to, int dist) : to(to), dist(dist) { }
  bool operator<(const edge& e) const {
    return dist > e.dist;
  }
};

std::vector<edge> ed[N];
std::vector<int> ev[N], er[N], ans;
int dist[N], vis[N], tin[N], low[N], tm;

void dfs(int u, int p) {
  tin[u] = low[u] = ++tm;
  for (int i = 0; i < int(ev[u].size()); ++i) {
    int v = ev[u][i];
    if (v == p) continue;
    if (tin[v] > 0) {
      low[u] = std::min(low[u], tin[v]);
    } else {
      er[u].push_back(v);
      dfs(v, u);
      low[u] = std::min(low[u], low[v]);
    }
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v, d;
    scanf("%d %d %d", &u, &v, &d);
    ed[u].push_back(edge(v, d));
    ed[v].push_back(edge(u, d));
  }
  std::priority_queue<edge> q;
  memset(dist, -1, sizeof(dist));
  dist[1] = 0;
  q.push(edge(1, 0));
  while (!q.empty()) {
    int u = q.top().to;
    int d = q.top().dist;
    q.pop();
    if (dist[u] != d) continue;
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].to;
      int t = ed[u][i].dist + d;
      if (dist[v] == -1 || dist[v] > t) {
        dist[v] = t;
        q.push(edge(v, t));
      }
    }
  }
  std::queue<int> que;
  que.push(n);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].to;
      int d = ed[u][i].dist;
      if (dist[v] + d == dist[u]) {
        ev[u].push_back(v);
        ev[v].push_back(u);
        if (!vis[v]) {
          vis[v] = 1;
          que.push(v);
        }
      }        
    }
  }
//  for (int i = 1; i <= n; ++i) {
//    fprintf(stderr, "i = %d : ", i);
//    for (int j = 0; j < int(ev[i].size()); ++j) {
//      fprintf(stderr, "%d ", ev[i][j]);      
//    }
//    putchar('\n');
//  }
  dfs(n, 0);
  for (int i = 2; i < n; ++i) {
//    fprintf(stderr, "i = %d tin = %d low = %d\n", i, tin[i], low[i]);
    if (tin[i] == 0) {
      ans.push_back(i);
    } else if (er[i].empty()) {
      ans.push_back(i);
    } else {
      int flag = 0;
      for (int j = 0; j < int(er[i].size()) && !flag; ++j) {
        int v = er[i][j];
        flag = low[v] >= tin[i];
      }
      if (flag == 0) {
        ans.push_back(i);
      }
    }
  }  
  printf("%d\n", int(ans.size()));
  for (int i = 0; i < int(ans.size()); ++i) {
    printf("%d\n", ans[i]);
  }
}
