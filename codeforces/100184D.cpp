// 2013 ACM-ICPC Ukraine, Round 1
// D - Accomodation

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

bool sieve[50505];
std::string s;
int a[30303], l[30303], r[30303];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  for (int i = 2; i <= 30000; ++i)
    sieve[i] = true;
  for (int i = 2; i * i <= 30000; ++i)
    if (sieve[i])
      for (int j = i * i; j <= 30000; j += i)
        sieve[j] = false;
  int n;
  size_t sz;
  std::cin >> n >> sz >> s;
  for (size_t i = 0; i < sz; ++i)
    a[i + 1] = s[i] == 'Y';
  size_t it_a = 1, it_l = 1, it_r = n;
  while (it_a <= sz) {
    if (a[it_a] == sieve[it_l]) {
      l[it_a] = it_l;
      ++it_a;
    }
    ++it_l;
  }
  it_a = sz;
  while (it_a >= 1) {
    if (a[it_a] == sieve[it_r]) {
      r[it_a] = it_r;
      --it_a;
    }
    --it_r;
  }
  int ans = 0;
  for (size_t i = 1; i <= sz; ++i)
    ans += l[i] == r[i];
  std::cout << ans << '\n';
}