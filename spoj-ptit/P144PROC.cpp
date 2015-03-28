#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
const int mod = 1e9 + 7;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int a;
  long long b;
  while (1) {
    scanf("%d %lld", &a, &b);
    if (a == 0 && b == 0) break;
    int ans = 1;
    while (b) {
      if (b & 1) ans = (1ll * ans * a) % mod;
      a = (1ll * a * a) % mod;
      b >>= 1;
    }
    printf("%d\n", ans);
  }
} 