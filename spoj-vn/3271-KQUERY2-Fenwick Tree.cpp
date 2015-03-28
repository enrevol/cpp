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
 
const int N = 30010;
const int Q = 200010;
 
int a[N];
std::vector<int> tr[N], fw[N]; 
int t[Q], x[Q], y[Q], z[Q];
 
inline void fw_update(int id, int pos, int val) {
  for (++pos; pos; pos -= pos & -pos)
    fw[id][pos - 1] += val;
}
 
inline int fw_query(int id, int pos) {
  int sz = int(fw[id].size());
  int res = 0;
  for (++pos; pos <= sz; pos += pos & -pos)
    res += fw[id][pos - 1];
  return res;
}
 
inline void add(int pos, int n, int val) {
  for ( ; pos <= n; pos += pos & -pos)
    tr[pos].push_back(val);
}
 
inline void build(int n) {
  for (int i = 1; i <= n; ++i) {
    std::sort(tr[i].begin(), tr[i].end());
    tr[i].resize(std::unique(tr[i].begin(), tr[i].end()) - tr[i].begin());
    fw[i].resize(tr[i].size());
  }
}
 
inline void update(int pos, int n, int val, int k) {
  for ( ; pos <= n; pos += pos & -pos)
    fw_update(pos, std::lower_bound(tr[pos].begin(), tr[pos].end(), val) - tr[pos].begin(), k);
}
 
inline int query(int pos, int val) {
  int res = 0;
  for ( ; pos; pos -= pos & -pos)
    res += fw_query(pos, std::upper_bound(tr[pos].begin(), tr[pos].end(), val) - tr[pos].begin());
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    add(i, n, a[i]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", t + i, x + i, y + i);
    if (t[i] == 1) scanf("%d", z + i);
    else add(x[i], n, y[i]);
  }
  build(n);
  for (int i = 1; i <= n; ++i) update(i, n, a[i], 1);
  for (int i = 1; i <= q; ++i) {
    if (t[i] == 1) {
      int ans = query(y[i], z[i]) - query(x[i] - 1, z[i]);
      printf("%d\n", ans);
    } else {
      update(x[i], n, a[x[i]], -1);
      update(x[i], n, y[i], 1);
      a[x[i]] = y[i];
    }
  }
}