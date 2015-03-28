#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  long long a, b;
  scanf("%lld %lld", &a, &b);
  long long ans = 0;
  long long p = 0;
  for (int i = 60; i >= 0; --i) {
    long long f = (a >> i) + ((a & ((1ll << i) - 1)) > 0);
    long long t = (b >> i);
    long long val = t - f + 1;
    ans += (val - p) << i;
    p = val;
  }
  printf("%lld", ans);
} 