#include <algorithm>
#include <cstdio>
#include <iostream>
#define MAXI 2000000
typedef long long LL;
using namespace std;
LL square[MAXI + 5];
LL linear[MAXI + 5];
int main() {
  for (LL i = 1; i <= MAXI; ++i) {
    square[i] = square[i - 1] + i * i;  
    linear[i] = linear[i - 1] + i;
  }
  freopen("army.in", "r", stdin);
  int T, nCase = 0;
  cin >> T;
  while (T--) {
    LL m;
    cin >> m;
    int row = lower_bound(square, square + MAXI, m) - square - 1;
    LL t = m - *(square + row);
    int maxCol = row + 1;
    LL maxVal = linear[maxCol];
    int col;
    if (t <= maxVal) {
      col = lower_bound(linear, linear + MAXI, t) - linear - 1;
    } else {
      t = *(square + row + 1) - m;
      col = upper_bound(linear, linear + MAXI, t) - linear - 1;
      col = row * 2 - col;
    }
    LL ans = 1LL * row * row + col + 1;
    cout << "Case " << ++nCase << ": " << ans << '\n';
  }
}
