#include <algorithm>
#include <iostream>
using namespace std;
int a[20005], b[20005];
int main() {
  ios::sync_with_stdio(0);
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    for (int i = 0; i < m; ++i)
      cin >> b[i];
    sort(a, a + n);
    sort(b, b + m);
    int ans = 0;
    int ai = 0, bi = 0;
    while (ai < n && bi < m) {
      if (a[ai] <= b[bi]) {
        ans += b[bi];
        ai++;
      }
      bi++;
    }
    if (ai != n) {
      cout << "Loowater is doomed!\n";
    } else {
      cout << ans << '\n';
    }
  }
}