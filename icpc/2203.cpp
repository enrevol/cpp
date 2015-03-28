#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int ff(int n) {
  int res = 0;
  while (n) {
    res += n % 10;
    n /= 10;
  }
  return res;
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int ans = n + 1;
    while (1) {
      int a = ff(ans);
      int b = 0;
      int it = 2;
      int t = ans;      
      while (it * it <= t) {
        while (t % it == 0) {
          b += ff(it);
          t /= it;
        }
        ++it;
      }
      if (t < ans) {
        if (t > 1) b += ff(t);
        if (a == b) break;
      }
      ++ans;
    }
    printf("%d\n", ans);
  }
}