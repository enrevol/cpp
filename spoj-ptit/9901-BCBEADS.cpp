#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
int a[101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  int ans = 0;
  for (int i = 2; i <= n; ++i)
    ans += a[i] != a[i - 1];
  printf("%d", ans);
} 