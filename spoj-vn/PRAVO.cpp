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

const int N = 1505;

struct point {
  int id, x, y;
  bool operator<(const point& p) const {    
    if (x != p.x) return x < p.x;
    if (y != p.y) return y < p.y;
    return id < p.id;
  }
} p[N], a[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &p[i].x, &p[i].y);
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int sz = 0;
    for (int j = 1; j <= n; ++j) {
      if (i == j) continue;
      int xx = p[j].x - p[i].x;
      int yy = p[j].y - p[i].y;
//      if (xx && yy) {
        int d = __gcd(xx, yy);
        xx /= d;
        yy /= d;
//      }
      if (yy < 0 || (yy == 0 && xx < 0)) {
        xx = -xx;
        yy = -yy;
      }
      ++sz;
      if (xx > 0) {
        a[sz].id = 0;
      } else {
        a[sz].id = 1;
        swap(xx, yy);
        yy = -yy;
      }
      a[sz].x = xx;
      a[sz].y = yy;
    }
//    DEBUG(0, i);
//    DEBUG(2, sz);
    sort(a + 1, a + sz + 1);
//    for (int j = 1; j <= sz; ++j) {
//      DEBUG(4, j);
//      DEBUG(4, a[j].x);
//      DEBUG(4, a[j].y);
//      DEBUG(4, a[j].id);
//    }
    for (int j = 1; j <= sz; ) {
      int cnt[2] = { 0 };
      int k = j;
      while (k <= sz && a[k].x == a[j].x && a[k].y == a[j].y) {
        ++cnt[a[k].id];
        ++k;
      }
      ans += cnt[0] * cnt[1];
      j = k;
    }
//    DEBUG(2, ans);
  }
  printf("%d", ans);
}
