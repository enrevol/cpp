#include <iostream>
#include <queue>
using namespace std;
int primes[10005];
int f(int i) {
  queue<int> s;
  int t = i;
  while (t) {
    s.push(t % 10);
    t /= 10;
  }
  int p = 1;
  for (int j = 0; j < s.size(); ++j) p *= 10;
  t = 0;
  int k = 1;
  while (s.size()) {
    k *= 10;
    t += p / k * s.front();
    s.pop();
  }
  return t;
}
int main() {
  for (int i = 2; i <= 10000; ++i)
    if (!primes[i])
      for (int j = i; j <= 10000; j += i)
        primes[j] = i;
  int a, b, ans = 0;
  cin >> a >> b;
  if (a > b) {
    int t = a;
    a = b;
    b = t;
  }
  for (int i = a; i <= b; ++i) {
    if (primes[i] == i) {
      int t = f(i);
      if (primes[t] == t) ans++;
    }
  }
  cout << ans << '\n';
}