#include <algorithm>
#include <cassert>
#include <cmath>
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
 
char s[111];
char t[111][111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s);
  int n = strlen(s);
  int row;
  int col;
  for (row = sqrt(n); row >= 1; --row)
    if (n % row == 0) break;
  col = n / row;
  for (int i = 0; i < col; ++i)
    for (int j = i; j < n; j += row)
      t[i][(j - i) / row] = s[j];
  for (int i = 0; i < row; ++i)
    printf("%s", t[i]);
} 