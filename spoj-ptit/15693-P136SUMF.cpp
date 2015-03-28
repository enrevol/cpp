#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
p2 a[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].first, &a[i].second);
  std::sort(a + 1, a + n + 1);
  long long ans = 0;
  int t = 0;
  for (int i = 1; i <= n; ++i) {
    int d = a[i].second - t;
    if (d >= 0) {
      ans += d;
      t += d;
    } else {
      t = a[i].second;
    }
  }
  printf("%lld", ans);
} 