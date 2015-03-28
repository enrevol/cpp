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

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MOD3 = 1e9 + 21;

const int N = 2500010;

struct ele {
  int h1, h2, h3;
  ele(int h1 = 0, int h2 = 0, int h3 = 0) : h1(h1), h2(h2), h3(h3) { }
  friend ele operator+(const ele& x, const ele& y) {
    return ele((x.h1 + y.h1) % MOD1, (x.h2 + y.h2) % MOD2, (x.h3 + y.h3) % MOD3);
  }
  bool operator<(const ele& e) const {
    if (h1 != e.h1) return h1 < e.h1;
    if (h2 != e.h2) return h2 < e.h2;
    return h3 < e.h3;
  }
} fi[N];

char s[N];

int get(const int MOD) {
  int r = 0;
  for (int i = 0; s[i]; ++i) {
    r = (1ll * r * 10 + s[i] - '0') % MOD;
  }
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  fi[0] = fi[1] = ele(1, 1, 1);
  fi[2] = ele(2, 2, 2);
  for (int i = 3; i < N; ++i) {
    fi[i] = fi[i - 1] + fi[i - 2];
  }
  std::sort(fi, fi + N);
  int n;
  scanf("%d", &n);
  while (n--) {
    scanf("%s", s);
    int h1 = get(MOD1);
    int h2 = get(MOD2);
    int h3 = get(MOD3);
    int ans = std::binary_search(fi, fi + N, ele(h1, h2, h3));
    puts(ans ? "Yes" : "No");
  }
}
