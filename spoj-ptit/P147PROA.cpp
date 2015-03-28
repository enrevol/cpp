#include <algorithm>
#include <cassert>
#include <cmath>
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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  int t = sqrt(1ll * a * b * c);
  a = t / a;
  b = t / b;
  c = t / c;
  printf("%d", (a + b + c) << 2);
} 