#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::map<int, int> s;
int a[1010101], b[1010101];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    s.clear();
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      b[i] = b[i - 1] + a[i];
      ++s[b[i]];
    }
    ++s[0];
    long long ans = 0;
    for (int i = 0; i <= n; ++i)
      ans += s[b[i]] - 1;
    printf("%lld\n", ans >> 1);
  }
} 