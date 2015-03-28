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
 
const int N = 10010;
const int SZ = 210;
 
int a[N];
long long dp[N];

namespace median_heap {
  
int median;
int lsz, lower[SZ];
int usz, upper[SZ];

long long lsum, usum;

void init() {
  median = -1;
  lsz = usz = 0;
  lsum = usum = 0;
}

void insert(int x) {
  if (median == -1) {
    median = x;    
  } else {
    int h = (lsz + usz + 1) >> 1;
    if (x < median) {
      if (lsz < h) {
        lower[lsz++] = x;
        push_heap(lower, lower + lsz);
        lsum += x;
      } else {
        upper[usz++] = median;
        push_heap(upper, upper + usz, greater<int>());
        usum += median;
        if (lsz == 0 || x >= lower[0]) {
          median = x;
        } else {
          median = lower[0];
          lsum = lsum - lower[0] + x;
          pop_heap(lower, lower + lsz);
          lower[lsz - 1] = x;
          push_heap(lower, lower + lsz);
        }
      }
    } else {
      if (lsz >= h) {
        upper[usz++] = x;
        push_heap(upper, upper + usz, greater<int>());
        usum += x;
      } else {
        lower[lsz++] = median;
        push_heap(lower, lower + lsz);
        lsum += median;
        if (usz == 0 || x <= upper[0]) {
          median = x;
        } else {
          median = upper[0];
          usum = usum - upper[0] + x;
          pop_heap(upper, upper + usz, greater<int>());
          upper[usz - 1] = x;
          push_heap(upper, upper + usz, greater<int>());
        }
      }
    }
  }
}

inline long long query() {
  long long l = 1LL * median * lsz - lsum;
  long long u = usum - 1LL * median * usz;
  return l + u;
}
  
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
  }
  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    int lim = max(i - k - k + 1, 1);
    median_heap::init();
    for (int j = i; j >= lim; --j) {
      median_heap::insert(a[j]);
      if (i - j + 1 >= k && ~dp[j - 1]) {
        long long v = dp[j - 1] + median_heap::query();
        if (dp[i] == -1 || dp[i] > v) {
          dp[i] = v;
        }
      }
    }
//    printf("%d = %lld\n", i, dp[i]);
  }
  printf("%lld", dp[n]);  
}
