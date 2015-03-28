#include <algorithm>
#include <iostream>
using namespace std;
int h[20005];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> h[i];
    sort(h, h + n);
    int ans = h[k - 1] - h[0];
    for (int i = 1; i + k - 1 < n; ++i) ans = min(ans, h[i + k - 1] - h[i]);
    cout << ans << '\n';
  }
} 