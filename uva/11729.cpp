#include <algorithm>
#include <iostream>
#include <functional>
#define pii pair<int, int>
using namespace std;
pii a[1005];
int main() {
  ios::sync_with_stdio(0);
  int n, tt = 0;
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; ++i)
      cin >> a[i].second >> a[i].first;
    sort(a, a + n, greater<pii>());
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      sum += a[i].second;
      ans = max(ans, sum + a[i].first);
    }
    cout << "Case " << ++tt << ": " << ans << '\n';
  }
}