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
 
const int N = 100010;
 
struct domino {
  int x, h, id;
  bool operator<(const domino& a) const {
    return x < a.x;
  }
} a[N];
 
int ans[N], x[N], tr[N << 2];
 
int query(int i, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) return tr[i];
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(i << 1, f, m, qf, qt);
  if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt);
  return std::max(query(i << 1, f, m, qf, qt), query(i << 1 | 1, m + 1, t, qf, qt));
}
 
void update(int i, int f, int t, int pos, int val) {
  if (f < t) {
    int m = (f + t) >> 1;
    if (pos < m + 1) update(i << 1, f, m, pos, val);
    else update(i << 1 | 1, m + 1, t, pos, val);
  }
  tr[i] = std::max(tr[i], val);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &a[i].x, &a[i].h);
    a[i].id = i;
  }
  std::sort(a + 1, a + n + 1);  
  for (int i = n; i; --i) {    
    int nx = a[i].x + a[i].h - 1;
    int pos = std::upper_bound(x + i + 1, x + n + 1, nx) - x - 1;
    int val = i;
    if (i < pos) val = std::max(val, query(1, 1, n, i + 1, pos));
    ans[a[i].id] = val - i + 1;
    update(1, 1, n, i, val);
    x[i] = a[i].x;
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
}