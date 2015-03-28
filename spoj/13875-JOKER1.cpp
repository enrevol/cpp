#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
const int mod = 1000000007;
int a[77];
long long ans[77];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    int f = 1;
    ans[1] = a[1];
    for (int i = 2; i <= n && f; ++i) {
      if (a[i] < i) f = 0;
      else ans[i] = (ans[i - 1] * (a[i] - (i - 1))) % mod;
    }
    if (f) printf("%lld\n", ans[n]);
    else puts("0");
  }
  puts("KILL BATMAN");
} 