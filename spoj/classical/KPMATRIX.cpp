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

const int N = 255;

int a[N][N], col[N][N];

inline int query(int fw[N], int p) {
  int r = 0;
  while (p) {
    r += fw[p];
    p &= p - 1;
  }
  return r;
}

inline void update(int fw[N], int n, int p) {
  while (p <= n) {
    ++fw[p];
    p += p & -p;
  }  
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", a[i] + j);
      col[j][i] = col[j][i - 1] + a[i][j];
    }
  int l, r;
  scanf("%d %d", &l, &r);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int ii = 0; ii < i; ++ii) {
      int arr[N];
      arr[1] = 0;
      for (int j = 1; j < m; ++j) {
        arr[j + 1] = arr[j] + col[j][i] - col[j][ii];
      }
      std::sort(arr + 1, arr + m + 1);
      int an = std::unique(arr + 1, arr + m + 1) - arr - 1;
      int fw[N];
      memset(fw + 1, 0, an << 2);
      int sum = 0;
      for (int j = 1; j <= m; ++j) {
        int pos = std::lower_bound(arr + 1, arr + an + 1, sum) - arr;
        update(fw, an, pos);
        sum += col[j][i] - col[j][ii];
        int ll = std::lower_bound(arr + 1, arr + an + 1, sum - r) - arr;
        int rr = std::upper_bound(arr + ll, arr + an + 1, sum - l) - arr - 1;
        ans += query(fw, rr) - query(fw, ll - 1);
      }
    }
  }
  printf("%lld", ans);
}