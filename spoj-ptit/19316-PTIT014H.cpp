#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct edge {
  int t, c;
  edge(int t, int c) : t(t), c(c) { }
};
 
struct ele {
  long long d;
  int u, e;
  ele(long long d, int u, int e) : d(d), u(u), e(e) { }
  bool operator< (const ele& a) const {
    if (d == a.d) return e > a.e;
    return d > a.d;
  }
};
 
std::vector<edge> e[505];
long long dist[505], ed[505];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; ++i) e[i].clear();
    int u, v, c;
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d %d", &u, &v, &c);
      e[u].push_back(edge(v, c));
      e[v].push_back(edge(u, c));
    }
    int x, y, z;    
    while (q--) {
      scanf("%d %d %d", &x, &y, &z);
      memset(dist, -1, sizeof(dist));
      memset(ed, -1, sizeof(ed));
      dist[x] = dist[y] = dist[z] = 0;
      ed[x] = ed[y] = ed[z] = 0;
      std::priority_queue<ele> que;
      que.push(ele(0, x, 0));
      que.push(ele(0, y, 0));
      que.push(ele(0, z, 0));
      long long ans = 0;      
      while (!que.empty()) {        
        ele t = que.top();
        que.pop();
        if (t.d == dist[t.u] && t.e == ed[t.u]) {
          ans += t.e;
          size_t sz = e[t.u].size();
          for (size_t i = 0; i < sz; ++i) {
            edge& k = e[t.u][i];
            long long v = t.d + k.c;
            if (dist[k.t] == -1 || dist[k.t] > v || (dist[k.t] == v && ed[k.t] > k.c)) {
              dist[k.t] = v;
              ed[k.t] = k.c;              
              que.push(ele(v, k.t, k.c));
            }
          }
        }
      }
      printf("%lld\n", ans * 100);
    }
  }
} 