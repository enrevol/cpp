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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  int nc = 0;
  while (~scanf("%d", &n)) {
    if (n >= 0) {
      double tx = 0;
      double ty = 0;
      double tm = 0;
      double x, y, m;
      for (int i = 1; i <= n; ++i) {
        scanf("%lf %lf %lf", &x, &y, &m);
        tx += x * m;
        ty += y * m;
        tm += m;
      }
      printf("Case %d: %.2lf %.2lf\n", ++nc, tx / tm, ty / tm);
    }
  }
}