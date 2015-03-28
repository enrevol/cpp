#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[] = "ABCD";
 
void solve(int n, long long k, int f, int t, int& an, int& af, int& at) {
  //printf("%d %lld %d %d\n", n, k, f, t);
  if (n == 1) {
    an = 1;
    af = f;
    at = t;
  } else {
    int m = 3 - f - t;
    long long v = (1ll << (n - 1)) - 1;
    if (k <= v) return solve(n - 1, k, f, m, an, af, at);
    if (k > v + 1) return solve(n - 1, k - (v + 1), m, t, an, af, at);
    an = n;
    af = f;
    at = t;
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  int nc = 0;
  long long k;
  while(~scanf("%lld %d", &k, &n)) {
    if (n | k) {
      int an, af, at;
      solve(n, k, 0, 2, an, af, at);
      printf("Case %d: %d %c %c\n", ++nc, an, s[af], s[at]);
    }
  }
} 