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
 
char fr[2020202];
char pat[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int x, y;
    scanf("%d %d %s", &x, &y, pat + 1);
    int pz = strlen(pat + 1);
    int sz = 0;
    int v = x / y;
    if (v) {
      while (v) {
        fr[++sz] = (v % 10) + '0';
        v /= 10;
      }
      std::reverse(fr + 1, fr + sz + 1);
    } else {
      fr[++sz] = '0';
    }
    x %= y;
    for (int i = 1; i <= (y << 1) || i <= (pz << 1); ++i) {
      if (x) {
        x += (x << 3) + x;
        while (x < y) {
          x += (x << 3) + x;
          fr[++sz] = '0';
          ++i;
        }
        fr[++sz] = (x / y) + '0';
        x %= y;
      } else {
        fr[++sz] = '0';
      }
    }
    fr[sz + 1] = 0;
    const char* res = strstr(fr + 1, pat + 1);
    if (res != NULL) {
      printf("%d\n", res - fr);
    } else {
      puts("0");
    }
  }
}  