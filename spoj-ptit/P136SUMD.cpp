#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int c, k;
  scanf("%d %d", &c, &k);
  int t = 1;
  while (k--) t *= 10;
  int r = c % t;
  if (r << 1 >= t) {
    printf("%d", c - r + t);
  } else {
    printf("%d", c - r);
  }
} 