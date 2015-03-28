#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const double eps = 1e-6;
 
inline bool eq(const double& a) {
  return abs(a) <= eps;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int x1, y1, r1;
  scanf("%d %d %d", &x1, &y1, &r1);
  int x2, y2, r2;
  scanf("%d %d %d", &x2, &y2, &r2);
  if (r1 > r2) {
    std::swap(x1, x2);
    std::swap(y1, y2);
    std::swap(r1, r2);
  }
  double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  double t = d - r1 - r2;
  double ans;
  if (t > 0 || eq(t)) {
    ans = t / 2;
  } else {
    double a = -r1;    
    double b = d - r2;
    t = b - a;
    if (t > 0 || eq(t)) {
      ans = 0;
    } else {
      ans = -t / 2;
    }
  }
  printf("%.15lf", ans);
} 