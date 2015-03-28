#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
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
 
char s[101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s);
    switch (*s) {
      case 'l': scanf("%*s"); puts("1"); break;
      case 'd': puts("2"); break;
      case 'n': scanf("%*s"); puts("3"); break;
    }
  }
} 