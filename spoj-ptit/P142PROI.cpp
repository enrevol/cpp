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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  int ans = 0;
  for (int i = 1; i < n; ++i) {
    bool f = true;
    int t = i;
    for (int j = 1; j < n - 1 && f; ++j) {
      t %= n;
      if (t == 1) f = false;
      t *= i;
    }
    if (f && t % n == 1) ++ans;
  }
  printf("%d", ans);
} 