#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define MAX 1000005
#define pb push_back
using namespace std;
vector<int> primes;
vector<int> v[15];
int sieve[MAX], nextnum[MAX], step[MAX];
void pre() {
  sieve[2] = 2;
  primes.pb(2);
  for (int i = 3; i < MAX; i += 2)
    if (!sieve[i]) {
      primes.pb(i);
      for (int j = i; j < MAX; j += i * 2)
        sieve[j] = i;
    }
}
int cal(int n) {
  if (nextnum[n]) return nextnum[n];
  int k = 0, res = 0, sq = sqrt(n);
  while (primes[k] <= sq) {
    if (n % primes[k] == 0) {
      res += primes[k];
      while (n % primes[k] == 0) n /= primes[k];
    }
    k++;
  }
  if (n > 1) res += n;
  nextnum[n] = res;
  return res;
}
int solve(int n) {
  if (step[n]) return step[n];
  int res;
  if (sieve[n] == n) res = 1;
  else res = solve(cal(n)) + 1;  
  step[n] = res;
  return res;
}
int main() {
  pre();
  int d;
  for (int i = 2; i < MAX; ++i) {
    d = solve(i);
    v[d].pb(i);
  }
  int p, a, b, k, ans;
  vector<int>::iterator ai, bi;
  cin >> p;
  while (p--) {
    cin >> a >> b >> k;
    if (k > 12) ans = 0;
    else {
      ai = lower_bound(v[k].begin(), v[k].end(), a);
      bi = upper_bound(v[k].begin(), v[k].end(), b);
      ans = bi - ai;
    }
    cout << ans << '\n';
  }
}