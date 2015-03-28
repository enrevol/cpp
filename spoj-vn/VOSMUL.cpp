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

#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }

using namespace std;

const int N = 100010;

struct factor {
  int prime, power;
  bool operator<(const factor& f) const {
    return prime < f.prime;
  }
} b[N];

struct element {
  int power, index;
  element() { }
  element(int power, int index) : power(power), index(index) { }
};

int n, m, a[N], cnt[N];
vector<element> fact[N];

inline int search(int val) {
  for (int low = 1, high = m; low <= high; ) {
    int mid = (low + high) >> 1;
    if (val == b[mid].prime) return mid;
    if (val < b[mid].prime) high = mid - 1;
    else low = mid + 1;
  }
  return 0;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {    
    scanf("%d", a + i);
  }  
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &b[i].prime, &b[i].power);
  }
  int lack = m;
  sort(b + 1, b + m + 1);
  for (int i = 1; i <= n; ++i) {
    int v = a[i];
    int low = 1;
    for (int j = 1; j <= m && 1LL * b[j].prime * b[j].prime <= v; ++j) {
      int k = b[j].prime;
      if (v % k == 0) {
        fact[i].push_back(element(0, j));
        do {
          ++fact[i].back().power;
          v /= k;
        } while (v % k == 0);
      }
    }
    if (v > 1) {
      int index = search(v);
      if (index > 0) {
        fact[i].push_back(element(1, index));
      }
    }
  }
  long long ans = 0;
  for (int i = 1, j = 0; i <= n; ++i) {
    while (j < n && lack > 0) {
      ++j;
      for (int k = 0; k < fact[j].size(); ++k) {
        int power = fact[j][k].power;
        int index = fact[j][k].index;
        int n_cnt = cnt[index] + power;
        lack -= cnt[index] < b[index].power && b[index].power <= n_cnt;
        cnt[index] = n_cnt;
      }
    }
    if (lack > 0) break;
    ans += n - j + 1;
    for (int k = 0; k < fact[i].size(); ++k) {
      int power = fact[i][k].power;
      int index = fact[i][k].index;
      int n_cnt = cnt[index] - power;
      lack += cnt[index] >= b[index].power && b[index].power > n_cnt;
      cnt[index] = n_cnt;
    }
  }
  printf("%lld", ans);
}
