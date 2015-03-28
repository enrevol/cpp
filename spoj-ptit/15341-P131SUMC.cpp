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
 
double abs(double x) {
  return x >= 0 ? x : -x;
}
 
double max(double x, double y) {
  return x > y ? x : y;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  double a, b, c, d;
  scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
  double x = abs(a / c - b / d);
  double y = abs(c / d - a / b);
  double z = abs(d / b - c / a);
  double t = abs(b / a - d / c);
  double m = max(max(x, y), max(z, t));
  if (m == x) { printf("0"); return 0; }
  if (m == y) { printf("1"); return 0; }
  if (m == z) { printf("2"); return 0; }
  printf("3");
}