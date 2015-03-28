#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[50505];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s + 1);
    int sz = strlen(s + 1);
    int ans = 0;
    int left = 1, right = sz, mid = 1, ff = 1;
    while (left + mid - 1 < right) {
      //printf("left = %d right = %d mid = %d\n", left, right, mid);
      if (s[left] == s[right] && s[left + mid - 1] == s[right + mid - 1]) {
        int f = 1;
        for (int i = 1; i <= mid && f; ++i)
          if (s[left + i - 1] != s[right + i - 1])
            f = 0;
        if (f) {
          ++ans;
          if (left + mid == right) ff = 0;
          left += mid;
          --right;
          mid = 1;
        } else {
          --right;
          ++mid;
        }
      } else {
        --right;
        ++mid;
      }
    }    
    printf("Case #%d: %d\n", ++n_case, (ans << 1) + ff);
  }
}