#include <algorithm>
#include <iostream>
using namespace std;
int q[100005], n[100005];
int main() {
  int s;
  cin >> s;
  for (int i = 0; i < s; ++i) cin >> q[i];
  for (int i = 0; i < s; ++i) cin >> n[i];
  sort(q, q + s);
  sort(n, n + s);
  int qi = 0, ni = 0, ans = 0;
  while (qi < s && ni < s) {
    if (n[ni] > q[qi]) {
      ans++;
      qi++;
    }
    ni++;
  }
  cout << ans << '\n';
}