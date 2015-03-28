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
 
std::vector<p2> e[10101];
long long d[10101];
int h[10101];
 
long long dfs(int u, int p, int k) {
  long long& res = d[u];
  h[u] = k;
  for (size_t i = 0; i < e[u].size(); ++i) {
    const p2& x = e[u][i];
    if (x.first == p) continue;
    long long val = dfs(x.first, u, k + 1) + x.second;
    if (val > res) res = val;
  }
  return res;
}
 
inline long long get(int u, int i) {
  const p2& x = e[u][i];
  return d[x.first] + x.second;
}
 
int find(int u, int p, long long th) {
  if (d[u] <= th) return u;
  int sz = int(e[u].size());
  return find(e[u][sz - 2].first, u, th);
}
 
bool dfs(int u, int p, int vx, long long k, long long th) {
  if (h[u] >= h[vx]) return 1;
  if (k > th && d[u] - d[vx] > th) return 0;
  int sz = int(e[u].size()) - 1;
  for (int i = 0; i < sz - 1; ++i) {
    const p2& x = e[u][i];
    assert(x.first != p);
    long long val = get(u, i);
    if (val + k > th && val + (d[u] - d[vx]) > th) return 0;
  }
  return dfs(e[u][sz - 1].first, u, vx, k + e[u][sz - 1].second, th);
}
 
bool cmp(const p2& a, const p2& b) {
  return d[a.first] + a.second < d[b.first] + b.second;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, p;
  scanf("%d %d", &n, &p);
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    e[u].push_back(p2(v, c));
    e[v].push_back(p2(u, c));
  }
  dfs(p, 0, 1);
  for (int i = 1; i <= n; ++i)
    std::sort(e[i].begin(), e[i].end(), cmp);
  int sz = e[p].size();
  const p2& x = e[p][sz - 1];
  long long ans = -1;
  long long lo = sz > 1 ? get(p, sz - 2) : 0;
  long long hi = get(p, sz - 1);
  while (lo <= hi) {
    long long mi = (lo + hi) >> 1;
    int vx = find(x.first, p, mi);
    if (dfs(x.first, p, vx, x.second, mi)) {
      ans = mi;
      hi = mi - 1;
    } else {
      lo = mi + 1;
    }
  }
  fprintf(stderr, "d = %lld\n", get(p, sz - 1));
  fprintf(stderr, "ans = %lld\n", ans);
  printf("%lld", get(p, sz - 1) - ans);
}