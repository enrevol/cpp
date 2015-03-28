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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }

using namespace std;

const int N = 250010;

int a[N], tree[18][65537];

inline void insert(int x) {
  for (int i = 0; i < 17; ++i) {
    ++tree[i][x];
    x >>= 1;
  }
}

inline void erase(int x) {
  for (int i = 0; i < 17; ++i) {
    --tree[i][x];
    x >>= 1;
  }
}

inline int find(int x) {
  int a = 0, b = 16;
  while (b--) {
    a <<= 1;
    if (tree[b][a] < x) {
      x -= tree[b][a++];
    }
  }
  return a;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  for (int tn = 1; tn <= tt; ++tn) {
    int seed, mul, add, n, k;
    scanf("%d %d %d %d %d", &seed, &mul, &add, &n, &k);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      a[i] = seed;
      seed = (1LL * seed * mul + add) & 65535;
      insert(a[i]);
      if (i >= k) {
        ans += find((k + 1) >> 1);
        erase(a[i - k + 1]);
      }
    }
    for (int i = n - k + 2; i <= n; ++i) {
      erase(a[i]);
    }
    printf("Case #%d: %lld\n", tn, ans);
  }
}
