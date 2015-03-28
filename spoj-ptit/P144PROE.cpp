#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int p[101010], q[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int x, y, a, b;
  scanf("%d %d %d %d", &x, &y, &a, &b);
  int cnt = 0;
  for (int i = std::max(a, b + 1); i <= x; ++i)
    for (int j = b; j < i && j <= y; ++j) {      
      ++cnt;
      p[cnt] = i;
      q[cnt] = j;
    }      
  printf("%d\n", cnt);
  for (int i = 1; i <= cnt; ++i)
    printf("%d %d\n", p[i], q[i]);
} 