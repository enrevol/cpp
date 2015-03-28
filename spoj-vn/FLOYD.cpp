#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
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
 
const int N = 110;
 
struct ele {
  int to, dist;
  ele(int to, int dist) : to(to), dist(dist) { }
  bool operator<(const ele& x) const {
    return dist > x.dist;
  }
};
 
std::vector<ele> ed[N];
int dist[N], parent[N];
 
int dijkstra(int src, int dst) {  
  std::priority_queue<ele> q;
  q.push(ele(src, 0));
  memset(dist, -1, sizeof(dist));
  dist[src] = 0;
  while (!q.empty()) {
    int u = q.top().to;
    int c = q.top().dist;
    q.pop();
    if (c != dist[u]) continue;
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].to;
      int t = ed[u][i].dist + c;
      if (dist[v] == -1 || dist[v] > t) {
        parent[v] = u;
        dist[v] = t;
        q.push(ele(v, t));
      }
    }
  }
  return dist[dst];
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  for (int u, v, c; m--; ) {
    scanf("%d %d %d", &u, &v, &c);
    ed[u].push_back(ele(v, c));
    ed[v].push_back(ele(u, c));
  }
  for (int t, u, v; k--; ) {
    scanf("%d %d %d", &t, &u, &v);
    int val = dijkstra(u, v);
    if (t == 0) {
      printf("%d", val);
    } else {
      if (val == -1) {
        printf("-1");
      } else if (val == 0) {
        printf("2 %d %d", u, u);
      } else {
        std::vector<int> vert;
        for (int x = v; x != u; x = parent[x]) {
          vert.push_back(x);
        }
        vert.push_back(u);
        std::reverse(vert.begin(), vert.end());
        printf("%d", int(vert.size()));
        for (int i = 0; i < int(vert.size()); ++i) {
          printf(" %d", vert[i]);
        }
      }
    }
    putchar('\n');
  }
}
