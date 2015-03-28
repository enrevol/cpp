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
 
std::map<int, int> st;
 
int a[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  int r = 0;
  int v = 0;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    while (r < n && v < m) {
      ++r;
      if (!st[a[r]]) ++v;
      ++st[a[r]];
    }
    while (r < n && st[a[r + 1]]) {
      ++r;
      ++st[a[r]];
    }
    int val = r - i + 1;
    //printf("%d %d\n", r, i);
    if (val > ans) ans = val;
    --st[a[i]];
    if (!st[a[i]]) --v;
  }
  printf("%d", ans);
} 