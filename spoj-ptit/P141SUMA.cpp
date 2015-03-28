#include <algorithm>
#include <cassert>
#include <cmath>
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
 
long long ccw(long long ax, long long ay,
              long long bx, long long by,
              long long cx, long long cy) {
  long long ux = ax - bx;
  long long uy = ay - by;
  long long vx = cx - bx;
  long long vy = cy - by;
  return ux * vy - uy * vx;
}
 
long long sqr(long long x) {
  return x * x;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  long long ax, ay, bx, by, cx, cy;
  scanf("%lld %lld %lld %lld %lld %lld", &ax, &ay, &bx, &by, &cx, &cy);
  long long ab = sqr(ax - bx) + sqr(ay - by);
  long long bc = sqr(bx - cx) + sqr(by - cy);
  long long ca = sqr(cx - ax) + sqr(cy - ay);
  if (ab + bc == ca) {
    if (ccw(ax, ay, bx, by, cx, cy) > 0) {
      puts("RIGHT");
    } else {
      puts("LEFT");
    }    
  } else {
    printf("TOWARDS");
  }
}