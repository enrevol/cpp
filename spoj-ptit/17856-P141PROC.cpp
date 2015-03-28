#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  int ans = 0;
  while (n--) {    
    scanf("%s", s + 1);
    if (s[2] == '+') ++ans;
    else --ans;
  }
  printf("%d", ans);
}