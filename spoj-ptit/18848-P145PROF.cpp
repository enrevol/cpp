#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[24][60];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int x, y;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &x, &y);
    ++a[x][y];
  }
  int ans = 0;
  for (int i = 0; i <= 23; ++i)
    for (int j = 0; j <= 59; ++j)
      if (a[i][j] > ans)
        ans = a[i][j];
  printf("%d", ans);
} 