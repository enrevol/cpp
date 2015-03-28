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

const int N = 1000010;
const int MOD = 1e9 + 7;

int a[N], dp[N], z[N], fact[N];
long long s[N];

int pmod(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1) r = 1LL * r * a % MOD;
    a = 1LL * a * a % MOD;
    b >>= 1;
  }
  return r;
}

int nCk(int n, int k) {
  return 1LL * fact[n] * pmod(1LL * fact[n - k] * fact[k] % MOD, MOD - 2) % MOD;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  int ans = 0;  
//  cerr << "s[n] = " << s[n] << '\n';
  if (s[n] % k == 0) {
    long long ss = s[n] / k;
//    cerr << "ss = " << ss << '\n';
    if (ss == 0) {
      int cnt = 0;
      for (int i = 1; i <= n; ++i) {
        cnt += s[i] == 0;
      }
      fact[0] = 1;
      for (int i = 1; i <= cnt - 1; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
      }
      ans = nCk(cnt - 1, k - 1);
    } else {
      dp[0] = 1;
      for (int i = 1; i <= n; ++i) {
        if (s[i] % ss == 0) {
          int id = s[i] / ss;
          int v = dp[id - 1];
          z[i] = v;
          dp[id] = (dp[id] + v) % MOD;
        }
      }
      ans = z[n];
    }
  }
  cout << ans;
}
