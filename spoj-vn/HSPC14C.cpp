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

const int N = 20000010;

int p[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  for (int m = 1; m * (m + 1) < N; m += 2) {
    for (int n = 1; n < m; n += 2) {
      int ssum = m * (m + n);
      int sp = (min(m * n, m * m - n * n) << 16) + m * m + n * n;
      for (int sum = ssum, pp = sp; sum < N ; sum += ssum, pp += sp) {
        if (p[sum] == -1 || p[sum] == pp) {
          continue;
        }
        if (!p[sum]) {
          p[sum] = pp;
          continue;
        }
        p[sum] = -1;
      }
    }
  }
  for (int i = 1; i < N; ++i) {
    p[i] = p[i - 1] + (p[i] < -1 || p[i] > 0);
  }
  int x;
  while (cin >> x) {
    cout << p[x] << '\n';
  }
}
