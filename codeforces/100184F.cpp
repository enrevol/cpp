#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long ll;

const ll mod = 1e9 + 7;

ll calc(ll n, ll k) {
  n %= mod;
  k %= mod;
  ll a = (n * (n + 1)) >> 1;
  a %= mod;
  //printf("n = %I64d a = %I64d k = %I64d\n", n, a, k);
  return (a * k) % mod;
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  ll n, a, b;
  std::cin >> n >> a >> b;
  ll c_a = calc((n - 1) / a, a);
  ll c_b = calc((n - 1) / b, b);
  ll c_ab = 0;
  ll g = std::__gcd(a, b);
  ll h = a / g * b;
  if (h / b == a / g) {
    c_ab = calc((n - 1) / h, h);
  }
  std::cout << (c_a + c_b - c_ab) % mod;
}