#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int al[30303], ar[30303];
int bl[30303], br[30303];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    memset(al, 0, sizeof(al));
    int t;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &t);
      ++al[t];
    }
    for (int i = 30000; i >= 1; --i)
      ar[i] = ar[i + 1] + al[i];
    for (int i = 30000; i >= 1; --i)    
      br[i] = br[i + 1] + ar[i];
    for (int i = 1; i <= 30000; ++i)
      al[i] += al[i - 1];
    for (int i = 1; i <= 30000; ++i)
      bl[i] = bl[i - 1] + al[i];
    int ans = 1e9;
    for (int i = 1; i <= 30000; ++i)
      ans = std::min(ans, bl[i - 1] + br[i + 1]);
    printf("%d\n", ans);
  }
}