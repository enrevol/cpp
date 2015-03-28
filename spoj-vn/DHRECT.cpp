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
 
int a[303030];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1, std::greater<int>());    
    int x = -1, y = -1;
    for (int i = 1; i <= n && (x == -1 || y == -1); ) {
      int j = i + 1;
      while (j <= n && a[j] == a[i]) ++j;
      int c = j - i;
      if (c >= 2) if (x == -1) x = a[i], c -= 2;
      if (c >= 2) if (y == -1) y = a[i];
      i = j;
    }
    if (x != -1 && y != -1) printf("%lld\n", 1ll * x * y);
    else puts("-1");
  }
}