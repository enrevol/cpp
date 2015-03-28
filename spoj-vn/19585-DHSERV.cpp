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
 
typedef std::pair<int, int> p2;
 
struct ele {
  int u;
  long long d;
  ele(int u, const long long& d) : u(u), d(d) { }
  bool operator< (const ele& a) const {
    return d > a.d;
  }
};
 
std::vector<p2> e[505];
int qu[1010101], qv[1010101];
bool b[505];
long long dist[505][505];
long long ans[1010101];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  int u, v, c;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &c);
    e[u].push_back(p2(v, c));
  }
  int x = 0;
  int t;
  for (int i = 1; i <= k + 1; ++i) {
    if (i <= k) scanf("%d %d", &t, qu + i);
    if (t == 1 || i > k) {
      if (i <= k && b[qu[i]]) continue;
      std::vector<int> vx;
      for (int j = x + 1; j < i; ++j)
        if (qv[j]) vx.push_back(qu[j]);
      memset(dist, -1, sizeof(dist));
      for (size_t j = 0; j < vx.size(); ++j) {
        int z = vx[j];
        std::priority_queue<ele> que;
        dist[z][z] = 0;
        que.push(ele(z, 0));
        while (!que.empty()) {
          ele x = que.top();
          que.pop();
          if (x.d > dist[z][x.u]) continue;
          if (!b[x.u] && x.u != z) continue;
          for (size_t i = 0; i < e[x.u].size(); ++i) {
            p2& t = e[x.u][i];
            long long val = x.d + t.second;
            long long& ref = dist[z][t.first];
            if (ref == -1 || ref > val) {
              ref = val;
              que.push(ele(t.first, val));
            }
          }
        }
      }
      for (int j = x + 1; j < i; ++j)
        if (qv[j]) printf("%lld\n", dist[qu[j]][qv[j]]);
      if (i <= k) b[qu[i]] = 1;
      x = i;
    } else {
      scanf("%d", qv + i);
    }
  }
}  