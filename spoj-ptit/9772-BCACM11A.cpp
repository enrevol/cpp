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
 
int a[1010101];
int cnt[5];
 
char dig[10];
char tmp[10];
 
bool ok3(int n) {
  memset(dig, 0, sizeof(dig));
  for (int i = 1; i <= 6; ++i) {
    dig[i] = n % 10;
    n /= 10;
  }
  std::reverse_copy(dig + 1, dig + 7, tmp + 1);
  return std::equal(dig + 1, dig + 7, tmp + 1);
}
 
bool ok2(int n) {
  int v = 0;
  for (int i = 1; i <= 6; ++i) {    
    v += n % 10;
    n /= 10;
  }
  return v % 10 == 0;
}
 
bool ok1(int n) {
  for (int i = 1; i <= 6; ++i) {
    if (n % 10 == 0) return false;
    n /= 10;
  }
  return true;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 100000; i <= 999999; ++i) {
    if (!ok3(i)) continue;
    ++a[i];
    if (!ok2(i)) continue;
    ++a[i];
    if (!ok1(i)) continue;
    ++a[i];
  }
  for (int i = 100000; i <= 999999; ++i)
    ++cnt[a[i]];  
  int tt;
  scanf("%d", &tt);
  int n, m, k;
  fprintf(stderr, "%d %d %d\n", cnt[1], cnt[2], cnt[3]);
  while (tt--) {
    scanf("%d %d %d", &n, &m, &k);
    if (n > cnt[3]) {
      puts("NO");
    } else {
      if (m > cnt[2] + cnt[3] - n) {
        puts("NO");
      } else {
        if (k > cnt[1] + cnt[2] + cnt[3] - m - n) {
          puts("NO");
        } else {
          puts("YES");
        }
      }
    }
  }
} 