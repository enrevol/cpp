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

const int N = 200010;

int a[N];
std::vector<int> p[N];

int ff(int v, int pos) {
  return std::upper_bound(p[v].begin(), p[v].end(), pos) - p[v].begin() - 1;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int sz = 0;
  while (n--) {
    int k, f, t, v;
    scanf("%d", &k);
    if (k == 0) {
      if (sz == 0) {
        puts("invalid");
      } else {
        p[a[sz]].pop_back();
        --sz;
      }
    } else {
      scanf("%d", &v);
      if (k == 1) {
        a[++sz] = v;
        p[v].push_back(sz);
      } else {
        scanf("%d %d", &f, &t);
        int ans = ff(v, t) - ff(v, f - 1);
        printf("%d\n", ans);
      }
    }
  }
}