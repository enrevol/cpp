#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  int n, nCase = 0;
  while (cin >> n) {
    if (n < 0) break;
    int ans = 0;    
    while ((n & (- n)) != n) {
      n += n & (- n);
    }
    while (n > 1) {
      n >>= 1;
      ans++;
    }
    cout << "Case " << ++nCase << ": " << ans << '\n';
  }
}