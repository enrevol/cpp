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
 
const int mod = 1e9 + 7;
const int w = 51;
 
struct matrix {
  int a[w + 5][w + 5];
} base, mat, id;
 
matrix operator* (const matrix& x, const matrix& y) {
  matrix res;
  for (int i = 0; i <= w; ++i)
    for (int j = 0; j <= i; ++j) {
      int v = 0;
      for (int k = j; k <= w; ++k)
        v = (v + 1ll * x.a[i][k] * y.a[k][j]) % mod;
      res.a[i][j] = v;
    }
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 0; i < w; ++i) {
    base.a[i][0] = base.a[i][i] = 1;
    for (int j = 1; j < i; ++j)
      base.a[i][j] = (base.a[i - 1][j - 1] + base.a[i - 1][j]) % mod;
    mat.a[i][0] = 1;
  }
  base.a[w][w] = 1;
  for (int i = 0; i <= w; ++i)
    id.a[i][i] = 1;
  int n, k;
  while (~scanf("%d %d", &n, &k)) {
    matrix ans = mat;
    matrix res = id;
    matrix tmp = base;
    tmp.a[w][k] = 1;
    while (n) {
      if (n & 1) res = res * tmp;
      tmp = tmp * tmp;
      n >>= 1;
    }
    ans = res * ans;
    printf("%d\n", ans.a[w][0]);
  }
}