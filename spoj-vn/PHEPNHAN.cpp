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
 
int x[1010101];
int y[1010101];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  int sz = 0;
  x[++sz] = k;
  int c = 0;
  bool f = false;
  for (int i = 1; i <= 1000000; ++i) {
    int v = (x[sz] * n) + c;
    y[sz] = v % 10;
    c = v / 10;
    if (y[sz] == k && c == 0 && x[sz] != 0) {      
      f = 1;
      break;
    }
    x[sz + 1] = y[sz];
    ++sz;
  }
  if (f) {
    for (int i = sz; i >= 1; --i)
      putchar(x[i] + '0');
  } else {
    printf("0");
  }
}