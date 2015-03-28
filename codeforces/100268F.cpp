#include <cstdio>
#include <iostream>
typedef long long LL;
using namespace std;
LL f[11];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> f[i];
    int flag = 1;
    // d = 1
    // aF0 = F1
    if (f[1] % f[0] == 0) {
      LL k = f[1] / f[0];
      for (int i = 2; i < n && flag; ++i)
        if (f[i] != f[i - 1] * k)
          flag = 0;
      if (flag) cout << f[n - 1] * k << '\n';
    } else {
      flag = 0;
    }
    // d = 2
    // aF0 + bF1 = F2
    // aF1 + bF2 = F3
    if (!flag) {
      flag = 1;
      LL det  = f[0] * f[2] - f[1] * f[1];
      if (det == 0) {
        flag = 0;
      } else {        
        LL detX =   f[1]  * (-f[3]) - (-f[2]) *   f[2];
        LL detY = (-f[2]) *   f[1]  -   f[0]  * (-f[3]);
        if (detX % det == 0 && detY % det == 0) {
          LL a = detX / det;
          LL b = detY / det;
          for (int i = 4; i < n && flag; ++i)
            if (f[i] != b * f[i - 1] + a * f[i - 2])
              flag = 0;
          if (flag) cout << a * f[n - 2] + b * f[n - 1] << '\n';
        } else {
          flag = 0;
        }
      }
    }
    // d = 3
    // aF0 + bF1 + cF2 = F3
    // aF1 + bF2 + cF3 = F4
    // aF2 + bF3 + cF4 = F5
    // -3 1 2
    // -4 2 3 
    // -5 3 4
    // 0 -3 2
    // 1 -4 3
    // 2 -5 4
    // 0 1 -3
    // 1 2 -4
    // 2 3 -5
    if (!flag) {
      LL det  = +   f[0]  * (f[2]  *   f[4]  -   f[3]  * f[3])
                -   f[1]  * (f[1]  *   f[4]  -   f[3]  * f[2])
                +   f[2]  * (f[1]  *   f[3]  -   f[2]  * f[2]);
      LL detX = + (-f[3]) * (f[2]  *   f[4]  -   f[3]  * f[3])
                -   f[1]  * (f[4]  * (-f[4]) - (-f[5]) * f[3])
                +   f[2]  * (f[3]  * (-f[4]) - (-f[5]) * f[2]);
      LL detY = +   f[0]  * (f[4]  * (-f[4]) - (-f[5]) * f[3])
                - (-f[3]) * (f[1]  *   f[4]  -   f[3]  * f[2])
                +   f[2]  * (f[1]  * (-f[5]) - (-f[4]) * f[2]);
      LL detZ = +   f[0]  * (f[2]  * (-f[5]) - (-f[4]) * f[3])
                -   f[1]  * (f[1]  * (-f[5]) - (-f[4]) * f[2])
                + (-f[3]) * (f[1]  *   f[3]  -   f[2]  * f[2]);
      //cout << det << ' ' << detX << ' ' << detY << ' ' << detZ << '\n';
      LL a = - detX / det;
      LL b = - detY / det;
      LL c = - detZ / det;
      cout << a * f[n - 3] + b * f[n - 2] + c * f[n - 1] << '\n';
    }
  }
}