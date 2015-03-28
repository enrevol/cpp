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
 
int a[1010101], b[1010101];
p2 c[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int h;
  scanf("%d", &h);
  int n = h << 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", a + i, b + i);
    c[i].first = a[i] - b[i];
    c[i].second = i;
  }
  std::sort(c + 1, c + n + 1);
  int ans = 0;
  for (int i = 1; i <= h; ++i)
    ans += a[c[i].second];
  for (int i = h + 1; i <= n; ++i)
    ans += b[c[i].second];
  printf("%d", ans);  
}