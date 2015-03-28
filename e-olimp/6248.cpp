#include <iostream>
#include <string>
using namespace std;
int p[] = { 0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800 };
int main() {
  string S;
  int N;
  while (cin >> S >> N) {    
    string ans = "";
    if (N > p[S.length()]) {
      ans = "No permutation";
    } else {
      int d, t, n = N - 1, cnt = 0, k = S.length();
      int was[11];
      fill(was, was + k, 0);
      while (n) {
        k--;
        d = 0;
        t = n / p[k];
        for (int i = 0; i < S.length(); ++i)
          if (!was[i]) {
            if (d == t) {
              d = i;
              break;
            }
            d++;
          }
        was[d] = 1;
        n %= p[k];
        ans += S[d];
      }
      for (int i = 0; i < S.length(); ++i)
        if (!was[i]) ans += S[i];
    }
    cout << S << ' ' << N << " = " << ans << '\n';
  }
}