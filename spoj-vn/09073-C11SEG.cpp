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
 
int n;
int a[101010];
int id[101010];
int pos[101010];
int fw[101010];
long long sum[101010];
 
bool cmp(int i, int j) {
  return sum[i] < sum[j];
}
 
void update(int i) {
  for ( ; i <= n; i += i & -i)
    ++fw[i];
}
 
int query(int i) {
  int res = 0;
  for ( ; i; i -= i & -i)
    res += fw[i];
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int lb, rb;
  scanf("%d %d %d", &n, &lb, &rb);  
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum[i] = sum[i - 1] + a[i];
    id[i] = i;
  }
  std::sort(id + 1, id + n + 1, cmp);
  for (int i = 1; i <= n; ++i)
    pos[id[i]] = i;
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += lb <= sum[i] && sum[i] <= rb;
    int lp = -1;    
    int rp = -1;
    for (int lo = 1, hi = n; lo <= hi; ) {
      int mi = (lo + hi) >> 1;
      long long v = sum[i] - sum[id[mi]];
      if (v <= rb) hi = mi - 1, lp = mi;
      else lo = mi + 1;
    }
    for (int lo = 1, hi = n; lo <= hi; ) {
      int mi = (lo + hi) >> 1;
      long long v = sum[i] - sum[id[mi]];
      if (v >= lb) lo = mi + 1, rp = mi;
      else hi = mi - 1;
    }
    if (lp != -1 && rp != -1)
      if (lp <= rp)
        ans += query(rp) - query(lp - 1);
    update(pos[i]);
  }
  printf("%lld", ans);
}