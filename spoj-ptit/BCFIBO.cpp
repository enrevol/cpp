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
 
const int mod = 1e9 + 7;
 
struct mat {
  int a[2][2];
  
  mat(int x, int y, int z, int t) {
    a[0][0] = x;
    a[0][1] = y;
    a[1][0] = z;
    a[1][1] = t;
  }  
} fi(1, 1, 1, 0);
 
mat operator* (const mat& a, const mat& b) {
  mat res(0, 0, 0, 0);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      for (int k = 0; k < 2; ++k)
        res.a[i][j] = (res.a[i][j] + 1ll * a.a[i][k] * b.a[k][j]) % mod;
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  mat ans = fi;
  while (n) {
    if (n & 1) ans = ans * fi;
    fi = fi * fi;
    n >>= 1;
  }
  printf("%d", ans.a[1][1]);
} 