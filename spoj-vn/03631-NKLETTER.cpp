#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
std::string a, b;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  std::cin >> a >> b;
  int sa = a.size();
  int sb = b.size();  
  for (int i = 0; i < sa; ++i) {
    int f = 1;
    for (int j = i; j < sa; ++j)
      if (j - i >= sb || a[j] != b[j - i]) f = 0;
    if (f) {
      printf("%d", sa + sb - (sa - i));
      return 0;
    }
  }
  printf("%d", sa + sb);
} 