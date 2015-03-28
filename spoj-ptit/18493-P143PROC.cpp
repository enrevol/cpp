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
  int y, k, n;
  scanf("%d %d %d", &y, &k, &n);
  int t = (y / k  + 1) * k;
  int d = 0;
  while (t <= n) {
    printf("%d\n", t - y);
    t += k;
    ++d;
  }
  if (!d) printf("-1");
} 