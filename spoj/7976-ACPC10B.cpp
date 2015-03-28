#include <iostream>
#include <map>
#define mii map<int, int>
using namespace std;
int sum(int k) {
  int res = 0, t;
  while (k) {
    t = k % 10;
    res += t * t;
    k /= 10;
  }
  return res;
}
void checka(int k, int step, mii& m, mii& was) {
  if (was[k]) return;
  was[k] = 1;
  m[k] = step;
  int tot = sum(k);
  checka(tot, step + 1, m, was);
}
int checkb(int k, int step, mii& m, mii& was) {
  if (was[k] == 1) return m[k] + step;
  else if (was[k] == 2) return -1;
  was[k] = 2;
  m[k] = step;
  int tot = sum(k);
  return checkb(tot, step + 1, m, was);
}
int solve(int a, int b) {
  int res;
  mii m, was;
  checka(a, 0, m, was);
  if (was[b]) res = m[b] + 2;
  else {
    int d = checkb(b, 0, m, was);
    if (d == -1) res = 0;
    else res = d + 2;
  }
  return res;
}
int main() {
  int a, b;
  while (cin >> a >> b) {
    if (a == 0 && b == 0) break;
    int ans = 0;
    if (a == b) ans = 2;
    else {
      int res1 = solve(a, b);
      int res2 = solve(b, a);
      ans = min(res1, res2);
    }    
    cout << a << ' ' << b << ' ' << ans << '\n';
  }
}