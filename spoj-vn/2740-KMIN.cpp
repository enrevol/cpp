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
 
int a[50505], b[50505], arr[50505];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int m, n, k;
  scanf("%d %d %d", &m, &n, &k);
  for (int i = 1; i <= m; ++i)
    scanf("%d", a + i);
  for (int i = 1; i <= n; ++i)
    scanf("%d", b + i);
  std::sort(a + 1, a + m + 1);
  std::sort(b + 1, b + n + 1);
  int lo = 1;
  int hi = 2e9;
  int val = -1;
  while (lo <= hi) {
    int mi = (1ll + lo + hi) >> 1;    
    int tot = 0;
    int j = n;
    for (int i = 1; i <= m && a[i] <= mi; ++i) {
      while (j >= 1 && a[i] + b[j] > mi)
        --j;
      if (j == 0) break;
      tot += j;
    }
    //fprintf(stderr, "lo = %d hi = %d mi = %d tot = %d\n", lo, hi, mi, tot);
    if (tot >= k) {
      val = mi;
      hi = mi - 1;
    } else {
      lo = mi + 1;
    }
  }
  //fprintf(stderr, "val = %d\n", val);
  int cnt = 0;
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n && a[i] + b[j] < val; ++j)
      arr[++cnt] = a[i] + b[j];
  while (cnt < k) arr[++cnt] = val;
  std::sort(arr + 1, arr + cnt + 1);  
  for (int i = 1; i <= k; ++i)
    printf("%d\n", arr[i]);
} 