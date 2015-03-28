#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

bool ff(int n) {
  if (n == 1) return false;
  if (n == 2) return true;
  if (n & 1) {  
    for (int i = 3; i * i <= n; i += 2)
      if (n % i == 0) return false;
    return true;    
  } else {
    return false;
  }  
}

int hh(int n) {
  int res = 0;
  while (n) {
    res += n % 10;
    n /= 10;
  }
  return res;
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    int t = n;
    while (n >= 10 && !ff(n))
      n = hh(n);
    if (ff(n)) {
      printf("%7d %7d\n", t, n);
    } else {
      printf("%7d    none\n", t);
    }
  }
}