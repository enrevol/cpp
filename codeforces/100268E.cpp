#include <cmath>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    double R, B, M;
    cin >> R >> B >> M;
    B = round(B * 100);
    M = round(M * 100);
    int ans = 0, f = 1;
    while (B > 0) {
      if (ans >= 1200) {
        f = 0;
        break;
      }
      B = B + round(B * R / 100);
      B = B - M;
      ans++;
    }
    if (f) cout << ans << '\n';
    else cout << "impossible\n";
  }
}