#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int mod = 123456789;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  long long n;
  scanf("%lld", &n);
  if (n == 1) {
    printf("1");
  } else {
    --n;
    int ans = 1;
    int t = 2;
    while (n) {
      if (n & 1) ans = (1ll * ans * t) % mod;
      t = (1ll * t * t) % mod;
      n >>= 1;
    }
    printf("%d", ans);
  }
} 