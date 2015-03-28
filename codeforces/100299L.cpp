#include <cstdio>
#include <iostream>
typedef long long LL;
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    int k;
    cin >> k;
    LL ans = 0;
    while (k--) {
      ans += 1;
      ans <<= 1; 
    }
    cout << (ans >> 1) << '\n';
  }
}