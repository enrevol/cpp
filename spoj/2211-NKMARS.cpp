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
 
struct event {
  int f, t;
  event() { }  
  event(int f, int t) : f(f), t(t) { }
};
 
std::vector<event> ev[30303][2];
int tr[202020], val[202020];
 
void modify(int i, int f, int t, int qf, int qt, int v) {  
  int il = i << 1;
  int ir = i << 1 | 1;
  if (qf <= f && t <= qt) {
    tr[i] += v;
  } else {
    int m = (f + t) >> 1;
    if (qf < m) modify(il, f, m, qf, qt, v);
    if (qt > m) modify(ir, m, t, qf, qt, v);
  }
  if (tr[i]) {
    val[i] = t - f;
  } else if (f < t) {
    val[i] = val[il] + val[ir];
  } else {
    val[i] = 0;
  }
}
 
int query(int i, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) {
    return val[i];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (f + t) >> 1;
    if (qt < m) return query(il, f, m, qf, qt);
    if (qf > m) return query(ir, m, t, qf, qt);
    return query(il, f, m, qf, qt) + query(ir, m, t, qf, qt);
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int x1, y1, x2, y2;  
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    ev[x1][0].push_back(event(y1, y2));
    ev[x2][1].push_back(event(y1, y2));
  }
  int ans = 0;
  for (int x = 0; x <= 30000; ++x) {
    ans += query(1, 0, 30000, 0, 30000);
    for (size_t i = 0; i < ev[x][0].size(); ++i)
      modify(1, 0, 30000, ev[x][0][i].f, ev[x][0][i].t, 1);
    for (size_t i = 0; i < ev[x][1].size(); ++i)
      modify(1, 0, 30000, ev[x][1][i].f, ev[x][1][i].t, -1);
  }
  printf("%d", ans);
} 