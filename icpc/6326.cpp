#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int a[111][111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  std::cin >> tt;
  while (tt--) {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        std::cin >> a[i][j];
    int ans = 0;
    bool b[111] = { false };
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        for (int k = i - 1; k <= i + 1; ++k)
          for (int l = j - 1; l <= j + 1; ++l)
            if (k != i || l != j)
              if (1 <= k && k <= n)
                if (1 <= l && l <= m)
                  if (a[i][j] == a[k][l])
                    b[a[i][j]] = true;
    for (int i = 1; i <= 100; ++i)
      ans += b[i];
    std::cout << ans << '\n';
  }
}