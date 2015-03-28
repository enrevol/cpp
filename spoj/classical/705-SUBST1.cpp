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
 
const int mx = 5e4;
 
char s[mx + 10];
 
int rank[mx + 10];
int sa[mx + 10];
int tmp[mx + 10];
int lcp[mx + 10];
 
int n, gap;
 
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
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
      sa[i] = i;
      rank[i] = s[i];
    }
    for (gap = 1, tmp[1] = 1; ; gap <<= 1) {
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
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
      ans += (n - sa[i] + 1) - lcp[i];
    printf("%lld\n", ans);
  }
}