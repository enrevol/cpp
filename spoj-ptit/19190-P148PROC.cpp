#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int w = 15e5;
const int h = 1e3;
 
bool sieve[w + 10];
int b[w + 10];
int p[200];
int a[w + 10];
int v[w + 10];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 3; i <= h; i += 2)
    if (!sieve[i])
      for (int j = i * i; j <= w; j += i << 1)
        sieve[j] = true;  
  v[2] = 2;
  for (int i = 3; i <= w; ++i)
    if (!sieve[i])
      v[i] = i;
  int pn = 0;
  p[++pn] = 2;
  for (int i = 3; i <= h; i += 2)
    if (!sieve[i])
      p[++pn] = i;
  a[1] = 1; b[1] = 1;
  a[2] = 2; b[2] = 2;
  for (int i = 3; i <= 585000; ++i) {
    int val = a[i - 1];
    int ft[10] = { 0 };
    int fn = 0;
    for (int j = 1; j <= pn && p[j] * p[j] <= val && val > 1; ++j)
      if (val % p[j] == 0) {
        while (val % p[j] == 0)
          val /= p[j];
        ft[++fn] = p[j];
      }
    if (val > 1) ft[++fn] = val;
    int x = -1;
    for (int j = 1; j <= fn; ++j) {
      while (b[v[ft[j]]]) v[ft[j]] += ft[j];
      if (x == -1 || v[x] > v[ft[j]])
        x = ft[j];
    }
    a[i] = v[x];
    b[a[i]] = i;
  }
  int n;
  while (~scanf("%d", &n))
    if (n) printf("The number %d appears in location %d.\n", n, b[n]);
} 