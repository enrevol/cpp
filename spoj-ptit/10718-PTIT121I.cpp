#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
int a[101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int k, r;
    char s[101];    
    scanf("%d %d %s", &k, &r, s + 1);
    printf("%d ", k);
    for (int i = 1; s[i]; ++i)
      for (int j = 0; j < r; ++j)
        putchar(s[i]);
    putchar('\n');
  }
} 