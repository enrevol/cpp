#include <iostream>
#include <string>
typedef long long LL;
using namespace std;
int ss[][4] = { { 0, 0, 0, 0 },
                { 1, 1, 1, 1 },
                { 2, 4, 8, 6 },
                { 3, 9, 7, 1 },
                { 4, 6, 4, 6 },
                { 5, 5, 5, 5 },
                { 6, 6, 6, 6 },
                { 7, 9, 3, 1 },
                { 8, 4, 2, 6 },
                { 9, 1, 9, 1 } };
int main() {
  int T;
  cin >> T;
  while (T--) {
    string a;
    LL b;
    cin >> a >> b;
    int d = a[a.length() - 1] - '0';
    if(b == 0) cout << "1";
    else cout << ss[d][(b - 1) % 4];
    cout << '\n';
  }
}