#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[33][33];
bool g[33][33];
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
typedef std::pair<int, int> p2;
 
std::set<p2> st[33][33];
 
int n, m;
int need;
int ans;
 
inline bool valid(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m && !g[x][y] && s[x][y] == '.';
}
 
void solve(int x, int y, int d, int cover, int turn) {
  if (d == -1) {
    bool end = true;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i];
      int yy = y + dy[i];
      if (valid(xx, yy)) {
        end = false;
        solve(x, y, i, cover, turn);
      }
    }
    if (end)
      if (cover == need)
        if (ans == -1 || turn < ans)
          ans = turn;
  } else {
    int xx = x + dx[d];
    int yy = y + dy[d];
    if (valid(xx, yy)) {
      g[xx][yy] = true;
      solve(xx, yy, d, cover + 1, turn);
      g[xx][yy] = false;
    } else{
      solve(x, y, -1, cover, turn + 1);
    }
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int nc = 0;
  while (~scanf("%d %d", &n, &m)) {
    if (n | m) {
      need = 0;
      for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; ++j)
          need += s[i][j] == '.';
      }
      ans = -1;
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
          if (s[i][j] == '.') {
            g[i][j] = true;
            solve(i, j, -1, 1, 0);
            g[i][j] = false;
          }
      printf("Case %d: %d\n", ++nc, ans);
    }
  }
} 