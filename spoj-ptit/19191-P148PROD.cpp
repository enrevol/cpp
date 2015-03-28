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
 
#define sqr(x) ((x) * (x))
 
const double eps = 1e-6;
 
std::vector<int> e[15];
double x[15], y[15];
 
inline double abs(const double& a) {
  return a >= 0 ? a : -a;
}
 
inline bool eq(const double& a, const double& b) {
  return abs(a - b) <= eps;
}
 
int n;
int v[15];
 
bool solve(int k, const int d) {
  if (k > n) return true;
  bool b[4] = { false };
  for (size_t i = 0; i < e[k].size(); ++i)
    if (v[e[k][i]] != -1)
      b[v[e[k][i]]] = true;
  bool res = false;
  for (int i = 0; i < d && !res; ++i)
    if (!b[i]) {
      v[k] = i;
      res = solve(k + 1, d);
    }
  v[k] = -1;
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(v, -1, sizeof(v));
  int nc = 0;
  while (~scanf("%d", &n)) {
    if (n) {      
      for (int i = 1; i <= n; ++i) {
        e[i].clear();
        scanf("%lf %lf", x + i, y + i);
        for (int j = 1; j < i; ++j) {
          double d = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
          if (eq(d, 400) || d < 400) {
            e[i].push_back(j);
            e[j].push_back(i);
          }
        }
      }
      int ans = -1;
      for (int i = 1; i <= 4 && ans == -1; ++i)
        if (solve(1, i))
          ans = i;
      if (ans == -1) ans = 5;
      printf("The towers in case %d can be covered in %d frequencies.\n", ++nc, ans);
    }
  }
} 