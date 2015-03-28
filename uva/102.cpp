#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pLL;
LL a[3][3];
string bin = "BGC";
int main() {
  ios::sync_with_stdio(0);
  while (cin >> a[0][0]) {
    for (int i = 1; i < 3; ++i) cin >> a[0][i];
    for (int i = 0; i < 3; ++i) cin >> a[1][i];
    for (int i = 0; i < 3; ++i) cin >> a[2][i];
    int best = -1;
    string s;  
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        for (int k = 0; k < 3; ++k)
          if (i != j && j != k && k != i) {
            int t =   a[1][i] + a[2][i]
                    + a[0][j] + a[2][j]
                    + a[0][k] + a[1][k];
            string b;
            b += bin[i];
            b += bin[j];
            b += bin[k];
            if (best == -1 || t < best || (t == best && b < s)) {
              best = t;
              s = b;
            }
          }
    cout << s << ' ' << best << '\n';
  }
}