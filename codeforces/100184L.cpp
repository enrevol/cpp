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

int a[7][7];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  for (int i = 1; i <= 3; ++i)
    for (int j = 1; j <= 3; ++j)
      scanf("%d", a[i] + j);
  int ans = a[1][1] * (a[2][2] * a[3][3] - a[2][3] * a[3][2]) -
            a[1][2] * (a[2][1] * a[3][3] - a[2][3] * a[3][1]) +
            a[1][3] * (a[2][1] * a[3][2] - a[2][2] * a[3][1]);
  printf("%d", ans);
}