#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (~scanf("%d", &n)) {
    if (n == 0) {
      puts("1");
    } else {
      int a[11];
      int d = 0;
      for (int tmp = n; tmp; tmp /= 10) a[++d] = tmp % 10;
      int cnt[11] = { 0 };
      int ans = 0;
      for (int i = 1; i <= d; ++i) ++cnt[a[i]];
      int p = 1;
      for (int i = 1; i <= d; ++i) {        
        p = p * 10;
        --cnt[a[i]];
        if (cnt[0] > 0) continue;
        int f = -1;
        for (int j = a[i] + 1; j <= 9; ++j)
          if (cnt[j] == 0) {
            f = j;
            break;
          }        
        for (int j = 1; j <= 9; ++j)
          if (cnt[j] > 1) {
            f = -1;
            break;
          }
        if (f != -1) {
          //fprintf(stderr, "i = %d\n", i);
          //fprintf(stderr, "f = %d\n", f);
          ans = n / p * p;
          //fprintf(stderr, "ans = %d\n", ans);
          p /= 10;
          ans = ans + p * f;          
          //fprintf(stderr, "ans = %d\n", ans);
          for (int j = 1, k = i - 1; j <= 9 && k >= 1; ++j)
            if (j != f && cnt[j] == 0) {
              p /= 10;
              ans = ans + j * p;
              --k;
            }
          break;
        }
      }
      //fprintf(stderr, "d = %d\n", d);
      if (ans == 0 && d < 9) {
        for (int i = 1; i <= d + 1; ++i)
          ans = ans * 10 + i;
      }
      printf("%d\n", ans);
    }
  }
}

