#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
vector<LL> prize[22];
LL stick[33];
int main() {
  int T;
  cin >> T;
  while (T--) {
    LL n, m, t, k;
    cin >> n >> m;
    memset(stick, 0, sizeof(stick));    
    for (int i = 0; i < n; ++i) {
      cin >> k;
      prize[i].clear();
      for (int j = 0; j < k; ++j) {
        cin >> t;
        prize[i].push_back(t);
      }
      cin >> t;
      prize[i].push_back(t);
    }
    for (int i = 1; i <= m; ++i) {
      cin >> stick[i];
    }
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
      t = 1 << 30;
      for (int j = 0; j < prize[i].size() - 1; ++j) {
        t = min(t, stick[prize[i][j]]);
      }
      ans += t * prize[i][prize[i].size() - 1];
    }
    cout << ans << '\n';
  }
}