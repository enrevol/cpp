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
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int x, y;
    scanf("%d %d", &x, &y);
    if (x == y) {
      printf("%d\n", (y & 1) + ((y >> 1) << 2));
    } else if (x == y + 2) {
      printf("%d\n", (y & 1) + ((y >> 1) << 2) + 2);
    } else {
      puts("No Number");
    }
  }
}