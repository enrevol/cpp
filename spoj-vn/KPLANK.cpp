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

int a[N], stack[N], l[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  stack[1] = 0;
  for (int i = 1, sz = 0; i <= n; ++i) {
    while (sz > 0 && a[stack[sz]] >= a[i]) --sz;
    l[i] = stack[sz] + 1;
    stack[++sz] = i;
  }
  int ans = 0;
  stack[1] = n + 1;
  for (int i = n, sz = 1; i >= 1; --i) {
    while (sz > 0 && a[stack[sz]] >= a[i]) --sz;
    int r = stack[sz] - 1;
    if (r - l[i] + 1 >= a[i] && a[i] > ans) {
      ans = a[i];
    }
    stack[++sz] = i;
  }
  cout << ans;
}
