SPOJ submission 11207006 (C++ 4.3.2) plaintext list. Status: AC, problem P145PROI, contest ACMPTIT. By enrevol (What Does The Fox Say?), 2014-03-08 03:34:55.
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
char s[1010101];
int a[1010101], b[1010101], c[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    a[i] = a[i - 1] + ('A' <= s[i] && s[i] <= 'Z');
    b[i] = b[i - 1] + ('a' <= s[i] && s[i] <= 'z');
    c[i] = c[i - 1] + ('0' <= s[i] && s[i] <= '9');
  }
  long long ans = 0;
  int it = 1;
  for (int i = 1; i <= n; ++i) {
    while (it < n && (a[it] - a[i - 1] == 0 || b[it] - b[i - 1] == 0 || c[it] - c[i - 1] == 0)) {
      ++it;
    }
    while (it - i + 1 < 6) ++it;
    if (it <= n && a[it] - a[i - 1] >= 1 && b[it] - b[i - 1] >= 1 && c[it] - c[i - 1] >= 1) {
      ans += n - it + 1;
    } else {
      break;
    }
  }
  printf("%lld", ans);
} 