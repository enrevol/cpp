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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m, a;
  scanf("%d %d %d", &n, &m, &a);  
  printf("%lld", 1ll * (n / a + (n % a > 0)) * (m / a + (m % a > 0)));
} 