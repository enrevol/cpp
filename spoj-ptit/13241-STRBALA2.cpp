#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
char s[11][11];
int ans, n, a[11][11], cnt;
 
void dfs(const int& x, const int& y, int l, int r) {  
  if (a[x][y]) return;
  int ll = l + (s[x][y] == '(');
  int rr = r + (s[x][y] == ')');
  if (ll < rr) return;
  if (ll > l && r) return;
  //printf("%d %d %d %d\n", x, y, ll, rr);
  if (ll == rr && (ll << 1) > ans) ans = ll << 1;
  a[x][y] = 1;
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (1 <= xx && xx <= n && 1 <= yy && yy <= n) {
      dfs(xx, yy, ll, rr);
    }
  }
  a[x][y] = 0;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);  
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);  
  dfs(1, 1, 0, 0);
  printf("%d", ans);
} 