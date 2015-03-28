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
 
int pos[101010];
int fw[202020];
 
void update(int i, int v) {
  for ( ; i; i -= i & -i)
    fw[i] += v;
}
 
int query(int i, int n) {
  int res = 0;
  for ( ; i <= n; i += i & -i)
    res += fw[i];
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    memset(fw, 0, sizeof(fw));
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      pos[i] = n + 1 - i;
      update(i - 1, 1);
    }
    while (m--) {
      int x;
      scanf("%d", &x);
      printf("%d ", query(pos[x], n));
      update(pos[x], -1);
      pos[x] = ++n;
      update(pos[x] - 1, 1);
    }
    putchar('\n');
  }
}