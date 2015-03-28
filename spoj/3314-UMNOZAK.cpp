#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
typedef long long ll;
 
const ll inf = 1e9;
 
ll a, b, p10[20], dp[20][30][20][15][12];
 
long long solve(const ll& qf, const ll& qt, const ll& n, int k, int x, int y, int z, int t) {
  ll vf = n;
  ll vt = n + p10[k] - 1;
  if (vt < qf || qt < vf) return 0;
  if (k == 0) return x == 0 && y == 0 && z == 0 && t == 0;  
  ll res = 0;
  if (qf <= vf && vt <= qt)
    if (dp[k][x][y][z][t] != -1)
      return dp[k][x][y][z][t];
  res += solve(qf, qt, n + p10[k - 1], k - 1, x, y, z, t);
  if (x >= 1) res += solve(qf, qt, n + (p10[k - 1] << 1), k - 1, x - 1, y, z, t);
  if (y >= 1) res += solve(qf, qt, n + (p10[k - 1] * 3),  k - 1, x, y - 1, z, t);
  if (x >= 2) res += solve(qf, qt, n + (p10[k - 1] << 2), k - 1, x - 2, y, z, t);
  if (z >= 1) res += solve(qf, qt, n + (p10[k - 1] * 5),  k - 1, x, y, z - 1, t);
  if (x && y) res += solve(qf, qt, n + (p10[k - 1] * 6),  k - 1, x - 1, y - 1, z, t);
  if (t >= 1) res += solve(qf, qt, n + (p10[k - 1] * 7),  k - 1, x, y, z, t - 1);
  if (x >= 3) res += solve(qf, qt, n + (p10[k - 1] << 3), k - 1, x - 3, y, z, t);
  if (y >= 2) res += solve(qf, qt, n + (p10[k - 1] * 9),  k - 1, x, y - 2, z, t);
  if (qf <= vf && vt <= qt)
    dp[k][x][y][z][t] = res;
  return res;
}
 
ll solve(const ll& val, int x, int y, int z, int t) {
  ll qf = a / val + (a % val > 0);
  ll qt = b / val;
  ll res = 0;
  for (int i = 1; i <= 18; ++i)
    res += solve(qf, qt, 0, i, x, y, z, t);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  p10[0] = 1;
  for (int i = 1; i <= 18; ++i)
    p10[i] = (p10[i - 1] << 3) + (p10[i - 1] << 1);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld %lld", &a, &b);
    ll ans = 0;
    for (ll x = 1, ix = 0; x <= inf; x <<= 1, ++ix)
      for (ll y = 1, iy = 0; x * y <= inf; y += y << 1, ++iy)
        for (ll z = 1, iz = 0; x * y * z <= inf; z += z << 2, ++iz)
          for (ll t = 1, it = 0; x * y * z * t <= inf; t = (t << 3) - t, ++it)
            ans += solve(x * y * z * t, ix, iy, iz, it);
    printf("%lld\n", ans);
  }
} 