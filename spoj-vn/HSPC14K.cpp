#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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
 
const int N = 1010;

int n, m; 
long long fxy[N][N], fx[N][N], fy[N][N], f[N][N];
 
void update(long long fw[N][N], int a, int b, long long v) {
  for (int i = a; i <= n; i += i & -i)
    for (int j = b; j <= m; j += j & -j)
      fw[i][j] += v;
}
 
long long query(long long fw[N][N], int a, int b) {
  long long res = 0;
  for (int i = a; i; i &= i - 1)
    for (int j = b; j; j &= j - 1)
      res += fw[i][j];
  return res;
}
 
long long query(int x, int y) {
  return query(fxy, x, y) * x * y + query(fx, x, y) * x + query(fy, x, y) * y + query(f, x, y);
}
 
long long query(int a, int b, int x, int y) {
  return query(x, y) - query(x, b - 1) - query(a - 1, y) + query(a - 1, b - 1);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int q;
  std::cin >> n >> m >> q;
  while (q--) {
    int k, a, b, x, y;
    long long w;
    std::cin >> k >> a >> b >> x >> y;;
    if (k == 1) {
      std::cin >> w;
      update(fxy, a, b, w);
      update(fxy, a, y + 1, -w);
      update(fxy, x + 1, b, -w);
      update(fxy, x + 1, y + 1, w);      
      long long v1 = (1 - b) * w;
      long long v2 = (y - b + 1) * w;      
      update(fx, a, b, v1);
      update(fx, a, y + 1, v2 - v1);
      update(fx, x + 1, b, -v1);
      update(fx, x + 1, y + 1, v1 - v2);      
      long long v3 = (1 - a) * w;
      long long v4 = (x - a + 1) * w;
      update(fy, a, b, v3);
      update(fy, x + 1, b, v4 - v3);
      update(fy, a, y + 1, -v3);
      update(fy, x + 1, y + 1, v3 - v4);    
      long long v5 = (a - 1) * (b - 1) * w;
      long long v6 = (1 - a) * (y - b + 1) * w;
      long long v7 = (1 - b) * (x - a + 1) * w;
      long long v8 = (x - a + 1) * (y - b + 1) * w;
      update(f, a, b, v5);
      update(f, a, y + 1, v6 - v5);
      update(f, x + 1, b, v7 - v5);
      update(f, x + 1, y + 1, v8 + v5 - v6 - v7);
    } else {      
      std::cout << query(a, b, x, y) << '\n';
    }
  }
}
 
