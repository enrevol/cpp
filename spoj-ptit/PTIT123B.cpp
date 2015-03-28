SPOJ submission 11228003 (C++ 4.3.2) plaintext list. Status: AC, problem PTIT123B, contest PTIT. By enrevol (What Does The Fox Say?), 2014-03-11 16:30:03.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[22];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, nc = 0;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    int ans = 0;
    bool f = false;
    while (ans <= 1000 && !f) {
      int x = *std::min_element(a + 1, a + n + 1);
      int y = *std::max_element(a + 1, a + n + 1);
      if (x == y) {
        f = true;
      } else {
        ++ans;
        int t = a[1];      
        for (int i = 1; i < n; ++i) {
          a[i] -= a[i + 1];
          if (a[i] < 0) a[i] = -a[i];
        }
        a[n] -= t;
        if (a[n] < 0) a[n] = -a[n];        
      }
    }
    printf("Case %d: ", ++nc);
    if (f) {
      printf("%d iterations\n", ans);
    } else {
      puts("not attained");
    }
  }
} 