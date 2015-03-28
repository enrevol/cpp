#include <iostream>
using namespace std;
int main() {
  int n, k, a, ans1 = 0, ans2 = 0;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a;
    if (a > k) ans1 += a - k;
    if (a < k) ans2 += k - a;
  }
  cout << ans1 << ' ' << ans2;
}