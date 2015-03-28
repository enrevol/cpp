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
  long long n;
  scanf("%lld", &n);
  int k = 0;
  while (n) {
    k += n % 10 == 4 || n % 10 == 7;
    n /= 10;
  }
  puts(k == 4 || k == 7 ? "YES" : "NO");
} 