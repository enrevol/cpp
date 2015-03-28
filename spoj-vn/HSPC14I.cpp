#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int x, y, z;
  while (~scanf("%d %d %d", &x, &y, &z)) {
    int a[5] = { x, y, z };
    std::sort(a, a + 3);
    int d = std::max(a[1] - a[0], a[2] - a[1]);
    printf("%d\n", d - 1);
  }
}

