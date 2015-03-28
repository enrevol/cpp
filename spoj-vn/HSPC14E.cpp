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

const int N = 20010;
const int CYC = 8;
const int MOD = 1e8;
const int PHI = 4e7;

int pmod(int a, int b, const int m) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % m;
    a = 1ll * a * a % m;
    b >>= 1;
  }
  return res;
}

int ff(int a, int b, const int k) {
  long long val = 1;
  for (int i = 1; i <= b; ++i) {
    val = val * a;
    if (val <= 0 || val > k) return 1;
  }
  return 0;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int a, b;
  while (~scanf("%d %d", &a, &b)) {
    assert(a > 0 && b > 0);
    int val = a;    
    //int f = (b >= 2 && a >= 9) || (b >= 3 && a >= 3) || (b >= 5 && a >= 2);
    for (int i = 2; i < b; ++i) {
      int tmp = pmod(a, val, PHI);
      if (tmp < CYC && ff(a, val, CYC - 1))
        tmp += PHI;
      if (tmp == val) break;
      else val = tmp;
    }
    if (b > 1) val = pmod(a, val, MOD);
    //if (f) {
      int dn = 0;
      if (val == 0) dn = 1;
      else for (int tmp = val; tmp; tmp /= 10) ++dn;
      dn = 8 - dn;
      while (dn--) putchar('0');
    //}
    printf("%d\n", val);
  }
}
