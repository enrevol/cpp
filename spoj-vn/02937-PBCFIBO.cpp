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
 
int fi[1010101];
long long d[10101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  long long n, s;
  int k;
  scanf("%lld %d %lld", &n, &k, &s);
  fi[1] = 1 % k;
  fi[2] = 2 % k;
  int f = 0;
  for (int i = 3; !f; ++i) {
    fi[i] = (fi[i - 1] + fi[i - 2]) % k;
    if (fi[i - 1] == fi[1] && fi[i] == fi[2])
      f = i - 2;
  }
  //printf("f = %d\n", f);
  long long a = n / f;
  int b = n % f;
  for (int i = 1; i <= f; ++i)
    d[fi[i]] += a;
  for (int i = 1; i <= b; ++i)    
    ++d[fi[i]];
  long long sum = 0;
  //for (int i = 0; i < k; ++i)
  //  sum += d[i];
  //printf("%lld\n", sum);
  int it = 0;
  while (s > d[it]) {
    s -= d[it];
    ++it;
  }
  printf("%d", it);
} 