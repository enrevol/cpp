#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int arr[101010], pf[101010];
bool sieve[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 3; i * i <= 100000; i += 2)
    if (!sieve[i])
      for (int j = i * i; j <= 100000; j += i)
        sieve[j] = true;
  int cnt = 0;
  arr[++cnt] = 2;
  for (int i = 3; i <= 100000; i += 2)
    if (!sieve[i])
      arr[++cnt] = i;
  for (int i = 1; i <= cnt; ++i)
    pf[i] = pf[i - 1] + arr[i];
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int l = 1;
    int r = cnt;
    int ans = 0;
    while (l <= cnt && arr[l] <= n) {
      if (pf[r] - pf[l - 1] > n) {
        --r;
      } else if (r + 1 <= cnt && pf[r + 1] - pf[l - 1] <= n) {
        ++r;
      } else {
        if (pf[r] - pf[l - 1] == n)
          ++ans;        
        ++l;
      }
    }
    printf("%d\n", ans);
  }
} 