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

bool ok(int n) {
  int a[11], b[11], d = 0;
  while (n) {
    a[++d] = n % 10;
    n /= 10;
  }
  std::reverse_copy(a + 1, a + d + 1, b + 1);
  for (int i = 1; i <= d; ++i)
    if (a[i] != b[i]) return false;
  return true;
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  int ans = 0, ki, kj;
  for (int i = n - 1; i >= 1; --i)
    for (int j = 1; j < n; ++j) {
      int k = i * j;
      if (ok(k) && k >= ans) {
        ans = k;
        ki = i;
        kj = j;
      }
    }
  if (ans) printf("%d %d", ki, kj);
  else printf("0 0");
}