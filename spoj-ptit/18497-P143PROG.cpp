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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k;
  scanf("%d %d", &n, &k);
  int m = n - 1;
  int t = k / m;
  int r = k % m;
  printf("%d %d\n", t + k - (r == 0), t + k);
} 