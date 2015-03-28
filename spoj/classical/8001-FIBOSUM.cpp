#include <algorithm>
#include <iostream>
#include <map>
#define MOD 1000000007
typedef long long LL;
using namespace std;
LL fi[20];
map<LL, LL> m;
int d = 0;
LL solve(LL k) {
  d++;
  if (k < 20) return fi[k];
  if (m[k]) return m[k];
  LL res1, res2;
  if (k & 1) {
    res1 = solve(k / 2);
    res2 = solve(k / 2 + 1);
    res1 = (res1 * res1) % MOD;
    res2 = (res2 * res2) % MOD;
    res1 = (res1 + res2) % MOD;    
  } else {
    res1 = solve(k / 2 - 1);
    res2 = solve(k / 2);
    res1 = (res1 * res2) % MOD;
    res1 = (res1 * 2) % MOD;
    res2 = (res2 * res2) % MOD;
    res1 = (res1 + res2) % MOD;
  }
  m[k] = res1;
  return res1;
}
LL sum(LL k) {
  LL res1 = solve(k + 1) - 1;
  LL res2 = solve(k);
  return (res1 + res2) % MOD;
}
int main() {
  fi[1] = 1;
  fi[2] = 1;
  for (int i = 3; i < 20; ++i) fi[i] = (fi[i - 1] + fi[i - 2]) % MOD;
  int T;
  cin >> T;
  while (T--) {
    LL N, M;    
    cin >> N >> M;
    d = 0;
    LL sM = sum(M);
    LL sN = sum(max(N - 1, 0LL));
    LL ans = sM - sN;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';
  }  
}