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
 
typedef std::pair<int, long long> p2;
 
const int w = 1 << 20;
 
int a[50], b[50];
p2 hl[w + 10], hr[w + 10];
int cl, cr;
int k;
 
void dfs(int i, int h, int w, long long val, int& cnt, p2 arr[]) {
  if (w > k) return;
  if (i == h) {
    arr[++cnt] = p2(w, val);
  } else {
    dfs(i + 1, h, a[i] + w, b[i] + val, cnt, arr);
    dfs(i + 1, h, w, val, cnt, arr);
  }
}
 
bool ff(const p2& a, const p2& b) {
  if (a.first == b.first) return a.second > b.second;
  return a.first < b.first;
}
 
bool ee(const p2& a, const p2& b) {
  return a.first == b.first;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%d %d", a + i, b + i);  
  int h = n >> 1;
  dfs(0, h, 0, 0, cl, hl);
  dfs(h, n, 0, 0, cr, hr);
  std::sort(hl + 1, hl + cl + 1);
  std::sort(hr + 1, hr + cr + 1);
  //cl = std::unique(hl + 1, hl + cl + 1, ee) - hl - 1;
  //cr = std::unique(hr + 1, hr + cr + 1, ee) - hr - 1;
  long long ans = 0;
  int j = 1;
  long long best = 0;
  for (int i = cl; i >= 1; --i) {
    while (j < cr && hl[i].first + hr[j + 1].first <= k) {
      ++j;
      if (hr[j].second > best)
        best = hr[j].second;
    }
    long long val = hl[i].second + best;;
    if (val > ans) ans = val;
  }
  printf("%lld", ans);
} 