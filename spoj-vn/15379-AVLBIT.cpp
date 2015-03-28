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
 
const int N = 100010;
 
class ST {
  int arr[17][N];
  
 public:
  void build(const int data[], const int n, int ff(int, int)) {
    memcpy(arr[0], data, N * sizeof(int));
    for (int j = 1; 1 << j <= n; ++j)
      for (int i = 1; i + (1 << j) - 1 <= n; ++i)
        arr[j][i] = ff(arr[j - 1][i], arr[j - 1][i + (1 << (j - 1))]);
  }
  
  inline int query(const int f, const int t, int ff(int, int)) {
    assert(f <= t);
    int k = std::__lg(t - f + 1);
    return ff(arr[k][f], arr[k][t - (1 << k) + 1]);
  }
} stmax, stmin, stgcd, stpos;
 
inline int ffmax(int x, int y) { return std::max(x, y); }
inline int ffmin(int x, int y) { return std::min(x, y); }
inline int ffgcd(int x, int y) { return std::__gcd(x, y); }
 
int a[N], b[N], p[N];
std::map<int, int> idx;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, q;
  scanf("%d %d", &n, &q);
  memset(p, 0x3c, N * sizeof(int));
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    int pos = idx[a[i]];
    if (pos > 0) p[pos] = i;
    idx[a[i]] = i;
  }
  for (int i = 1; i < n; ++i)
    b[i] = a[i + 1] - a[i];
  stmax.build(a, n, ffmax);
  stmin.build(a, n, ffmin);
  stgcd.build(b, n - 1, ffgcd);
  stpos.build(p, n, ffmin);
  for (int f, t; q--; ) {
    scanf("%d %d", &f, &t);
    int max = stmax.query(f, t, ffmax);
    int min = stmin.query(f, t, ffmin);
    //fprintf(stderr, "max = %d min = %d\n", max, min);
    if (max == min) {
      puts("NO");
    } else {
      int dif = max - min;
      int num = t - f + 1;
      //fprintf(stderr, "dif = %d num = %d\n", dif, num);
      if (dif % (num - 1) > 0) {
        puts("NO");
      } else {
        int dt = dif / (num - 1);
        int gcd = std::abs(stgcd.query(f, t - 1, ffgcd));
        int pos = stpos.query(f, t, ffmin);
        //fprintf(stderr, "dt = %d gcd = %d pos = %d\n", dt, gcd, pos);
        //if (pos > t && gcd == dt) {
        if (pos > t && gcd == dt) {
          puts("YES");
        } else {
          puts("NO");
        }
      }
    }
  }
}