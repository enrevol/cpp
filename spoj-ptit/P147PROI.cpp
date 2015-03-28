#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int a[1010101];
int b[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int m, n;
  scanf("%d %d", &n, &m);
  for (int i = 0; i <= n; ++i)
    scanf("%d", a + i);
  for (int i = 0; i <= m; ++i)
    scanf("%d", b + i);
  if (n < m) {
    puts("0/1");
  } else if (n > m) {
    if (a[0] * b[0] < 0) putchar('-');
    puts("Infinity");
  } else {
    int g = std::__gcd(a[0], b[0]);
    printf("%d/%d", a[0] / g, b[0] / g);
  }
} 