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
  int fx, fy, tx, ty;
  scanf("%d %d %d %d", &fx, &fy, &tx, &ty);
  int dx = abs(fx - tx);
  int dy = abs(fy - ty);
  printf("%d %d %d", 2 - (fx == tx) - (fy == ty), (dx - dy) & 1 ? 0 : 2 - (dx == dy) - (fx == tx && fy == ty), std::max(dx, dy));
} 