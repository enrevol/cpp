#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#define ts first
#define ms second
#define pb push_back
#define mp make_pair
#define pLL pair<LL, LL>
typedef long long LL;
using namespace std;
vector<pLL> vs;
pLL lim = mp(1, 1);
pLL p0 = mp(0, 1);
void simplify(pLL& a) {
  LL g = __gcd(a.ts, a.ms);
  a.ts /= g;
  a.ms /= g;
}
pLL operator +(const pLL& a, const pLL& b) {
  if (a.ts == 0) return b;
  if (b.ts == 0) return a;
  pLL res = mp(a.ts * b.ms + b.ts * a.ms, a.ms * b.ms);
  simplify(res);
  return res;
}
pLL operator -(const pLL& a, const pLL& b) {
  if (b.ts == 0) return a;
  pLL res = mp(a.ts * b.ms - b.ts * a.ms, a.ms * b.ms);
  simplify(res);
  return res;
}
pLL operator *(const pLL& a, const int& t) {
  if (t == 0) return p0;
  pLL res = mp(a.ts * t, a.ms);
  simplify(res);
  return res;
}
bool operator <(const pLL& a, const pLL& b) {
  if (a.ts == 0) {
    if (b.ts == 0) return 0;
    else return 1;
  }
  if (b.ts == 0) return 0;
  return a.ts * b.ms < a.ms * b.ts;
}
bool func(const pLL& a, const pLL& b) {
  return a < b;
}
pLL abs(const pLL& a) {
  pLL res = a;
  if (a.ts < 0) res.ts = - res.ts;
  if (a.ms < 0) res.ms = - res.ms;
  return res;
}
void dfs(pLL sum, int k) {
  if (k > 13) {
    vs.pb(sum);
    return;
  }
  pLL t;
  for (int i = 0; t < lim; ++i) {
    t = sum + mp(1, k) * i;
    dfs(t, k + 1);
  }
}
int main() {
  freopen("zanzibar.in", "r", stdin);
  dfs(mp(0, 0), 2);
  sort(vs.begin(), vs.end(), func);
  int T, nCase = 0;
  cin >> T;
  while (T--) {
    pLL x;
    cin >> x.ts >> x.ms;
    vector<pLL>::iterator ii = lower_bound(vs.begin(), vs.end(), x, func);
    pLL res1 = *ii;
    pLL res2 = *(ii - 1);
    res1 = abs(res1 - x);
    res2 = abs(res2 - x);
    pLL ans;
    if (res1 < res2) ans = res1;
    else ans = res2;
    cout << "Case " << ++nCase << ": " << ans.ts << '/' << ans.ms << '\n';
  }
}