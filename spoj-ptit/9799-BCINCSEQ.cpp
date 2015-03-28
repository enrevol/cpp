#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  int ans = 0;
  int cnt = 0;
  for (int i = 2; i <= n; ++i) {
    if (a[i] >= a[i - 1]) {
      ++cnt;
    } else {
      if (cnt > ans) ans = cnt;
      cnt = 0;      
    }
  }
  if (cnt > ans) ans = cnt;
  printf("%d", ans + 1);
} 