#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pLL;
int a[1000005];
void calc(LL val, int& d) {
  if (1 <= val && val <= 1000000 && a[val]) {
    d = a[val];
  } else {
    if (val & 1) {
      calc(val * 3 + 1, d);      
    } else {
      calc(val >> 1, d);
    }
    ++d;
    if (val <= 1000000) a[val] = d;
  }
}
int main() {
  ios::sync_with_stdio(0);
  a[1] = 1;
  int d;
  for (int i = 2; i <= 1000000; ++i)
    if (!a[i]) calc(i, d);
  int m, n;
  while (cin >> m >> n) {    
    int best = 1;
    for (int i = m; i <= n; ++i) best = max(best, a[i]);
    for (int i = n; i <= m; ++i) best = max(best, a[i]);
    cout << m << ' ' << n << ' ' << best << '\n';
  }
}