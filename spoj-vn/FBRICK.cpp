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
 
int mod;
const int w = 6;
 
// A[n-1]
// A[n-2]
// A[n-1] * A[n-2]
// A[n-1] ^ 2
// A[n-2] ^ 2
// S[n-1]
 
struct matrix {
  int a[w][w];
} base, mat, id;
 
matrix operator* (const matrix& x, const matrix& y) {
  matrix res;
  for (int i = 0; i < w; ++i)
    for (int j = 0; j < w; ++j) {
      int v = 0;
      for (int k = 0; k < w; ++k)
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
  mat.a[0][1] = -1;
  mat.a[1][0] = 1;
  mat.a[2][2] = -1;
  mat.a[3][4] = 1;
  mat.a[4][3] = 1;
  mat.a[5][3] = 1;
  mat.a[5][5] = 1;
  for (int i = 0; i < w; ++i) id.a[i][i] = 1;
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int v, n;
    scanf("%d %d %d", &v, &n, &mod);    
    // Matrix[2]    
    base.a[0][0] = v % mod;           // A[2]
    base.a[1][0] = 1 % mod;           // A[1]
    base.a[2][0] = v % mod;           // A[2] * A[1]
    base.a[3][0] = 1ll * v * v % mod; // A[2] ^ 2
    base.a[4][0] = 1 % mod;           // A[1] ^ 2
    base.a[5][0] = 1 % mod;           // S[1]
    --n;
    matrix res = id;
    matrix tmp = mat;
    tmp.a[0][0] = (v << 1) % mod;
    tmp.a[2][3] = (v << 1) % mod;
    tmp.a[3][2] = (1ll * -v * 4) % mod;
    tmp.a[3][3] = (1ll * v * v * 4) % mod;
    while (n) {
      if (n & 1) res = res * tmp;
      n >>= 1;
      tmp = tmp * tmp;
    }    
    int ans = (res * base).a[5][0];
    if (ans < 0) ans += mod;
    printf("%d\n", ans);
  }
}