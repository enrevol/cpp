#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
char s[2020], ans[2020];
int dp[2020][2020];
p2 tr[2020][2020];
 
int solve(int f, int t) {
  int& res = dp[f][t];
  if (res != -1) return res;
  if (f > t) return res = 0;
  if (f == t) return res = 1;
  if (s[f] == s[t]) {
    tr[f][t] = p2(f + 1, t - 1);
    return res = solve(f + 1, t - 1) + 2;
  }
  int x = solve(f + 1, t);
  int y = solve(f, t - 1);
  if (x > y) {
    tr[f][t] = p2(f + 1, t);
    return res = x;
  }
  tr[f][t] = p2(f, t - 1);
  return res = y;
}
 
void trace(int f, int t, int rf, int rt) {
  if (f == 0 || t == 0) return;
  if (s[f] == s[t]) {
    ans[rf++] = s[f];
    ans[rt--] = s[t];
  }  
  trace(tr[f][t].first, tr[f][t].second, rf, rt);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  int sz = solve(1, n);
  trace(1, n, 1, sz);
  printf("%s", ans + 1);
} 