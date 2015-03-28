SPOJ submission 11158603 (C++ 4.3.2) plaintext list. Status: AC, problem P144PROI, contest ACMPTIT. By enrevol (What Does The Fox Say?), 2014-03-01 03:22:20.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int l[111], r[111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", l + i, r + i);
  int ans = -1;
  int sz = -1;
  for (int i = 1; i <= n; ++i) {
    bool f = true;
    for (int j = 1; j <= n && f; ++j)
      f = l[i] <= l[j] && r[j] <= r[i];
    if (f) {
      if (sz == -1 || r[i] - l[i] + 1 > sz) {
        ans = i;
        sz = r[i] - l[i] + 1;
      } else if (r[i] - l[i] + 1 == sz) {        
        ans = -1;
      }
    }
  }
  printf("%d", ans);
} 