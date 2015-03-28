#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int q;
  scanf("%d", &q);
  while (q--) {
    long long n, p;
    scanf("%lld %lld", &n, &p);
    int x = __builtin_popcountll(n - 1);
    x = x % p;
    printf("%d\n", x);
  }
}

