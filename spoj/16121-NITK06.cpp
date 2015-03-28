#include <iostream>
using namespace std;
int a[10005];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, ans = 1;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 1; i < n && ans; ++i) {
      a[i] -= a[i - 1];
      if (a[i] < 0) ans = 0;
    }
    if (a[n - 1]) ans = 0;
    if (ans) cout << "YES\n";
    else cout << "NO\n";
  }
} 