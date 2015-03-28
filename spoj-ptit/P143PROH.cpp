#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
long long fi[55];
 
void solve(long long n) {
  int it = 1;
  while (n >= fi[it + 1]) ++it;
  if (fi[it] == n) {
    printf("%lld", fi[it]);
  } else {
    solve(n - fi[it]);
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  fi[1] = fi[2] = 1;
  for (int i = 3; i <= 75; ++i)
    fi[i] = fi[i - 1] + fi[i - 2];
  long long n;
  scanf("%lld", &n);  
  solve(n);
} 