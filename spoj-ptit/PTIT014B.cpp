#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
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
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int fx1, tx1, fy1, ty1;
    int fx2, tx2, fy2, ty2;
    scanf("%d %d %d %d", &fx1, &ty1, &tx1, &fy1);
    scanf("%d %d %d %d", &fx2, &ty2, &tx2, &fy2);
    if (tx2 < fx1 || fx2 > tx1 || ty2 > fy1 || fy2 < ty1) {
      puts("0");
    } else {
      puts("1");
    }
  }
} 