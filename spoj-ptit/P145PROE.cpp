#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
char s[22], ans[11][111], pat[] = "#*";
 
void ff(int p, char c, int f) {
  for (int i = 1; i <= 5; ++i)
    for (int j = p - 2; j <= p + 2; ++j) {      
      if (abs(i - 3) + abs(j - p) == 2) {
        if ((f && ans[i][j]) || !ans[i][j])
          ans[i][j] = pat[f];
      } else if (!ans[i][j]) {
        ans[i][j] = '.';
      }
    }
  ans[3][p] = c;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  int p = 3;
  for (int i = 1; s[i]; ++i) {
    ff(p, s[i], (i % 3) == 0);
    p += 4;
  }
  for (int i = 1; i <= 5; ++i)
    puts(ans[i] + 1);
} 