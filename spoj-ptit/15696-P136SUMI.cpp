#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
bool b[365];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k, t;
  scanf("%d %d", &n, &k);
  b[0] = true;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    std::vector<int> v;
    int e = 0;
    for (int j = 1; j < 360; ++j) {
      e += t;
      if (e >= 360) e -= 360;
      v.push_back(e);
    }
    for (int j = 0; j <= 359; ++j)
      if (b[j])
        for (size_t p = 0; p < v.size(); ++p)
          b[(j + v[p]) % 360] = true;
  }
  while (k--) {
    scanf("%d", &t);
    puts(b[t] ? "YES" : "NO");
  }
} 