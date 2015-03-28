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

int d, k;
long long a, b, dp[20][20][20], p[20];

long long solve(long long prefix, int remain, int bad, int last) {  
  long long f = prefix * p[remain];
  long long t = f + p[remain] - 1;
  if (t < a || f > b) {
    return 0;
  }
  if (a <= f && t <= b && dp[remain][bad][last] != -1) {
    return dp[remain][bad][last];
  }
  if (remain == 0) {
//    cerr << prefix << ' ' << last << ' ' << bad << '\n';
    return last != -1 && bad <= k;
  }
  long long r = 0;
  for (int dig = 0; dig <= 9; ++dig) {
    if (prefix || dig) {
      int nbad = bad;
      if (last != -1) nbad += abs(dig - last) <= d;
      if (nbad <= k) {
        r += solve(prefix * 10 + dig, remain - 1, nbad, dig);
      }
    }
  }
  if (a <= f && t <= b) {
    dp[remain][bad][last] = r;
  }
//  cerr << prefix << ' ' << remain << ' ' << bad << ' ' << last << ' ' << r << '\n';
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  cin >> a >> b >> d >> k;
  p[0] = 1;
  for (int i = 1; i < 20; ++i)
    p[i] = p[i - 1] * 10;
  memset(dp, -1, sizeof(dp));
  long long ans = 0;
  for (int digs = 1; digs < 17; ++digs)
    ans += solve(0, digs, 0, -1);
  cout << ans;
}
