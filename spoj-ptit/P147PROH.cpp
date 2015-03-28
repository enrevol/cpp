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
 
char s[1010];
char t[1010];
int a[255];
int b[255];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int nc = 0;
  while (~scanf("%s %s", s, t)) {
    if (strcmp(s, "END") | strcmp(t, "END")) {      
      memset(a, 0, sizeof(a));
      memset(b, 0, sizeof(b));
      for (int i = 0; s[i]; ++i)
        ++a[s[i]];
      for (int i = 0; t[i]; ++i)
        ++b[t[i]];
      printf("Case %d: ", ++nc);
      puts(memcmp(a, b, sizeof(a)) ? "different" : "same");
    }
  }
} 