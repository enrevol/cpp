#include <algorithm>
#include <bitset>
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
 
typedef unsigned int u32;
typedef std::pair<u32, u32> p2;
 
const u32 mx = 1e6;
const u32 kx = 9e2;
 
std::vector<p2> ans;
 
u32 n, m;
u32 tn;
 
u32 xt[34];
u32 st[2][34];
u32 a[30][30];
 
u32 last[mx + 10];
u32 next[kx + 10];
u32 row[kx + 10];
u32 mask[kx + 10];
u32 step[kx + 10];
 
inline void add(u32 v, u32 i) {
  if (v > m) return;
  next[i] = last[v];
  last[v] = i;
}
 
void input() {
  scanf("%u %u", &n, &m);
  u32 x, y;
  scanf("%u %u", &x, &y);
  --x, --y;
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j)
      scanf("%u", a[i] + j);
  st[0][x + 2] |= 1u << y;
}
 
void pre() {
  for (u32 i = 0, en = 0; i < n; ++i) {
    std::vector<p2> vt(n);
    for (u32 j = 0; j < n; ++j)
      vt[j] = p2(a[i][j], 1u << j);
    std::sort(vt.begin(), vt.end());
    for (u32 j = 0; j < n && vt[j].first <= m; ) {
      u32 k = j + 1;
      while (k < n && vt[k].first == vt[j].first)
        vt[j].second |= vt[k++].second;
      add(vt[j].first, ++en);
      mask[en] = vt[j].second;
      row[en] = i + 2;
      step[en] = vt[j].first;
      j = k;
    }
  }
}
 
void solve() {
  for (u32 k = 1; k <= m; ++k, tn = 1 - tn) {
    memset(st[1 - tn], 0, 128);
    memset(xt, 0, 128);
    for (u32 i = 2; i < n + 2; ++i)
      if (st[tn][i]) {
        u32 u = st[tn][i] << 2 | st[tn][i] >> 2;
        st[1 - tn][i - 1] |= u;
        st[1 - tn][i + 1] |= u;
        u32 v = st[tn][i] << 1 | st[tn][i] >> 1;
        st[1 - tn][i - 2] |= v;
        st[1 - tn][i + 2] |= v;
      }
    for (u32 i = last[k], j; i; i = j) {
      xt[row[i]] |= mask[i];
      j = next[i];
      add(k + step[i], i);
    }
    for (u32 i = 2; i < n + 2; ++i)
      st[1 - tn][i] &= xt[i];
  }
}
 
void output() {
  for (u32 i = 2; i < n + 2; ++i)
    for (u32 j = 0; j < n; ++j)
      if (st[tn][i] & (1 << j))
        ans.push_back(p2((i - 2) + 1, j + 1));
  printf("%u\n", u32(ans.size()));
  for (u32 i = 0; i < ans.size(); ++i)
    printf("%u %u\n", ans[i].first, ans[i].second);  
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  input();
  pre();
  solve();
  output();
}