#include <algorithm>
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
 
const int N = 500010;
 
int dx[N << 1], dy[N << 1];
int* ax = dx + N;
int* ay = dy + N;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  long long ans = 0;
  int x = 0;
  int y = 0;
  int cnt = 0;
  ++ax[0];
  ++ay[0];
  for (int i = 1; i <= n; ++i) {
    int v;
    scanf("%d", &v);
    int nx = x + (v <= k ? 1 : -1);
    int ny = y + (v >= k ? 1 : -1);
    if (nx > x && ny > y) {
      cnt += ax[x] + ay[ny];
    } else if (nx < x) {
      cnt += ay[ny] - ax[nx];
    } else {
      cnt += ax[x] - ay[y];
    }
    ans += cnt;
    ++ax[nx];
    ++ay[ny];
    x = nx;
    y = ny;
  }
  printf("%.10lf\n", 1.0 * ans / (1ll * n * (n + 1) / 2));
} 
