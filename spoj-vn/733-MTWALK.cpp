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
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
int n;
int a[101][101];
bool b[101][101];
 
typedef std::pair<int, int> p2;
 
bool ok(int f, int t) {
  memset(b, 0, sizeof(b));  
  std::queue<p2> que;
  que.push(p2(1, 1));
  b[1][1] = 1;
  while (!que.empty()) {    
    p2 k = que.front();
    que.pop();    
    for (int i = 0; i < 4; ++i) {
      int x = k.first + dx[i];
      int y = k.second + dy[i];
      if (1 <= x && x <= n)
        if (1 <= y && y <= n)          
          if (f <= a[x][y] && a[x][y] <= t)
            if (!b[x][y]) {
              b[x][y] = 1;
              que.push(p2(x, y));
            }
    }
  }
  return b[n][n];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", a[i] + j);
  int ans = -1;
  for (int lo = 0, hi = 110; lo <= hi; ) {
    int mi = (lo + hi) >> 1;
    bool f = 0;
    for (int base = 0; base <= a[1][1] && base + mi <= 110 && !f; ++base)
      f = ok(base, base + mi);
    if (f) {
      hi = mi - 1;
      ans = mi;
    } else {
      lo = mi + 1;
    }
  }
  printf("%d", ans);
}