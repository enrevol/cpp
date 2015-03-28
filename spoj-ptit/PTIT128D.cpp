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
 
std::vector<int> ed[1010];
int a[1010];
int b[1010];
bool c[1010];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  while (scanf("%d %d", &n, &k)) {
    if (n == 0 && k == 0) break;
    for (int i = 1; i <= n; ++i)
      ed[i].clear();
    for (int i = 1, x, v; i <= n; ++i) {
      scanf("%d %d", a + i, &x);
      b[i] = a[i];
      c[i] = 0;
      while (x--) {
        scanf("%d", &v);
        ed[i].push_back(v + 1);
      }
    }
    for (int i = 1; i <= n; ++i)
      for (std::vector<int>::iterator j = ed[i].begin(); j != ed[i].end(); ++j)
        b[i] += a[*j];
    for (bool f = 1; f; ) {
      std::vector<int> er;
      for (int i = 1; i <= n; ++i)
        if (!c[i] && b[i] < k) {
          er.push_back(i);
          c[i] = 1;
        }
      f = er.size() > 0;
      for (std::vector<int>::iterator i = er.begin(); i != er.end(); ++i)
        for (std::vector<int>::iterator j = ed[*i].begin(); j != ed[*i].end(); ++j)
          b[*j] -= a[*i];
    }
    int ans = 0;
    int tot = 0;
    for (int i = 1; i <= n; ++i)
      if (!c[i]) ++ans, tot += a[i];        
    printf("%d %d\n", ans, tot);
  }
}