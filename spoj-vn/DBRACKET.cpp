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
 
char s[N];
int gap, n;
int rank[N], sa[N], lcp[N], tmp[N], dp[17][N], a[N];
std::vector<int> pos[N << 1];
 
int query(int f, int t) {
  assert(f <= t);
  int k = std::__lg(t - f + 1);
  return std::min(dp[k][f], dp[k][t - (1 << k) + 1]);
}
 
bool cmp(int i, int j) {
  if (rank[i] != rank[j]) return rank[i] < rank[j];
  i += gap;
  j += gap;
  if (i <= n && j <= n) return rank[i] < rank[j];
  return i > j;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  tmp[1] = 1;
  a[0] = N;
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 0; i < N << 1; ++i) pos[i].clear();
    for (int i = 1; i <= n; ++i) {
      a[i] = a[i - 1] + (s[i] == '(' ? 1 : -1);
      dp[0][i] = a[i];
      pos[a[i]].push_back(i);
    }
    for (int j = 1; 1 << j <= n; ++j)
      for (int i = 1; i + (1 << j) - 1 <= n; ++i)
        dp[j][i] = std::min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
    for (int i = 1; i <= n; ++i) {
      sa[i] = i;
      rank[i] = s[i];
    }
    for (gap = 1; ; gap <<= 1) {
      std::sort(sa + 1, sa + n + 1, cmp);
      for (int i = 2; i <= n; ++i)
        tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
      for (int i = 1; i <= n; ++i)
        rank[sa[i]] = tmp[i];
      if (tmp[n] == n) break;
    }
    for (int i = 1, k = 0; i <= n; ++i) {
      if (rank[i] == n) continue;
      for (int j = sa[rank[i] + 1]; s[i + k] == s[j + k]; )
        ++k;
      lcp[rank[i]] = k;
      if (k) --k;
    }
    lcp[n] = 0;
    long long ans = 0;
    for (int i = 1, right = 1; i <= n; ++i) {
      if (right < lcp[i - 1]) {
        lcp[i] = std::min(lcp[i], lcp[i - 1]);
      } else {
        int val = a[sa[i] - 1];
        int lb = sa[i] + lcp[i - 1] - 1;
        int rb = lb;
        for (int f = lb + 1, t = n; f <= t; ) {
          int m = (f + t) >> 1;
          if (query(f, m) >= val) {
            rb = m;
            f = m + 1;
          } else {
            t = m - 1;
          }
        }
        int lv = std::upper_bound(pos[val].begin(), pos[val].end(), lb) - pos[val].begin();
        int rv = std::upper_bound(pos[val].begin(), pos[val].end(), rb) - pos[val].begin();
        ans += rv - lv;
        right = rb - sa[i] + 1;
      }
    }
    printf("%lld\n", ans);
  }
}