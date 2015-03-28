#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <queue>
#define r first
#define c second
#define pLL pair<LL, LL>
#define mp make_pair
typedef long long LL;
using namespace std;
LL grid[111][111];
bool check(LL posR, LL posC, LL val) {
  if (grid[posR][posC] < 0 || grid[posR][posC] > val) {
    grid[posR][posC] = val;
    return 1;
  }
  return 0;
}
int main() {
  LL R, C, d;
  pLL Gpos, Lpos, t;
  while (cin >> R >> C >> Gpos.r >> Gpos.c >> Lpos.r >> Lpos.c) {
    memset(grid, -1, sizeof(grid));
    queue<pLL> q;
    q.push(Gpos);
    grid[Gpos.r][Gpos.c] = 0;
    while (!q.empty()) {
      t = q.front();
      d = grid[t.r][t.c] + 1;
      q.pop();
      if (t.r >= 2) {
        if (t.c >= 3     && check(t.r - 1, t.c - 2, d)) q.push(mp(t.r - 1, t.c - 2));
        if (t.c <= C - 2 && check(t.r - 1, t.c + 2, d)) q.push(mp(t.r - 1, t.c + 2));
      }
      if (t.r >= 3) {
        if (t.c >= 2     && check(t.r - 2, t.c - 1, d)) q.push(mp(t.r - 2, t.c - 1));
        if (t.c <= C - 1 && check(t.r - 2, t.c + 1, d)) q.push(mp(t.r - 2, t.c + 1));
      }
      if (t.r <= R - 2) {
        if (t.c >= 2     && check(t.r + 2, t.c - 1, d)) q.push(mp(t.r + 2, t.c - 1));
        if (t.c <= C - 1 && check(t.r + 2, t.c + 1, d)) q.push(mp(t.r + 2, t.c + 1));
      }
      if (t.r <= R - 1) {
        if (t.c >= 3     && check(t.r + 1, t.c - 2, d)) q.push(mp(t.r + 1, t.c - 2));
        if (t.c <= C - 2 && check(t.r + 1, t.c + 2, d)) q.push(mp(t.r + 1, t.c + 2));
      }
    }
    if (grid[Lpos.r][Lpos.c] < 0) cout << "impossible\n";
    else cout << grid[Lpos.r][Lpos.c] << '\n';
  }
}