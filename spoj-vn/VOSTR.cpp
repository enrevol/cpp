#include <algorithm>
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
 
const int base = 29;
 
const int N = 1e6;
 
char sa[N + 10];
char sb[N + 10];
 
unsigned hp[N + 10];
unsigned ha[N + 10];
unsigned hb[N + 10];
 
inline unsigned get(unsigned h[], int f, int t) {
  return h[t] - h[f - 1] * hp[t - f + 1];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  hp[0] = 1;
  for (int i = 1; i <= N; ++i)
    hp[i] = hp[i - 1] * base;
  int an, bn;
  scanf("%d %d", &an, &bn);
  scanf("%s %s", sa + 1, sb + 1);
  for (int i = 1; i <= an; ++i)
    ha[i] = ha[i - 1] * base + sa[i];
  for (int i = 1; i <= bn; ++i)
    hb[i] = hb[i - 1] * base + sb[i];
  int q;
  scanf("%d", &q);
  for (int af, at, bf, bt; q--; ) {
    scanf("%d %d %d %d", &af, &at, &bf, &bt);
    int pos = 0;
    int az = at - af + 1;
    int bz = bt - bf + 1;
    for (int lo = 1, hi = std::min(az, bz); lo <= hi; ) {
      int mi = (lo + hi) >> 1;
      if (get(ha, af, af + mi - 1) == get(hb, bf, bf + mi - 1)) {
        pos = mi;
        lo = mi + 1;
      } else {
        hi = mi - 1;
      }
    }
    if (az == bz) {
      if (pos == az) {
        putchar('=');
      } else {
        putchar(sa[af + pos] < sb[bf + pos] ? '<' : '>');
      }
    } else {
      if (pos == std::min(az, bz)) {
        putchar(az < bz ? '<' : '>');
      } else {
        putchar(sa[af + pos] < sb[bf + pos] ? '<' : '>');
      }
    }
  }
}