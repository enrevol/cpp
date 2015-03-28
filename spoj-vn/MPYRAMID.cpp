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

const int N = 1010;

int n, m, a, b, c, d;
int h[N][N], sum[N][N];
deque<pair<int, int> > deq[N];

inline int calc(int x1, int y1, int x2, int y2) {
  return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
}

inline int calc(int x, int y) {
  return calc(x, y, x + c - 1, y + d - 1);
}

inline void rem(pair<int, int> p, deque<pair<int, int> >& d) {
  while (d.front() < p) {
    d.pop_front();
  }
}

inline void add(pair<int, int> p, deque<pair<int, int> >& d) {
  while (!d.empty() && calc(d.back().first, d.back().second) >= calc(p.first, p.second)) {
    d.pop_back();
  }
  d.push_back(p);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> m >> n >> b >> a >> d >> c;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      cin >> h[i][j];
      sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + h[i][j];
    }
  int aa = 0, bb = 0, cc = 0, dd = 0, vv = 0;
  for (int i = 2; i + c - 1 + 1 <= a - 1; ++i)
    for (int j = 2; j + d - 1 <= m - 1; ++j) {
      add(make_pair(i, j), deq[j]);
    }
  for (int i = 1; i + a - 1 <= n; ++i) {
//    cerr << "i = " << i << '\n';
    for (int j = 2; j + d - 1 <= m - 1; ++j) {
      add(make_pair(i + a - 1 - 1 - c + 1, j), deq[j]);
      rem(make_pair(i + 1, 0), deq[j]);
    }
    deque<pair<int, int> > row;
    for (int j = 2; j + d - 1 + 1 <= b - 1; ++j) {
      add(deq[j].front(), row);
    }
    for (int j = 1; j + b - 1 <= m; ++j) {
//      cerr << "  j = " << j << '\n';
      int s = calc(i, j, i + a - 1, j + b - 1);
      add(deq[j + b - 1 - 1 - d + 1].front(), row);
      while (row.front().second < j + 1) row.pop_front();
      int ii = row.front().first;
      int jj = row.front().second;
      int x = calc(ii, jj);
      int v = s - x;
      if (v > vv) {
        vv = v;
        aa = i;
        bb = j;
        cc = ii;
        dd = jj;
      }
    }
  }
//  cerr << "vv = " << vv << '\n';
  cout << bb << ' ' << aa << '\n' << dd << ' ' << cc;
}
