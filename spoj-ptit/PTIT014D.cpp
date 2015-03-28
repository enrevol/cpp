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
 
bool b[1010];
char s[1010];
 
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
  b[9] = true;
  for (int i = 10; i <= 1000; ++i) {
    int t = i;
    while (t >= 10 && !b[i]) {
      int v = ff(t);
      b[i] = b[v];
      t = v;
    }
  }
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s);
    int v = 0;
    for (int i = 0; s[i]; ++i)
      v += s[i] - '0';
    if (v == 9 || b[v]) {
      puts("1");
    } else {
      puts("0");
    }
  }
} 