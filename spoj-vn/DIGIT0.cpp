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

int cnt[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  string s;
  cin >> s;
  int c[26] = { 0 };
  for (int i = 0; i < s.size(); ++i) {
    ++c[s[i] - 'a'];
  }
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= s.size(); ++i) {
    ++cnt[i];
  }
  for (int i = 0; i < 26; ++i)
    for (int j = 1; j <= c[i]; ++j)
      --cnt[j];
  int c2 = 0, c5 = 0;
  for (int i = s.size(); i > 1; --i) {
    if (cnt[i] == 0) continue;
//      cerr << "i = " << i << '\n';
    int tmp = i;
    while ((tmp & 1) == 0) c2 += cnt[i], tmp >>= 1;
    while ((tmp % 5) == 0) c5 += cnt[i], tmp /= 5;
  }
//    cerr << "c2 = " << c2 << " c5 = " << c5 << '\n';
  cout << min(c2, c5) << '\n';
}
