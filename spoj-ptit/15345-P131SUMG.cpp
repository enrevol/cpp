#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[303030];
int dp[2][303030][20];
 
int comp(int k, int i, int j) {
  if (k) return a[i] > a[j] ? i : j;
  return a[i] < a[j] ? i : j;
}
 
int query(int k, int f, int t) {
  int h = std::__lg(t - f + 1);
  return comp(k, dp[k][f][h], dp[k][t - (1 << h) + 1][h]);
}
 
long long solve(int k, int f, int t) {  
  if (f > t) return 0;
  int p = query(k, f, t);
  int l = p - f + 1;
  int r = t - p + 1;
  long long res = 1ll * l * r * a[p];
  res += solve(k, f, p - 1);
  res += solve(k, p + 1, t);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    dp[0][i][0] = i;
    dp[1][i][0] = i;
  }  
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i + (1 << j) - 1 <= n; ++i)
      for (int k = 0; k < 2; ++k)
        dp[k][i][j] = comp(k, dp[k][i][j - 1], dp[k][i + (1 << (j - 1))][j - 1]);  
  printf("%lld", solve(1, 1, n) - solve(0, 1, n));
} 